cmd_drivers/md/raid1.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/md/raid1.ko drivers/md/raid1.o drivers/md/raid1.mod.o
