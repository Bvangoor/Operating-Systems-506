cmd_crypto/ghash-generic.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o crypto/ghash-generic.ko crypto/ghash-generic.o crypto/ghash-generic.mod.o
