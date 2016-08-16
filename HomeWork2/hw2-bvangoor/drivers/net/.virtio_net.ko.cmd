cmd_drivers/net/virtio_net.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/net/virtio_net.ko drivers/net/virtio_net.o drivers/net/virtio_net.mod.o
