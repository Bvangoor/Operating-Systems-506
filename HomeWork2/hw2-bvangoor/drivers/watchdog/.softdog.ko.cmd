cmd_drivers/watchdog/softdog.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/watchdog/softdog.ko drivers/watchdog/softdog.o drivers/watchdog/softdog.mod.o
