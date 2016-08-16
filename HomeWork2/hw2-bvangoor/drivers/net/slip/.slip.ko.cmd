cmd_drivers/net/slip/slip.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/net/slip/slip.ko drivers/net/slip/slip.o drivers/net/slip/slip.mod.o
