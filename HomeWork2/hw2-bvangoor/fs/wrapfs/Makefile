WRAPFS_VERSION="0.1"

EXTRA_CFLAGS += -DWRAPFS_VERSION=\"$(WRAPFS_VERSION)\"

obj-$(CONFIG_WRAP_FS) += wrapfs.o

wrapfs-y := dentry.o file.o inode.o main.o super.o lookup.o mmap.o

INC=/lib/modules/$(shell uname -r)/build/arch/x86/include

all: wrapfs

wrapfs:
	make -Wall -Werror -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
