cmd_drivers/tty/serial/jsm/jsm.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/tty/serial/jsm/jsm.ko drivers/tty/serial/jsm/jsm.o drivers/tty/serial/jsm/jsm.mod.o
