cmd_fs/cachefiles/cachefiles.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o fs/cachefiles/cachefiles.ko fs/cachefiles/cachefiles.o fs/cachefiles/cachefiles.mod.o
