cmd_arch/x86/kernel/msr.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds   -o arch/x86/kernel/msr.ko arch/x86/kernel/msr.o arch/x86/kernel/msr.mod.o
