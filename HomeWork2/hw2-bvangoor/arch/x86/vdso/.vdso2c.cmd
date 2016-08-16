cmd_arch/x86/vdso/vdso2c := gcc -Wp,-MD,arch/x86/vdso/.vdso2c.d -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer -std=gnu89   -I./tools/include -I./include/uapi -I./arch/x86/include/uapi  -o arch/x86/vdso/vdso2c arch/x86/vdso/vdso2c.c  

source_arch/x86/vdso/vdso2c := arch/x86/vdso/vdso2c.c

deps_arch/x86/vdso/vdso2c := \
  /usr/include/inttypes.h \
  /usr/include/features.h \
  /usr/include/sys/cdefs.h \
  /usr/include/bits/wordsize.h \
  /usr/include/gnu/stubs.h \
  /usr/include/gnu/stubs-32.h \
  /usr/include/stdint.h \
  /usr/include/bits/wchar.h \
  /usr/include/unistd.h \
  /usr/include/bits/posix_opt.h \
  /usr/include/bits/types.h \
  /usr/lib/gcc/i386-redhat-linux/4.1.2/include/stddef.h \
  /usr/include/bits/typesizes.h \
  /usr/include/bits/confname.h \
  /usr/include/getopt.h \
  /usr/lib/gcc/i386-redhat-linux/4.1.2/include/stdarg.h \
  /usr/include/stdlib.h \
  /usr/include/sys/types.h \
  /usr/include/time.h \
  /usr/include/endian.h \
  /usr/include/bits/endian.h \
  /usr/include/sys/select.h \
  /usr/include/bits/select.h \
  /usr/include/bits/sigset.h \
  /usr/include/bits/time.h \
  /usr/include/sys/sysmacros.h \
  /usr/include/bits/pthreadtypes.h \
  /usr/include/alloca.h \
  /usr/include/stdio.h \
  /usr/include/libio.h \
  /usr/include/_G_config.h \
  /usr/include/wchar.h \
  /usr/include/gconv.h \
  /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h \
  /usr/include/bits/stdio.h \
  /usr/include/string.h \
  /usr/include/bits/string.h \
  /usr/include/bits/string2.h \
  /usr/include/fcntl.h \
  /usr/include/bits/fcntl.h \
  /usr/include/err.h \
  /usr/include/sys/mman.h \
  /usr/include/bits/mman.h \
  tools/include/tools/le_byteshift.h \
  include/uapi/linux/elf.h \
  tools/include/linux/types.h \
  /usr/lib/gcc/i386-redhat-linux/4.1.2/include/stdbool.h \
  arch/x86/include/uapi/asm/types.h \
  include/uapi/asm-generic/types.h \
  include/uapi/asm-generic/int-ll64.h \
  arch/x86/include/uapi/asm/bitsperlong.h \
  include/uapi/asm-generic/bitsperlong.h \
    $(wildcard include/config/64bit.h) \
  include/uapi/linux/elf-em.h \
  arch/x86/vdso/vdso2c.h \

arch/x86/vdso/vdso2c: $(deps_arch/x86/vdso/vdso2c)

$(deps_arch/x86/vdso/vdso2c):
