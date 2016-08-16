cmd_crypto/cmac.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o crypto/cmac.ko crypto/cmac.o crypto/cmac.mod.o
