cmd_crypto/cast5_generic.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o crypto/cast5_generic.ko crypto/cast5_generic.o crypto/cast5_generic.mod.o
