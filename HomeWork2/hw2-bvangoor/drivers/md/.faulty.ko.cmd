cmd_drivers/md/faulty.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/md/faulty.ko drivers/md/faulty.o drivers/md/faulty.mod.o
