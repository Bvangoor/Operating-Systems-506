cmd_drivers/net/bonding/bonding.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/net/bonding/bonding.ko drivers/net/bonding/bonding.o drivers/net/bonding/bonding.mod.o
