cmd_arch/x86/boot/compressed/vmlinux := ld -m elf_i386   -T arch/x86/boot/compressed/vmlinux.lds arch/x86/boot/compressed/head_32.o arch/x86/boot/compressed/misc.o arch/x86/boot/compressed/string.o arch/x86/boot/compressed/cmdline.o arch/x86/boot/compressed/piggy.o arch/x86/boot/compressed/cpuflags.o arch/x86/boot/compressed/early_serial_console.o -o arch/x86/boot/compressed/vmlinux