cmd_crypto/twofish_common.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o crypto/twofish_common.ko crypto/twofish_common.o crypto/twofish_common.mod.o
