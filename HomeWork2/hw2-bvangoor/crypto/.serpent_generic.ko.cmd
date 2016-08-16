cmd_crypto/serpent_generic.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o crypto/serpent_generic.ko crypto/serpent_generic.o crypto/serpent_generic.mod.o
