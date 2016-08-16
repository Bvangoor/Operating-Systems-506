cmd_crypto/gcm.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o crypto/gcm.ko crypto/gcm.o crypto/gcm.mod.o
