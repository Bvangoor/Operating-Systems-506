cmd_drivers/md/raid0.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/md/raid0.ko drivers/md/raid0.o drivers/md/raid0.mod.o
