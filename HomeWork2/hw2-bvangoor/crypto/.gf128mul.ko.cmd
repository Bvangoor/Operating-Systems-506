cmd_crypto/gf128mul.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o crypto/gf128mul.ko crypto/gf128mul.o crypto/gf128mul.mod.o
