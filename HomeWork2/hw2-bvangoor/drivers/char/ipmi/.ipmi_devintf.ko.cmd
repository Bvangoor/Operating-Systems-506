cmd_drivers/char/ipmi/ipmi_devintf.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/char/ipmi/ipmi_devintf.ko drivers/char/ipmi/ipmi_devintf.o drivers/char/ipmi/ipmi_devintf.mod.o
