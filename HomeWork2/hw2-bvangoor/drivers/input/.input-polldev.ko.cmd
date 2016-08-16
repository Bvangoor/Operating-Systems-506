cmd_drivers/input/input-polldev.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/input/input-polldev.ko drivers/input/input-polldev.o drivers/input/input-polldev.mod.o
