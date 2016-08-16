cmd_crypto/crypto_null.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o crypto/crypto_null.ko crypto/crypto_null.o crypto/crypto_null.mod.o
