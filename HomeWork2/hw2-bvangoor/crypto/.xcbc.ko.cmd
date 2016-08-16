cmd_crypto/xcbc.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o crypto/xcbc.ko crypto/xcbc.o crypto/xcbc.mod.o
