cmd_arch/x86/lib/misc.o := gcc -Wp,-MD,arch/x86/lib/.misc.o.d  -nostdinc -isystem /usr/lib/gcc/i386-redhat-linux/4.1.2/include -I./arch/x86/include -Iarch/x86/include/generated/uapi -Iarch/x86/include/generated  -Iinclude -I./arch/x86/include/uapi -Iarch/x86/include/generated/uapi -I./include/uapi -Iinclude/generated/uapi -include ./include/linux/kconfig.h -D__KERNEL__ -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -std=gnu89 -m32 -msoft-float -mregparm=3 -freg-struct-return -fno-pic -mpreferred-stack-boundary=2 -march=i686 -mtune=generic -Wa,-mtune=generic32 -ffreestanding -DCONFIG_AS_CFI=1 -DCONFIG_AS_CFI_SIGNAL_FRAME=1 -DCONFIG_AS_SSSE3=1 -DCONFIG_AS_CRC32=1 -pipe -Wno-sign-compare -fno-asynchronous-unwind-tables -mno-sse -mno-mmx -mno-sse2 -mno-3dnow -fno-delete-null-pointer-checks -Os -fno-stack-protector -fomit-frame-pointer -g -Wdeclaration-after-statement -Wno-pointer-sign    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(misc)"  -D"KBUILD_MODNAME=KBUILD_STR(misc)" -c -o arch/x86/lib/misc.o arch/x86/lib/misc.c

source_arch/x86/lib/misc.o := arch/x86/lib/misc.c

deps_arch/x86/lib/misc.o := \

arch/x86/lib/misc.o: $(deps_arch/x86/lib/misc.o)

$(deps_arch/x86/lib/misc.o):
