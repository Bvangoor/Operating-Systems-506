cmd_drivers/net/ethernet/nvidia/forcedeth.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/net/ethernet/nvidia/forcedeth.ko drivers/net/ethernet/nvidia/forcedeth.o drivers/net/ethernet/nvidia/forcedeth.mod.o