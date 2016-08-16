cmd_crypto/blowfish_common.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o crypto/blowfish_common.ko crypto/blowfish_common.o crypto/blowfish_common.mod.o
