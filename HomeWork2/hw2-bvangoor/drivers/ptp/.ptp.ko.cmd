cmd_drivers/ptp/ptp.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/ptp/ptp.ko drivers/ptp/ptp.o drivers/ptp/ptp.mod.o
