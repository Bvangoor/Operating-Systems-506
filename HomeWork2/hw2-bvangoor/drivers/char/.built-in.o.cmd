cmd_drivers/char/built-in.o :=  ld -m elf_i386   -r -o drivers/char/built-in.o drivers/char/mem.o drivers/char/random.o drivers/char/misc.o drivers/char/raw.o drivers/char/hpet.o drivers/char/nvram.o drivers/char/hw_random/built-in.o drivers/char/agp/built-in.o drivers/char/pcmcia/built-in.o 