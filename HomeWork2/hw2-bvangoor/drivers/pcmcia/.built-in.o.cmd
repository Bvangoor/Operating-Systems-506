cmd_drivers/pcmcia/built-in.o :=  ld -m elf_i386   -r -o drivers/pcmcia/built-in.o drivers/pcmcia/pcmcia_core.o drivers/pcmcia/pcmcia.o drivers/pcmcia/pcmcia_rsrc.o drivers/pcmcia/yenta_socket.o 
