cmd_drivers/watchdog/w83627hf_wdt.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/watchdog/w83627hf_wdt.ko drivers/watchdog/w83627hf_wdt.o drivers/watchdog/w83627hf_wdt.mod.o
