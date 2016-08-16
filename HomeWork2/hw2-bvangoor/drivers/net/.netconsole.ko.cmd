cmd_drivers/net/netconsole.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/net/netconsole.ko drivers/net/netconsole.o drivers/net/netconsole.mod.o
