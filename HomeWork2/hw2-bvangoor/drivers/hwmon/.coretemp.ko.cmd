cmd_drivers/hwmon/coretemp.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/hwmon/coretemp.ko drivers/hwmon/coretemp.o drivers/hwmon/coretemp.mod.o
