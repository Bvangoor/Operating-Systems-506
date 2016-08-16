cmd_drivers/watchdog/wdt_pci.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/watchdog/wdt_pci.ko drivers/watchdog/wdt_pci.o drivers/watchdog/wdt_pci.mod.o
