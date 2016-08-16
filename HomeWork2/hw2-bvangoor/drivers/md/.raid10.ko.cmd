cmd_drivers/md/raid10.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/md/raid10.ko drivers/md/raid10.o drivers/md/raid10.mod.o
