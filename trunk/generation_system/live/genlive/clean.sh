#!/bin/sh
#
# clean.sh:
# 1) Put pkgs to install in PKGSDIR on target system
# 2) Put this script in /tmp on target system
# 3) Execute chroot /target /tmp/clean.sh

PKGSDIR=/tmp/pkgs

# Install pkgs in PKGSDIR
cd $PKGSDIR
dpkg --install *.deb

#apt-get update && apt-get -f install -y --force-yes
apt-get -f install -y --force-yes

# Removing cdrom line from sources.list
cat /etc/apt/sources.list | grep -v cdrom > /tmp/sources.list.tmp
cp /tmp/sources.list.tmp /etc/apt/sources.list

# Cleaning /etc/fstab
rm /etc/fstab
touch /etc/fstab

# Cleaning /media
rm -rf /media/*

# Cleaning Hermes
rm -rf /var/tmp/*

# Removing users
for user in `ls /home | xargs -n 1 | grep -v compartido`
do
  deluser --remove-home $user
  rm -rf /home/$user
done

# Cleaning flash
rm -rf /usr/lib/flashplugin-nonfree

# Cleaning /etc/resolv.conf
rm /etc/resolv.conf
touch /etc/resolv.conf

# Cleaning menu.lst
rm /boot/grub/menu.lst*
touch /boot/grub/menu.lst

# Restoring the initial config at initramfs.conf
grep -q "#RESUME=" /etc/mkinitramfs/initramfs.conf || sed -i "s|RESUME=\(.*\)|#RESUME=|g" /etc/mkinitramfs/initramfs.conf

# Cleaning up the alsa configuration
rm -f /var/lib/alsa/asound.state

# Cleaning /tmp
cd /tmp
for file in `find`
do
  if [ "$file" = "." ]; then
	continue
  fi
  rm $file -rf
done

# Finishing
echo "Cleaning process finished..."