cmd_drivers/hwmon/hwmon.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/hwmon/hwmon.ko drivers/hwmon/hwmon.o drivers/hwmon/hwmon.mod.o
