cmd_fs/wrapfs/wrapfs.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o fs/wrapfs/wrapfs.ko fs/wrapfs/wrapfs.o fs/wrapfs/wrapfs.mod.o
