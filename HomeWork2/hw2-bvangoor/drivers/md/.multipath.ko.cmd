cmd_drivers/md/multipath.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/md/multipath.ko drivers/md/multipath.o drivers/md/multipath.mod.o
