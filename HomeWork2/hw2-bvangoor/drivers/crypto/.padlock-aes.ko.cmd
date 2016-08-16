cmd_drivers/crypto/padlock-aes.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o drivers/crypto/padlock-aes.ko drivers/crypto/padlock-aes.o drivers/crypto/padlock-aes.mod.o
