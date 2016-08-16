#!/bin/sh
echo "unmounting amfs filesystem"
umount /mnt/amfs
rmmod amfs
insmod amfs.ko
echo "mounting amfs filesystem"
mount -t amfs -o pattdb=/mypatterns.db /home/student/AMFileSystem /mnt/amfs
