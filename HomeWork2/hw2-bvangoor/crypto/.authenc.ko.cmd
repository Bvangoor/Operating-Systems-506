cmd_crypto/authenc.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o crypto/authenc.ko crypto/authenc.o crypto/authenc.mod.o
