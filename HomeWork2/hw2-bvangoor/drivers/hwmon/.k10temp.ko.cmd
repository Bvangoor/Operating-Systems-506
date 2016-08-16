cmd_drivers/hwmon/k10temp.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/hwmon/k10temp.ko drivers/hwmon/k10temp.o drivers/hwmon/k10temp.mod.o
