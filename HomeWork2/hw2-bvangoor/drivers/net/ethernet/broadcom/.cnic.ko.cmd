cmd_drivers/net/ethernet/broadcom/cnic.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/net/ethernet/broadcom/cnic.ko drivers/net/ethernet/broadcom/cnic.o drivers/net/ethernet/broadcom/cnic.mod.o