cmd_fs/fscache/fscache.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o fs/fscache/fscache.ko fs/fscache/fscache.o fs/fscache/fscache.mod.o
