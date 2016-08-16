cmd_drivers/net/phy/fixed_phy.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/net/phy/fixed_phy.ko drivers/net/phy/fixed_phy.o drivers/net/phy/fixed_phy.mod.o
