cmd_drivers/watchdog/machzwd.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/watchdog/machzwd.ko drivers/watchdog/machzwd.o drivers/watchdog/machzwd.mod.o
