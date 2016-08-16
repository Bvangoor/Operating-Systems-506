cmd_drivers/tty/n_hdlc.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/tty/n_hdlc.ko drivers/tty/n_hdlc.o drivers/tty/n_hdlc.mod.o
