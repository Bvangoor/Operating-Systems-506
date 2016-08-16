cmd_lib/crc-itu-t.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o lib/crc-itu-t.ko lib/crc-itu-t.o lib/crc-itu-t.mod.o
