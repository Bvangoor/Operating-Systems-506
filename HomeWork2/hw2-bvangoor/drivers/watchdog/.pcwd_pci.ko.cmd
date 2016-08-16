cmd_drivers/watchdog/pcwd_pci.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/watchdog/pcwd_pci.ko drivers/watchdog/pcwd_pci.o drivers/watchdog/pcwd_pci.mod.o
