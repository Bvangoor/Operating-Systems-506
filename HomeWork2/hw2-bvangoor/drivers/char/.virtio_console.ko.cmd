cmd_drivers/char/virtio_console.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/char/virtio_console.ko drivers/char/virtio_console.o drivers/char/virtio_console.mod.o
