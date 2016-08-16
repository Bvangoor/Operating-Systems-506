cmd_crypto/cast_common.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o crypto/cast_common.ko crypto/cast_common.o crypto/cast_common.mod.o
