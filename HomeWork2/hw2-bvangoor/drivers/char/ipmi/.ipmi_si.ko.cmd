cmd_drivers/char/ipmi/ipmi_si.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/char/ipmi/ipmi_si.ko drivers/char/ipmi/ipmi_si.o drivers/char/ipmi/ipmi_si.mod.o
