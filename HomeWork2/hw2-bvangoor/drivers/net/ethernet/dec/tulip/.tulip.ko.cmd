cmd_drivers/net/ethernet/dec/tulip/tulip.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/net/ethernet/dec/tulip/tulip.ko drivers/net/ethernet/dec/tulip/tulip.o drivers/net/ethernet/dec/tulip/tulip.mod.o