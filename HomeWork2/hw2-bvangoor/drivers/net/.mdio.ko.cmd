cmd_drivers/net/mdio.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/net/mdio.ko drivers/net/mdio.o drivers/net/mdio.mod.o
