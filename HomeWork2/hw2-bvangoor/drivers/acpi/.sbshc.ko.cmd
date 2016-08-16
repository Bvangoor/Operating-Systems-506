cmd_drivers/acpi/sbshc.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/acpi/sbshc.ko drivers/acpi/sbshc.o drivers/acpi/sbshc.mod.o
