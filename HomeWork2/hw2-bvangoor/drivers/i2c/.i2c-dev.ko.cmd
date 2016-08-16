cmd_drivers/i2c/i2c-dev.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/i2c/i2c-dev.ko drivers/i2c/i2c-dev.o drivers/i2c/i2c-dev.mod.o
