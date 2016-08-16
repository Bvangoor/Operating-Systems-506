cmd_drivers/acpi/ac.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/acpi/ac.ko drivers/acpi/ac.o drivers/acpi/ac.mod.o
