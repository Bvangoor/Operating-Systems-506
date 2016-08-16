cmd_drivers/tty/synclink.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/tty/synclink.ko drivers/tty/synclink.o drivers/tty/synclink.mod.o
