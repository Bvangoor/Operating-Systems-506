cmd_crypto/xor.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o crypto/xor.ko crypto/xor.o crypto/xor.mod.o
