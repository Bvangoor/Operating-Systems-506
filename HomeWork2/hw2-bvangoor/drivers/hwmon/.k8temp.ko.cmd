cmd_drivers/hwmon/k8temp.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/hwmon/k8temp.ko drivers/hwmon/k8temp.o drivers/hwmon/k8temp.mod.o
