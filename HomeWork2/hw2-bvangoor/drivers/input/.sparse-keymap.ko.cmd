cmd_drivers/input/sparse-keymap.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/input/sparse-keymap.ko drivers/input/sparse-keymap.o drivers/input/sparse-keymap.mod.o
