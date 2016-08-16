cmd_drivers/md/dm-mod.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/md/dm-mod.ko drivers/md/dm-mod.o drivers/md/dm-mod.mod.o
