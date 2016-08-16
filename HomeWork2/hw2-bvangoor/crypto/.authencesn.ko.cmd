cmd_crypto/authencesn.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o crypto/authencesn.ko crypto/authencesn.o crypto/authencesn.mod.o
