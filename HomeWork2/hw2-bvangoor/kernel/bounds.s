	.file	"bounds.c"
# GNU C version 4.1.2 20080704 (Red Hat 4.1.2-55) (i386-redhat-linux)
#	compiled by GNU C version 4.1.2 20080704 (Red Hat 4.1.2-55).
# GGC heuristics: --param ggc-min-expand=64 --param ggc-min-heapsize=64250
# options passed:  -nostdinc -I./arch/x86/include
# -Iarch/x86/include/generated/uapi -Iarch/x86/include/generated -Iinclude
# -I./arch/x86/include/uapi -Iarch/x86/include/generated/uapi
# -I./include/uapi -Iinclude/generated/uapi -D__KERNEL__ -DCONFIG_AS_CFI=1
# -DCONFIG_AS_CFI_SIGNAL_FRAME=1 -DCONFIG_AS_SSSE3=1 -DCONFIG_AS_CRC32=1
# -DKBUILD_STR(s)=#s -DKBUILD_BASENAME=KBUILD_STR(bounds)
# -DKBUILD_MODNAME=KBUILD_STR(bounds) -isystem -include -MD -m32
# -msoft-float -mregparm=3 -mpreferred-stack-boundary=2 -march=i686
# -mtune=generic -mno-sse -mno-mmx -mno-sse2 -mno-3dnow -auxbase-strip -g
# -Os -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs
# -Werror-implicit-function-declaration -Wno-format-security
# -Wno-sign-compare -Wdeclaration-after-statement -Wno-pointer-sign
# -std=gnu89 -fno-strict-aliasing -fno-common -freg-struct-return -fno-pic
# -ffreestanding -fno-asynchronous-unwind-tables
# -fno-delete-null-pointer-checks -fno-stack-protector -fomit-frame-pointer
# -fverbose-asm
# options enabled:  -falign-loops -fargument-alias -fbranch-count-reg
# -fcaller-saves -fcprop-registers -fcrossjumping -fcse-follow-jumps
# -fcse-skip-blocks -fdefer-pop -fearly-inlining
# -feliminate-unused-debug-types -fexpensive-optimizations -ffunction-cse
# -fgcse -fgcse-lm -fguess-branch-probability -fident -fif-conversion
# -fif-conversion2 -finline-functions -finline-functions-called-once
# -fipa-pure-const -fipa-reference -fivopts -fkeep-static-consts
# -fleading-underscore -floop-optimize -floop-optimize2 -fmath-errno
# -fmerge-constants -fomit-frame-pointer -foptimize-register-move
# -foptimize-sibling-calls -fpeephole -fpeephole2 -freg-struct-return
# -fregmove -freorder-functions -frerun-cse-after-loop -frerun-loop-opt
# -fsched-interblock -fsched-spec -fsched-stalled-insns-dep
# -fschedule-insns2 -fshow-column -fsplit-ivs-in-unroller -fstrength-reduce
# -fthread-jumps -ftrapping-math -ftree-ccp -ftree-copy-prop
# -ftree-copyrename -ftree-dce -ftree-dominator-opts -ftree-dse -ftree-fre
# -ftree-loop-im -ftree-loop-ivcanon -ftree-loop-optimize -ftree-lrs
# -ftree-salias -ftree-sink -ftree-sra -ftree-store-ccp
# -ftree-store-copy-prop -ftree-ter -ftree-vect-loop-version -ftree-vrp
# -funit-at-a-time -fvar-tracking -fverbose-asm -fzero-initialized-in-bss
# -m32 -m96bit-long-double -malign-stringops -mfused-madd -mieee-fp
# -mno-fancy-math-387 -mno-red-zone -mpush-args -mtls-direct-seg-refs

	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.text
.Ltext0:
# Compiler executable checksum: 391ea76ef17128f7cf6721bdef1a3431

.globl foo
	.type	foo, @function
foo:
.LFB159:
	.file 1 "kernel/bounds.c"
	.loc 1 16 0
	.loc 1 18 0
#APP
	
->NR_PAGEFLAGS $22 __NR_PAGEFLAGS	#
	.loc 1 19 0
	
->MAX_NR_ZONES $4 __MAX_NR_ZONES	#
	.loc 1 23 0
	
->SPINLOCK_SIZE $0 sizeof(spinlock_t)	#
	.loc 1 25 0
#NO_APP
	ret
.LFE159:
	.size	foo, .-foo
	.section	.debug_frame,"",@progbits
.Lframe0:
	.long	.LECIE0-.LSCIE0
.LSCIE0:
	.long	0xffffffff
	.byte	0x1
	.string	""
	.uleb128 0x1
	.sleb128 -4
	.byte	0x8
	.byte	0xc
	.uleb128 0x4
	.uleb128 0x4
	.byte	0x88
	.uleb128 0x1
	.align 4
.LECIE0:
.LSFDE0:
	.long	.LEFDE0-.LASFDE0
.LASFDE0:
	.long	.Lframe0
	.long	.LFB159
	.long	.LFE159-.LFB159
	.align 4
.LEFDE0:
	.file 2 "./arch/x86/include/asm/page_types.h"
	.file 3 "include/linux/printk.h"
	.file 4 "include/linux/kernel.h"
	.text
.Letext0:
	.section	.debug_info
	.long	0x143
	.value	0x2
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.Ldebug_line0
	.long	.Letext0
	.long	.Ltext0
	.long	.LASF16
	.byte	0x1
	.long	.LASF17
	.long	.LASF18
	.uleb128 0x2
	.long	.LASF0
	.byte	0x1
	.byte	0x6
	.uleb128 0x2
	.long	.LASF1
	.byte	0x1
	.byte	0x8
	.uleb128 0x2
	.long	.LASF2
	.byte	0x2
	.byte	0x5
	.uleb128 0x2
	.long	.LASF3
	.byte	0x2
	.byte	0x7
	.uleb128 0x3
	.string	"int"
	.byte	0x4
	.byte	0x5
	.uleb128 0x2
	.long	.LASF4
	.byte	0x4
	.byte	0x7
	.uleb128 0x2
	.long	.LASF5
	.byte	0x8
	.byte	0x5
	.uleb128 0x2
	.long	.LASF6
	.byte	0x8
	.byte	0x7
	.uleb128 0x2
	.long	.LASF7
	.byte	0x4
	.byte	0x7
	.uleb128 0x2
	.long	.LASF4
	.byte	0x4
	.byte	0x7
	.uleb128 0x2
	.long	.LASF8
	.byte	0x1
	.byte	0x6
	.uleb128 0x2
	.long	.LASF9
	.byte	0x4
	.byte	0x5
	.uleb128 0x2
	.long	.LASF10
	.byte	0x1
	.byte	0x2
	.uleb128 0x4
	.byte	0x1
	.string	"foo"
	.byte	0x1
	.byte	0x10
	.byte	0x1
	.long	.LFB159
	.long	.LFE159
	.byte	0x2
	.byte	0x74
	.sleb128 4
	.uleb128 0x5
	.long	.LASF11
	.byte	0x2
	.byte	0x34
	.long	0x5d
	.byte	0x1
	.byte	0x1
	.uleb128 0x6
	.long	0xac
	.long	0x41
	.uleb128 0x7
	.byte	0x0
	.uleb128 0x5
	.long	.LASF12
	.byte	0x3
	.byte	0x2c
	.long	0xa1
	.byte	0x1
	.byte	0x1
	.uleb128 0x8
	.long	.LASF13
	.byte	0x4
	.value	0x1a7
	.long	0x41
	.byte	0x1
	.byte	0x1
	.uleb128 0x6
	.long	0xd2
	.long	0x6b
	.uleb128 0x7
	.byte	0x0
	.uleb128 0x8
	.long	.LASF14
	.byte	0x4
	.value	0x1dc
	.long	0xe0
	.byte	0x1
	.byte	0x1
	.uleb128 0x9
	.long	0xc7
	.uleb128 0x8
	.long	.LASF15
	.byte	0x4
	.value	0x1e7
	.long	0xf3
	.byte	0x1
	.byte	0x1
	.uleb128 0x9
	.long	0xc7
	.uleb128 0x5
	.long	.LASF11
	.byte	0x2
	.byte	0x34
	.long	0x5d
	.byte	0x1
	.byte	0x1
	.uleb128 0x5
	.long	.LASF12
	.byte	0x3
	.byte	0x2c
	.long	0xa1
	.byte	0x1
	.byte	0x1
	.uleb128 0x8
	.long	.LASF13
	.byte	0x4
	.value	0x1a7
	.long	0x41
	.byte	0x1
	.byte	0x1
	.uleb128 0x8
	.long	.LASF14
	.byte	0x4
	.value	0x1dc
	.long	0x12e
	.byte	0x1
	.byte	0x1
	.uleb128 0x9
	.long	0xc7
	.uleb128 0x8
	.long	.LASF15
	.byte	0x4
	.value	0x1e7
	.long	0x141
	.byte	0x1
	.byte	0x1
	.uleb128 0x9
	.long	0xc7
	.byte	0x0
	.section	.debug_abbrev
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x10
	.uleb128 0x6
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.byte	0x0
	.byte	0x0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x4
	.uleb128 0x2e
	.byte	0x0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x5
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0x0
	.byte	0x0
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x7
	.uleb128 0x21
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.uleb128 0x8
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0x0
	.byte	0x0
	.uleb128 0x9
	.uleb128 0x26
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.section	.debug_pubnames,"",@progbits
	.long	0x16
	.value	0x2
	.long	.Ldebug_info0
	.long	0x147
	.long	0x80
	.string	"foo"
	.long	0x0
	.section	.debug_aranges,"",@progbits
	.long	0x1c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x4
	.byte	0x0
	.value	0x0
	.value	0x0
	.long	.Ltext0
	.long	.Letext0-.Ltext0
	.long	0x0
	.long	0x0
	.section	.debug_str,"MS",@progbits,1
.LASF18:
	.string	"/usr/src/hw2-bvangoor"
.LASF15:
	.string	"hex_asc_upper"
.LASF13:
	.string	"panic_timeout"
.LASF6:
	.string	"long long unsigned int"
.LASF5:
	.string	"long long int"
.LASF0:
	.string	"signed char"
.LASF9:
	.string	"long int"
.LASF17:
	.string	"kernel/bounds.c"
.LASF4:
	.string	"unsigned int"
.LASF7:
	.string	"long unsigned int"
.LASF12:
	.string	"console_printk"
.LASF3:
	.string	"short unsigned int"
.LASF16:
	.string	"GNU C 4.1.2 20080704 (Red Hat 4.1.2-55)"
.LASF11:
	.string	"max_pfn_mapped"
.LASF10:
	.string	"_Bool"
.LASF2:
	.string	"short int"
.LASF8:
	.string	"char"
.LASF1:
	.string	"unsigned char"
.LASF14:
	.string	"hex_asc"
	.ident	"GCC: (GNU) 4.1.2 20080704 (Red Hat 4.1.2-55)"
	.section	.note.GNU-stack,"",@progbits
