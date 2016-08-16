AMFS_VERSION="0.1"

EXTRA_CFLAGS += -DAMFS_VERSION=\"$(AMFS_VERSION)\"

obj-$(CONFIG_AM_FS) += amfs.o

amfs-y := dentry.o file.o inode.o main.o super.o lookup.o mmap.o ioctl.o

INC=/lib/modules/$(shell uname -r)/build/arch/x86/include

all: amfs amfsctl

amfs:
	make -Wall -Werror -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

amfsctl:
	gcc -Wall -Werror amfsctl.c -o amfsctl

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -rf amfsctl
