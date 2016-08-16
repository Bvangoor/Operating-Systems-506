cmd_drivers/cpufreq/acpi-cpufreq.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/cpufreq/acpi-cpufreq.ko drivers/cpufreq/acpi-cpufreq.o drivers/cpufreq/acpi-cpufreq.mod.o
