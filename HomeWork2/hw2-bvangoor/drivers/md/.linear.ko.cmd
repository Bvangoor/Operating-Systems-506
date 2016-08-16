cmd_drivers/md/linear.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/md/linear.ko drivers/md/linear.o drivers/md/linear.mod.o
