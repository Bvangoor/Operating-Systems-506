cmd_drivers/net/dummy.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/net/dummy.ko drivers/net/dummy.o drivers/net/dummy.mod.o
