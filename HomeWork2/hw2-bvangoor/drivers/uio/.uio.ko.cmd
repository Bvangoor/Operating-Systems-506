cmd_drivers/uio/uio.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/uio/uio.ko drivers/uio/uio.o drivers/uio/uio.mod.o
