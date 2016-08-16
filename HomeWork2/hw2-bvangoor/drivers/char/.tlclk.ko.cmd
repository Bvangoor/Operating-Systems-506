cmd_drivers/char/tlclk.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/char/tlclk.ko drivers/char/tlclk.o drivers/char/tlclk.mod.o
