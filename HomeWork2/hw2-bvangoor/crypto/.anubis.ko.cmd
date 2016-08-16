cmd_crypto/anubis.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o crypto/anubis.ko crypto/anubis.o crypto/anubis.mod.o
