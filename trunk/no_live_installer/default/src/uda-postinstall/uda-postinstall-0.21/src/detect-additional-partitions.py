# -*- coding: utf-8 -*-

import os

# Changelog
# - Modificado el backend sfdisk -> parted
# - Casos de traduccion con el nuevo backend:
#     fat32 -> vfat
#     linux-swap -> swap
# - Añadido método get_disks()
# - Añadido modo DEBUG 
# - Añadido método get_partitions_already_used()
#   No se tocará ninguna de estas particiones, las ya existenten se quedarán comom están. Es decir, únicamente se añadirán las particiones que el usuario no haya configurado en el particionado.
# - passno siempre 0 para todas las particiones que no se hayan definido en el particionado

DEBUG=0

def get_partitions():
  """returns an array with fdisk output related to partition data."""

  import re

  # parsing partitions from the procfs
  # attetion with the output format. the partitions list is without '/dev/'
  partition_table = open('/proc/partitions').read()
  regex = re.compile('[sh]d[a-g][0-9]+')
  partition = regex.findall(partition_table)

  return partition

def get_disks():
  """returns a set with the disks detected."""

  import re

  # parsing partitions from the procfs
  # attetion with the output format. the partitions list is without '/dev/'
  partition_table = open('/proc/partitions').read()
  regex = re.compile('[sh]d[a-g]')
  disks = regex.findall(partition_table)
  disks = set(disks)

  return disks

def get_filesystems():
  """returns a dictionary with a skeleton { device : filesystem }
  with data from local hard disks. Only swap and ext3 filesystems
  are available."""

  import re, subprocess
  device_list = {}

  disks_list = get_disks()

  if DEBUG:
    print "disk_list: ", disks_list

  # For each disk, have a look for the partitions that it has.
  for disk in disks_list:
    disk = '/dev/' + disk
    if DEBUG:
      print "disk: " + disk
    partition_pipe = subprocess.Popen(['parted', '-s', disk, 'print'], stdout=subprocess.PIPE)
    partitions = partition_pipe.communicate()[0]

    partitions = partitions.splitlines()
    # If the output is smaller than this, is not correct.
    if partitions.__len__() > 2:
      # For each line of partition... the first partition starts at the 4th line
      for x in range(3,partitions.__len__()):
        temp_line = partitions[x].split()
        # This condiction has to be satisfied if parted has identified the partition fs.
        if temp_line.__len__() == 5:
          partition_number = temp_line[0]
          partition_type = temp_line[4]
	  if partition_type == 'fat32':
            device_list[disk + partition_number] = 'vfat'
          elif partition_type == 'linux-swap':
            device_list[disk + partition_number] = 'swap'
          else:
            device_list[disk + partition_number] = partition_type
          if DEBUG:
            print "partition: ", partition_number, partition_type, disk + partition_number, device_list[disk + partition_number]
         
  return device_list

def get_partitions_already_used():
  """returns an array containing all the partitions already listed."""
  fstab = open('/etc/fstab', 'r')
  blacklist = []
  import re
  for line in fstab.readlines():
  	list_columns = line.split()
  	try:
  		dev_re = re.compile('/dev/*')
  		is_true = dev_re.match(list_columns[0])
  
                if is_true:
                  blacklist.append(list_columns[0])
  	except:
  		pass
  fstab.close()
  
  return blacklist

########
# MAIN #
########

if DEBUG:
  print "DEBUG MODE ENABLED"

blacklist = get_partitions_already_used()

if DEBUG:
  print "blacklist: ", blacklist

fstab = open('/etc/fstab','a')

win_counter = 1

for new_device, fs in get_filesystems().items():
  # CASE 1: Windows partitions
  if ( fs in ['vfat', 'ntfs'] ):
    passno = 0
    if not (new_device in blacklist):
      if fs == 'vfat' :
        options = 'rw,gid=100,users,umask=0002,fmask=0113,sync,noauto,defaults'
      else:
        options = 'gid=100,users,umask=0222,fmask=0333,sync,nls=utf8,noauto,defaults'
      path = '/media/Windows%d' % win_counter
      if not os.path.exists(path):
        os.mkdir(path)
      win_counter += 1
      if DEBUG:
        print '%s\t%s\t%s\t%s\t%d\t%d' % (new_device, path, fs, options, 0, passno)
      else:
        print >>fstab, '%s\t%s\t%s\t%s\t%d\t%d' % (new_device, path, fs, options, 0, passno)
  # CASE 2: swap
  elif fs == 'swap':
    passno = 0
    if not (new_device in blacklist):
      options = 'sw'
      path = 'none'
      if DEBUG:
        print '%s\t%s\t%s\t%s\t%d\t%d' % (new_device, path, fs, options, 0, passno)
      else:
        print >>fstab, '%s\t%s\t%s\t%s\t%d\t%d' % (new_device, path, fs, options, 0, passno)
  # CASE 3: common partitions types that hasn't been set yet
  elif fs in ['ext3', 'ext2', 'reiserfs', 'xfs']:
    passno = 2
    if not (new_device in blacklist):
      options = 'defaults'
      path = '/media/%s%d' % (new_device[5:8],int(new_device[8:]))
      if not os.path.exists(path):
        os.mkdir(path)
      if DEBUG:
        print '%s\t%s\t%s\t%s\t%d\t%d' % (new_device, path, fs, options, 0, passno)
      else:
        print >>fstab, '%s\t%s\t%s\t%s\t%d\t%d' % (new_device, path, fs, options, 0, passno)
fstab.close()
