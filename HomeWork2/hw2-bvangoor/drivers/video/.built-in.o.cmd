cmd_drivers/video/built-in.o :=  ld -m elf_i386   -r -o drivers/video/built-in.o drivers/video/console/built-in.o drivers/video/backlight/built-in.o drivers/video/fbdev/built-in.o 
