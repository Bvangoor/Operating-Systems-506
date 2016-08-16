cmd_crypto/async_tx/async_pq.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o crypto/async_tx/async_pq.ko crypto/async_tx/async_pq.o crypto/async_tx/async_pq.mod.o
