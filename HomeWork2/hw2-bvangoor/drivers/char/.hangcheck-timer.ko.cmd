cmd_drivers/char/hangcheck-timer.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/char/hangcheck-timer.ko drivers/char/hangcheck-timer.o drivers/char/hangcheck-timer.mod.o
