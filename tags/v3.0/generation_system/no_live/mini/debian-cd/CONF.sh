#
# This file will have to be sourced where needed
#

# Unset all optional variables first to start from a clean state
unset NONUS             || true
unset FORCENONUSONCD1   || true
unset NONFREE           || true
unset CONTRIB           || true
unset EXTRANONFREE      || true
# allow configuration on command line
#unset LOCAL             || true
#unset LOCALDEBS         || true
unset SECURED           || true
unset SECRET_KEYRING    || true
unset PUBLIC_KEYRING    || true
unset SIGNING_KEYID     || true
unset SECURITY          || true
unset BOOTDIR           || true
unset BOOTDISKS         || true
unset SYMLINK           || true
unset COPYLINK          || true
unset MKISOFS           || true
unset MKISOFS_OPTS      || true
unset ISOLINUX          || true
unset EXCLUDE           || true
unset SRCEXCLUDE        || true
unset NODEPENDS         || true
unset NORECOMMENDS      || true
unset NOSUGGESTS        || true
unset DOJIGDO           || true
unset JIGDOCMD          || true
unset JIGDOTEMPLATEURL  || true
unset JIGDOFALLBACKURLS || true
unset JIGDOINCLUDEURLS  || true
unset JIGDOSCRIPT       || true
unset DEFBINSIZE        || true
unset DEFSRCSIZE        || true
unset FASTSUMS          || true
unset PUBLISH_URL       || true
unset PUBLISH_NONUS_URL || true
unset PUBLISH_PATH      || true
unset UDEB_INCLUDE      || true
unset UDEB_EXCLUDE      || true
unset BASE_INCLUDE      || true
unset BASE_EXCLUDE      || true
unset INSTALLER_CD      || true
unset DI_CODENAME       || true
unset MAXCDS            || true
unset OMIT_MANUAL	|| true


if [ -z "$PROJECT" ]; then
  PROJECT=guadalinex
fi
if [ -z "$CAPPROJECT" ]; then
  CAPPROJECT="$(echo "$PROJECT" | perl -ne 'print ucfirst')"
fi

if [ -z "$DIST" ]; then
  DIST=breezy
fi

# The debian-cd dir
# Where I am (hoping I'm in the debian-cd dir)
export BASEDIR=`pwd`

case $DIST in
  warty)
    export CODENAME=warty
    export CAPCODENAME='Warty Warthog'
    export DEBVERSION=4.10
    export OFFICIAL="Linux+ Edition"
    ;;
  hoary)
    export CODENAME=hoary
    export CAPCODENAME='Hoary Hedgehog'
    export DEBVERSION=5.04
    export OFFICIAL="Release"
    ;;
  breezy)
    export CODENAME=breezy
    export CAPCODENAME='Flamenco'
    export DEBVERSION=2005
    export OFFICIAL="Beta"
    ;;
#  gx05)
#  gx05-mini)
esac

# By default use Debian installer packages from $CODENAME
if [ ! "$DI_CODENAME" ]
then
  export DI_CODENAME=$CODENAME
fi

# If set, controls where the d-i components are downloaded from.
# This may be an url, or "default", which will make it use the default url
# for the daily d-i builds. If not set, uses the official d-i images from
# the Debian mirror.
#export DI_WWW_HOME=default

# installer for properly uploaded debian-installer builds, daily-installer
# for autobuilt dailies. The newest available version is selected
# automatically; this is an override.
#export DI_TYPE=installer

# ... for arch  
export ARCH=`dpkg --print-installation-architecture`

# IMPORTANT : The 4 following paths must be on the same partition/device.
#	      If they aren't then you must set COPYLINK below to 1. This
#	      takes a lot of extra room to create the sandbox for the ISO
#	      images, however. Also, if you are using an NFS partition for
#	      some part of this, you must use this option.
# Paths to the mirrors
export MIRROR=${MIRROR:-$CDIMAGE_ROOT/ftp}

# Comment the following line if you don't have/want non-US
#export NONUS=/ftp/debian-non-US

# And this option will make you 2 copies of CD1 - one with all the
# non-US packages on it, one with none. Useful if you're likely to
# need both.
#export FORCENONUSONCD1=1

# Path of the temporary directory
export TDIR=$CDIMAGE_ROOT/scratch/$PROJECT/tmp

# Path where the images will be written
export OUT=$CDIMAGE_ROOT/scratch/$PROJECT/debian-cd

# Where we keep the temporary apt stuff.
# This cannot reside on an NFS mount.
export APTTMP=$CDIMAGE_ROOT/scratch/$PROJECT/apt

# Where extracted debootstrap scripts live
export DEBOOTSTRAP=$CDIMAGE_ROOT/scratch/$PROJECT/debootstrap

# Where live filesystem images live
export LIVEIMAGES=$CDIMAGE_ROOT/scratch/$PROJECT/live

# Do I want to have NONFREE merged in the CD set
# export NONFREE=1

# Do I want to have CONTRIB merged in the CD set
#export CONTRIB=1

# Do I want to have NONFREE on a separate CD (the last CD of the CD set)
# WARNING: Don't use NONFREE and EXTRANONFREE at the same time !
# export EXTRANONFREE=1

export RESTRICTED=1

#export UNIVERSE=1

# If you have a $MIRROR/dists/$CODENAME/local/binary-$ARCH dir with 
# local packages that you want to put on the CD set then
# uncomment the following line 
# export LOCAL=1

# If your local packages are not under $MIRROR, but somewhere else, 
# you can uncomment this line and edit to to point to a directory
# containing dists/$CODENAME/local/binary-$ARCH
# export LOCALDEBS=$CDIMAGE_ROOT/local/packages

# If you want a <codename>-secured tree with a copy of the signed
# Release.gpg and files listed by this Release file, then
# uncomment this line
# export SECURED=1

case $DIST in
  warty) ;;
  *)
    export SECRET_KEYRING=$CDIMAGE_ROOT/secret/dot-gnupg/secring.gpg
    export PUBLIC_KEYRING=$CDIMAGE_ROOT/secret/dot-gnupg/pubring.gpg
#    export SIGNING_KEYID=FBB75451
    export SIGNING_KEYID=E8AC3912
    ;;
esac

# Where to find the security patches.  This directory should be the
# top directory of a security.debian.org mirror.
case $DIST in
  warty)
    export SECURITY="$MIRROR"
    ;;
esac

# Sparc only : bootdir (location of cd.b and second.b)
# export BOOTDIR=/boot

# Symlink farmers should uncomment this line :
# export SYMLINK=1

# Use this to force copying the files instead of symlinking or hardlinking
# them. This is useful if your destination directories are on a different
# partition than your source files.
# export COPYLINK=1

# Options
# export MKISOFS=/usr/bin/mkisofs
# export MKISOFS_OPTS="-r"		#For normal users
# export MKISOFS_OPTS="-r -F ."	#For symlink farmers

# ISOLinux support for multiboot on CD1 for i386
export ISOLINUX=1

# uncomment this to if you want to see more of what the Makefile is doing
#export VERBOSE_MAKE=1

# uncoment this to make build_all.sh try to build a simple CD image if
# the proper official CD run does not work
#ATTEMPT_FALLBACK=yes

# Set your disk size here in MB. Used in calculating package and
# source file layouts in build.sh and build_all.sh. Defaults are for
# CD-R, try ~4600 for DVD-R.
if [ "$CDIMAGE_DVD" = 1 ]; then
  export DEFBINSIZE=4600
  export DEFSRCSIZE=4600
else
  export DEFBINSIZE=700
  export DEFSRCSIZE=690
fi

# We don't want certain packages to take up space on CD1...
#export EXCLUDE="$BASEDIR"/tasks/exclude-sarge
# ...but they are okay for other CDs (UNEXCLUDEx == may be included on CD >= x)
#export UNEXCLUDE2="$BASEDIR"/tasks/unexclude-CD2-sarge
# Any packages listed in EXCLUDE but not in any UNEXCLUDE will be
# excluded completely.

# We also exclude some source packages
#export SRCEXCLUDE="$BASEDIR"/tasks/exclude-src-potato

export NODEPENDS=1

# Set this if the recommended packages should be skipped when adding 
# package on the CD.  The default is 'false'.
export NORECOMMENDS=1

# Set this if the suggested packages should be skipped when adding 
# package on the CD.  The default is 'true'.
export NOSUGGESTS=1

# Produce jigdo files:
# 0/unset = Don't do jigdo at all, produce only the full iso image.
# 1 = Produce both the iso image and jigdo stuff.
# 2 = Produce ONLY jigdo stuff by piping mkisofs directly into jigdo-file,
#     no temporary iso image is created (saves lots of disk space).
#     NOTE: The no-temp-iso will not work for (at least) alpha and powerpc
#     since they need the actual .iso to make it bootable. For these archs,
#     the temp-iso will be generated, but deleted again immediately after the
#     jigdo stuff is made; needs temporary space as big as the biggest image.
#if [ "$CDIMAGE_DVD" = 1 ]; then
#  # disabled for now, takes ages
#  export DOJIGDO=0
#elif [ "$CDIMAGE_INSTALL" != 1 ]; then
#  # inappropriate
#  export DOJIGDO=0
#elif [ "$DIST" = warty ]; then
#  # only custom builds now
#  export DOJIGDO=0
#elif [ "$SPECIAL" = 1 ]; then
#  # special custom build
#  export DOJIGDO=0
#else
#  export DOJIGDO=1
#fi

DOJIGDO=0

#
# jigdo-file command & options
# Note: building the cache takes hours, so keep it around for the next run
export JIGDOCMD="jigdo-file --cache=$TDIR/jigdo-cache.db"
#
# HTTP/FTP URL for directory where you intend to make the templates
# available. You should not need to change this; the default value ""
# means "template in same dir as the .jigdo file", which is usually
# correct. If it is non-empty, it needs a trailing slash. "%ARCH%"
# will be substituted by the current architecture.
#export JIGDOTEMPLATEURL=""
#
# Name of a directory on disc to create data for a fallback server in. 
# Should later be made available by you at the URL given in
# JIGDOFALLBACKURLS. In the directory, two subdirs named "Debian" and
# "Non-US" will be created, and filled with hard links to the actual
# files in your FTP archive. Because of the hard links, the dir must
# be on the same partition as the FTP archive! If unset, no fallback
# data is created, which may cause problems - see README.
#export JIGDOFALLBACKPATH="$(OUT)/snapshot/"
#
# Space-separated list of label->URL mappings for "jigdo fallback
# server(s)" to add to .jigdo file. If unset, no fallback URL is
# added, which may cause problems - see README.
export JIGDOFALLBACKURLS="Debian=http://archive.ubuntu.com/ubuntu/"
# commented out until the snapshot archives actually exist to avoid
# silly server load
#export JIGDOFALLBACKURLS="Debian=http://archive.ubuntu.com/cdimage/jigit/$CODENAME/snapshot/"
#
# Space-separated list of "include URLs" to add to the .jigdo file. 
# The included files are used to provide an up-to-date list of Debian
# mirrors to the jigdo _GUI_application_ (_jigdo-lite_ doesn't support
# "[Include ...]").
#export JIGDOINCLUDEURLS="http://cdimage.debian.org/debian-cd/debian-servers.jigdo"
#
# $JIGDOTEMPLATEURL and $JIGDOINCLUDEURLS are passed to
# "tools/jigdo_header", which is used by default to generate the
# [Image] and [Servers] sections of the .jigdo file. You can provide
# your own script if you need the .jigdo file to contain different
# data.
#export JIGDOSCRIPT="myscript"

# If set, use the md5sums from the main archive, rather than calculating
# them locally
#export FASTSUMS=1

# A couple of things used only by publish_cds, so it can tweak the
# jigdo files, and knows where to put the results.
# You need to run publish_cds manually, it is not run by the Makefile.
export PUBLISH_URL="http://cdimage.debian.org/jigdo-area"
export PUBLISH_NONUS_URL="http://non-US.cdimage.debian.org/jigdo-area"
export PUBLISH_PATH="/home/jigdo-area/"

# Where to find the boot disks
#export BOOTDISKS=$TOPDIR/ftp/skolelinux/boot-floppies

# File with list of packages to include when fetching modules for the
# first stage installer (debian-installer). One package per line.
# Lines starting with '#' are comments.  The package order is
# important, as the packages will be installed in the given order.
export UDEB_INCLUDE="$BASEDIR"/data/$CODENAME/udeb_include

# File with list of packages to exclude as above.
#export UDEB_EXCLUDE="$BASEDIR"/data/$CODENAME/udeb_exclude

# File with list of packages to include when running debootstrap from
# the first stage installer (currently only supported in
# debian-installer). One package per line.  Lines starting with '#'
# are comments.  The package order is important, as the packages will
# be installed in the given order.
export BASE_INCLUDE="$BASEDIR"/data/$CODENAME/base_include

# File with list of packages to exclude as above.
#export BASE_EXCLUDE="$BASEDIR"/data/$CODENAME/base_exclude

# Only put the installer onto the cd (set NORECOMMENDS,... as well).
# INSTALLER_CD=0: nothing special (default)
# INSTALLER_CD=1: just add debian-installer (use TASK=tasks/debian-installer)
# INSTALLER_CD=2: add d-i and base (use TASK=tasks/debian-installer+kernel)
#export INSTALLER_CD=0

# Parameters to pass to kernel when the CD boots. Not currently supported
# for all architectures.
#export KERNEL_PARAMS="DEBCONF_PRIORITY=critical"

# If set, limits the number of binary CDs to produce.
export MAXCDS=1

# If set, overrides the boot picture used.
if [ -z "$SPLASHRLE" ]; then
	export SPLASHRLE="$BASEDIR/data/$DI_CODENAME/splash.rle"
fi

# Used by build.sh to determine what to build, this is the name of a target
# in the Makefile. Use bin-official_images to build only binary CDs. The
# default, official_images, builds everything.
IMAGETARGET=bin-official_images

# Set to 1 to save space by omitting the installation manual. 
# If so the README will link to the manual on the web site.
#export OMIT_MANUAL=1

SKIPMIRRORCHECK=yes

COMPLETE=0
