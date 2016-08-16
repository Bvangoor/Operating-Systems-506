cmd_drivers/watchdog/ibmasr.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/watchdog/ibmasr.ko drivers/watchdog/ibmasr.o drivers/watchdog/ibmasr.mod.o
