cmd_crypto/blowfish_generic.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o crypto/blowfish_generic.ko crypto/blowfish_generic.o crypto/blowfish_generic.mod.o
