#!/bin/sh
echo "unmounting wrapfs filesystem"
umount /mnt/wrapfs
rmmod wrapfs
insmod wrapfs.ko
echo "mounting wrapfs filesystem"
mount -t wrapfs /home/student/wrapFileSystem /mnt/wrapfs
