cmd_crypto/deflate.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o crypto/deflate.ko crypto/deflate.o crypto/deflate.mod.o
