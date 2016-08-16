cmd_crypto/twofish_generic.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o crypto/twofish_generic.ko crypto/twofish_generic.o crypto/twofish_generic.mod.o
