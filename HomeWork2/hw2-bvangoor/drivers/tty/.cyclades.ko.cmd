cmd_drivers/tty/cyclades.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/tty/cyclades.ko drivers/tty/cyclades.o drivers/tty/cyclades.mod.o
