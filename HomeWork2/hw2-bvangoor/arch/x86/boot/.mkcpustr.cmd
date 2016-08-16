cmd_arch/x86/boot/mkcpustr := gcc -Wp,-MD,arch/x86/boot/.mkcpustr.d -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer -std=gnu89   -I./tools/include -include include/generated/autoconf.h -D__EXPORTED_HEADERS__  -o arch/x86/boot/mkcpustr arch/x86/boot/mkcpustr.c  

source_arch/x86/boot/mkcpustr := arch/x86/boot/mkcpustr.c

deps_arch/x86/boot/mkcpustr := \
  /usr/include/stdio.h \
  /usr/include/features.h \
  /usr/include/sys/cdefs.h \
  /usr/include/bits/wordsize.h \
  /usr/include/gnu/stubs.h \
  /usr/include/gnu/stubs-32.h \
  /usr/lib/gcc/i386-redhat-linux/4.1.2/include/stddef.h \
  /usr/include/bits/types.h \
  /usr/include/bits/typesizes.h \
  /usr/include/libio.h \
  /usr/include/_G_config.h \
  /usr/include/wchar.h \
  /usr/include/bits/wchar.h \
  /usr/include/gconv.h \
  /usr/lib/gcc/i386-redhat-linux/4.1.2/include/stdarg.h \
  /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h \
  /usr/include/bits/stdio.h \
  arch/x86/boot/../include/asm/required-features.h \
    $(wildcard include/config/x86/minimum/cpu/family.h) \
    $(wildcard include/config/math/emulation.h) \
    $(wildcard include/config/x86/pae.h) \
    $(wildcard include/config/x86/64.h) \
    $(wildcard include/config/x86/cmpxchg64.h) \
    $(wildcard include/config/x86/cmov.h) \
    $(wildcard include/config/x86/use/3dnow.h) \
    $(wildcard include/config/x86/p6/nop.h) \
    $(wildcard include/config/matom.h) \
    $(wildcard include/config/paravirt.h) \
  arch/x86/boot/../include/asm/disabled-features.h \
    $(wildcard include/config/x86/intel/mpx.h) \
  arch/x86/boot/../include/asm/cpufeature.h \
    $(wildcard include/config/x86/feature/names.h) \
    $(wildcard include/config/x86/debug/static/cpu/has.h) \
  arch/x86/boot/../kernel/cpu/capflags.c \

arch/x86/boot/mkcpustr: $(deps_arch/x86/boot/mkcpustr)

$(deps_arch/x86/boot/mkcpustr):
