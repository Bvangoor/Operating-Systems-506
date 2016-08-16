cmd_drivers/acpi/button.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/acpi/button.ko drivers/acpi/button.o drivers/acpi/button.mod.o
