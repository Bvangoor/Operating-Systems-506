cmd_net/core/pktgen.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o net/core/pktgen.ko net/core/pktgen.o net/core/pktgen.mod.o
