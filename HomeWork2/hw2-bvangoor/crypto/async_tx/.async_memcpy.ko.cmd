cmd_crypto/async_tx/async_memcpy.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o crypto/async_tx/async_memcpy.ko crypto/async_tx/async_memcpy.o crypto/async_tx/async_memcpy.mod.o
