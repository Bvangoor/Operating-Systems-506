cmd_drivers/net/ethernet/intel/igb/igb.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/net/ethernet/intel/igb/igb.ko drivers/net/ethernet/intel/igb/igb.o drivers/net/ethernet/intel/igb/igb.mod.o