cmd_drivers/acpi/sbs.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/acpi/sbs.ko drivers/acpi/sbs.o drivers/acpi/sbs.mod.o
