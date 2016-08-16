cmd_drivers/virtio/virtio_pci.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/virtio/virtio_pci.ko drivers/virtio/virtio_pci.o drivers/virtio/virtio_pci.mod.o
