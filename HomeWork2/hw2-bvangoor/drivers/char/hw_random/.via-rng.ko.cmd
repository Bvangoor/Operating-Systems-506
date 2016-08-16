cmd_drivers/char/hw_random/via-rng.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/char/hw_random/via-rng.ko drivers/char/hw_random/via-rng.o drivers/char/hw_random/via-rng.mod.o
