cmd_crypto/async_tx/async_tx.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o crypto/async_tx/async_tx.ko crypto/async_tx/async_tx.o crypto/async_tx/async_tx.mod.o
