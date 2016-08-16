cmd_crypto/wp512.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o crypto/wp512.ko crypto/wp512.o crypto/wp512.mod.o
