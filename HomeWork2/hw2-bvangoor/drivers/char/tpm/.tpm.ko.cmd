cmd_drivers/char/tpm/tpm.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/char/tpm/tpm.ko drivers/char/tpm/tpm.o drivers/char/tpm/tpm.mod.o
