cmd_drivers/i2c/i2c-core.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/i2c/i2c-core.ko drivers/i2c/i2c-core.o drivers/i2c/i2c-core.mod.o
