cmd_drivers/acpi/video.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/acpi/video.ko drivers/acpi/video.o drivers/acpi/video.mod.o
