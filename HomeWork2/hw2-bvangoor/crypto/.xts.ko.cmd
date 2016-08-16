cmd_crypto/xts.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o crypto/xts.ko crypto/xts.o crypto/xts.mod.o
