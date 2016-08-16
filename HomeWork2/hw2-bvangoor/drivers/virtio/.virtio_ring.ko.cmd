cmd_drivers/virtio/virtio_ring.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/virtio/virtio_ring.ko drivers/virtio/virtio_ring.o drivers/virtio/virtio_ring.mod.o
