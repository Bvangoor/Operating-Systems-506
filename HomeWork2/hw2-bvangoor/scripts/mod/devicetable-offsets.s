	.file	"devicetable-offsets.c"
# GNU C version 4.1.2 20080704 (Red Hat 4.1.2-55) (i386-redhat-linux)
#	compiled by GNU C version 4.1.2 20080704 (Red Hat 4.1.2-55).
# GGC heuristics: --param ggc-min-expand=64 --param ggc-min-heapsize=64250
# options passed:  -nostdinc -I./arch/x86/include
# -Iarch/x86/include/generated/uapi -Iarch/x86/include/generated -Iinclude
# -I./arch/x86/include/uapi -Iarch/x86/include/generated/uapi
# -I./include/uapi -Iinclude/generated/uapi -D__KERNEL__ -DCONFIG_AS_CFI=1
# -DCONFIG_AS_CFI_SIGNAL_FRAME=1 -DCONFIG_AS_SSSE3=1 -DCONFIG_AS_CRC32=1
# -DKBUILD_STR(s)=#s -DKBUILD_BASENAME=KBUILD_STR(devicetable_offsets)
# -DKBUILD_MODNAME=KBUILD_STR(devicetable_offsets) -isystem -include -MD
# -m32 -msoft-float -mregparm=3 -mpreferred-stack-boundary=2 -march=i686
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

.globl main
	.type	main, @function
main:
.LFB15:
	.file 1 "scripts/mod/devicetable-offsets.c"
	.loc 1 9 0
	.loc 1 10 0
#APP
	
->SIZE_usb_device_id $24 sizeof(struct usb_device_id)	#
	.loc 1 11 0
	
->OFF_usb_device_id_match_flags $0 offsetof(struct usb_device_id, match_flags)	#
	.loc 1 12 0
	
->OFF_usb_device_id_idVendor $2 offsetof(struct usb_device_id, idVendor)	#
	.loc 1 13 0
	
->OFF_usb_device_id_idProduct $4 offsetof(struct usb_device_id, idProduct)	#
	.loc 1 14 0
	
->OFF_usb_device_id_bcdDevice_lo $6 offsetof(struct usb_device_id, bcdDevice_lo)	#
	.loc 1 15 0
	
->OFF_usb_device_id_bcdDevice_hi $8 offsetof(struct usb_device_id, bcdDevice_hi)	#
	.loc 1 16 0
	
->OFF_usb_device_id_bDeviceClass $10 offsetof(struct usb_device_id, bDeviceClass)	#
	.loc 1 17 0
	
->OFF_usb_device_id_bDeviceSubClass $11 offsetof(struct usb_device_id, bDeviceSubClass)	#
	.loc 1 18 0
	
->OFF_usb_device_id_bDeviceProtocol $12 offsetof(struct usb_device_id, bDeviceProtocol)	#
	.loc 1 19 0
	
->OFF_usb_device_id_bInterfaceClass $13 offsetof(struct usb_device_id, bInterfaceClass)	#
	.loc 1 20 0
	
->OFF_usb_device_id_bInterfaceSubClass $14 offsetof(struct usb_device_id, bInterfaceSubClass)	#
	.loc 1 21 0
	
->OFF_usb_device_id_bInterfaceProtocol $15 offsetof(struct usb_device_id, bInterfaceProtocol)	#
	.loc 1 22 0
	
->OFF_usb_device_id_bInterfaceNumber $16 offsetof(struct usb_device_id, bInterfaceNumber)	#
	.loc 1 24 0
	
->SIZE_hid_device_id $16 sizeof(struct hid_device_id)	#
	.loc 1 25 0
	
->OFF_hid_device_id_bus $0 offsetof(struct hid_device_id, bus)	#
	.loc 1 26 0
	
->OFF_hid_device_id_group $2 offsetof(struct hid_device_id, group)	#
	.loc 1 27 0
	
->OFF_hid_device_id_vendor $4 offsetof(struct hid_device_id, vendor)	#
	.loc 1 28 0
	
->OFF_hid_device_id_product $8 offsetof(struct hid_device_id, product)	#
	.loc 1 30 0
	
->SIZE_ieee1394_device_id $24 sizeof(struct ieee1394_device_id)	#
	.loc 1 31 0
	
->OFF_ieee1394_device_id_match_flags $0 offsetof(struct ieee1394_device_id, match_flags)	#
	.loc 1 32 0
	
->OFF_ieee1394_device_id_vendor_id $4 offsetof(struct ieee1394_device_id, vendor_id)	#
	.loc 1 33 0
	
->OFF_ieee1394_device_id_model_id $8 offsetof(struct ieee1394_device_id, model_id)	#
	.loc 1 34 0
	
->OFF_ieee1394_device_id_specifier_id $12 offsetof(struct ieee1394_device_id, specifier_id)	#
	.loc 1 35 0
	
->OFF_ieee1394_device_id_version $16 offsetof(struct ieee1394_device_id, version)	#
	.loc 1 37 0
	
->SIZE_pci_device_id $28 sizeof(struct pci_device_id)	#
	.loc 1 38 0
	
->OFF_pci_device_id_vendor $0 offsetof(struct pci_device_id, vendor)	#
	.loc 1 39 0
	
->OFF_pci_device_id_device $4 offsetof(struct pci_device_id, device)	#
	.loc 1 40 0
	
->OFF_pci_device_id_subvendor $8 offsetof(struct pci_device_id, subvendor)	#
	.loc 1 41 0
	
->OFF_pci_device_id_subdevice $12 offsetof(struct pci_device_id, subdevice)	#
	.loc 1 42 0
	
->OFF_pci_device_id_class $16 offsetof(struct pci_device_id, class)	#
	.loc 1 43 0
	
->OFF_pci_device_id_class_mask $20 offsetof(struct pci_device_id, class_mask)	#
	.loc 1 45 0
	
->SIZE_ccw_device_id $12 sizeof(struct ccw_device_id)	#
	.loc 1 46 0
	
->OFF_ccw_device_id_match_flags $0 offsetof(struct ccw_device_id, match_flags)	#
	.loc 1 47 0
	
->OFF_ccw_device_id_cu_type $2 offsetof(struct ccw_device_id, cu_type)	#
	.loc 1 48 0
	
->OFF_ccw_device_id_cu_model $6 offsetof(struct ccw_device_id, cu_model)	#
	.loc 1 49 0
	
->OFF_ccw_device_id_dev_type $4 offsetof(struct ccw_device_id, dev_type)	#
	.loc 1 50 0
	
->OFF_ccw_device_id_dev_model $7 offsetof(struct ccw_device_id, dev_model)	#
	.loc 1 52 0
	
->SIZE_ap_device_id $8 sizeof(struct ap_device_id)	#
	.loc 1 53 0
	
->OFF_ap_device_id_dev_type $2 offsetof(struct ap_device_id, dev_type)	#
	.loc 1 55 0
	
->SIZE_css_device_id $8 sizeof(struct css_device_id)	#
	.loc 1 56 0
	
->OFF_css_device_id_type $1 offsetof(struct css_device_id, type)	#
	.loc 1 58 0
	
->SIZE_serio_device_id $4 sizeof(struct serio_device_id)	#
	.loc 1 59 0
	
->OFF_serio_device_id_type $0 offsetof(struct serio_device_id, type)	#
	.loc 1 60 0
	
->OFF_serio_device_id_proto $3 offsetof(struct serio_device_id, proto)	#
	.loc 1 61 0
	
->OFF_serio_device_id_id $2 offsetof(struct serio_device_id, id)	#
	.loc 1 62 0
	
->OFF_serio_device_id_extra $1 offsetof(struct serio_device_id, extra)	#
	.loc 1 64 0
	
->SIZE_acpi_device_id $16 sizeof(struct acpi_device_id)	#
	.loc 1 65 0
	
->OFF_acpi_device_id_id $0 offsetof(struct acpi_device_id, id)	#
	.loc 1 67 0
	
->SIZE_pnp_device_id $12 sizeof(struct pnp_device_id)	#
	.loc 1 68 0
	
->OFF_pnp_device_id_id $0 offsetof(struct pnp_device_id, id)	#
	.loc 1 70 0
	
->SIZE_pnp_card_device_id $76 sizeof(struct pnp_card_device_id)	#
	.loc 1 71 0
	
->OFF_pnp_card_device_id_devs $12 offsetof(struct pnp_card_device_id, devs)	#
	.loc 1 73 0
	
->SIZE_pcmcia_device_id $52 sizeof(struct pcmcia_device_id)	#
	.loc 1 74 0
	
->OFF_pcmcia_device_id_match_flags $0 offsetof(struct pcmcia_device_id, match_flags)	#
	.loc 1 75 0
	
->OFF_pcmcia_device_id_manf_id $2 offsetof(struct pcmcia_device_id, manf_id)	#
	.loc 1 76 0
	
->OFF_pcmcia_device_id_card_id $4 offsetof(struct pcmcia_device_id, card_id)	#
	.loc 1 77 0
	
->OFF_pcmcia_device_id_func_id $6 offsetof(struct pcmcia_device_id, func_id)	#
	.loc 1 78 0
	
->OFF_pcmcia_device_id_function $7 offsetof(struct pcmcia_device_id, function)	#
	.loc 1 79 0
	
->OFF_pcmcia_device_id_device_no $8 offsetof(struct pcmcia_device_id, device_no)	#
	.loc 1 80 0
	
->OFF_pcmcia_device_id_prod_id_hash $12 offsetof(struct pcmcia_device_id, prod_id_hash)	#
	.loc 1 82 0
	
->SIZE_of_device_id $196 sizeof(struct of_device_id)	#
	.loc 1 83 0
	
->OFF_of_device_id_name $0 offsetof(struct of_device_id, name)	#
	.loc 1 84 0
	
->OFF_of_device_id_type $32 offsetof(struct of_device_id, type)	#
	.loc 1 85 0
	
->OFF_of_device_id_compatible $64 offsetof(struct of_device_id, compatible)	#
	.loc 1 87 0
	
->SIZE_vio_device_id $64 sizeof(struct vio_device_id)	#
	.loc 1 88 0
	
->OFF_vio_device_id_type $0 offsetof(struct vio_device_id, type)	#
	.loc 1 89 0
	
->OFF_vio_device_id_compat $32 offsetof(struct vio_device_id, compat)	#
	.loc 1 91 0
	
->SIZE_input_device_id $160 sizeof(struct input_device_id)	#
	.loc 1 92 0
	
->OFF_input_device_id_flags $0 offsetof(struct input_device_id, flags)	#
	.loc 1 93 0
	
->OFF_input_device_id_bustype $4 offsetof(struct input_device_id, bustype)	#
	.loc 1 94 0
	
->OFF_input_device_id_vendor $6 offsetof(struct input_device_id, vendor)	#
	.loc 1 95 0
	
->OFF_input_device_id_product $8 offsetof(struct input_device_id, product)	#
	.loc 1 96 0
	
->OFF_input_device_id_version $10 offsetof(struct input_device_id, version)	#
	.loc 1 97 0
	
->OFF_input_device_id_evbit $12 offsetof(struct input_device_id, evbit)	#
	.loc 1 98 0
	
->OFF_input_device_id_keybit $16 offsetof(struct input_device_id, keybit)	#
	.loc 1 99 0
	
->OFF_input_device_id_relbit $112 offsetof(struct input_device_id, relbit)	#
	.loc 1 100 0
	
->OFF_input_device_id_absbit $116 offsetof(struct input_device_id, absbit)	#
	.loc 1 101 0
	
->OFF_input_device_id_mscbit $124 offsetof(struct input_device_id, mscbit)	#
	.loc 1 102 0
	
->OFF_input_device_id_ledbit $128 offsetof(struct input_device_id, ledbit)	#
	.loc 1 103 0
	
->OFF_input_device_id_sndbit $132 offsetof(struct input_device_id, sndbit)	#
	.loc 1 104 0
	
->OFF_input_device_id_ffbit $136 offsetof(struct input_device_id, ffbit)	#
	.loc 1 105 0
	
->OFF_input_device_id_swbit $152 offsetof(struct input_device_id, swbit)	#
	.loc 1 107 0
	
->SIZE_eisa_device_id $12 sizeof(struct eisa_device_id)	#
	.loc 1 108 0
	
->OFF_eisa_device_id_sig $0 offsetof(struct eisa_device_id, sig)	#
	.loc 1 110 0
	
->SIZE_parisc_device_id $8 sizeof(struct parisc_device_id)	#
	.loc 1 111 0
	
->OFF_parisc_device_id_hw_type $0 offsetof(struct parisc_device_id, hw_type)	#
	.loc 1 112 0
	
->OFF_parisc_device_id_hversion $2 offsetof(struct parisc_device_id, hversion)	#
	.loc 1 113 0
	
->OFF_parisc_device_id_hversion_rev $1 offsetof(struct parisc_device_id, hversion_rev)	#
	.loc 1 114 0
	
->OFF_parisc_device_id_sversion $4 offsetof(struct parisc_device_id, sversion)	#
	.loc 1 116 0
	
->SIZE_sdio_device_id $12 sizeof(struct sdio_device_id)	#
	.loc 1 117 0
	
->OFF_sdio_device_id_class $0 offsetof(struct sdio_device_id, class)	#
	.loc 1 118 0
	
->OFF_sdio_device_id_vendor $2 offsetof(struct sdio_device_id, vendor)	#
	.loc 1 119 0
	
->OFF_sdio_device_id_device $4 offsetof(struct sdio_device_id, device)	#
	.loc 1 121 0
	
->SIZE_ssb_device_id $6 sizeof(struct ssb_device_id)	#
	.loc 1 122 0
	
->OFF_ssb_device_id_vendor $0 offsetof(struct ssb_device_id, vendor)	#
	.loc 1 123 0
	
->OFF_ssb_device_id_coreid $2 offsetof(struct ssb_device_id, coreid)	#
	.loc 1 124 0
	
->OFF_ssb_device_id_revision $4 offsetof(struct ssb_device_id, revision)	#
	.loc 1 126 0
	
->SIZE_bcma_device_id $6 sizeof(struct bcma_device_id)	#
	.loc 1 127 0
	
->OFF_bcma_device_id_manuf $0 offsetof(struct bcma_device_id, manuf)	#
	.loc 1 128 0
	
->OFF_bcma_device_id_id $2 offsetof(struct bcma_device_id, id)	#
	.loc 1 129 0
	
->OFF_bcma_device_id_rev $4 offsetof(struct bcma_device_id, rev)	#
	.loc 1 130 0
	
->OFF_bcma_device_id_class $5 offsetof(struct bcma_device_id, class)	#
	.loc 1 132 0
	
->SIZE_virtio_device_id $8 sizeof(struct virtio_device_id)	#
	.loc 1 133 0
	
->OFF_virtio_device_id_device $0 offsetof(struct virtio_device_id, device)	#
	.loc 1 134 0
	
->OFF_virtio_device_id_vendor $4 offsetof(struct virtio_device_id, vendor)	#
	.loc 1 136 0
	
->SIZE_hv_vmbus_device_id $20 sizeof(struct hv_vmbus_device_id)	#
	.loc 1 137 0
	
->OFF_hv_vmbus_device_id_guid $0 offsetof(struct hv_vmbus_device_id, guid)	#
	.loc 1 139 0
	
->SIZE_i2c_device_id $24 sizeof(struct i2c_device_id)	#
	.loc 1 140 0
	
->OFF_i2c_device_id_name $0 offsetof(struct i2c_device_id, name)	#
	.loc 1 142 0
	
->SIZE_spi_device_id $36 sizeof(struct spi_device_id)	#
	.loc 1 143 0
	
->OFF_spi_device_id_name $0 offsetof(struct spi_device_id, name)	#
	.loc 1 145 0
	
->SIZE_dmi_system_id $332 sizeof(struct dmi_system_id)	#
	.loc 1 146 0
	
->OFF_dmi_system_id_matches $8 offsetof(struct dmi_system_id, matches)	#
	.loc 1 148 0
	
->SIZE_platform_device_id $24 sizeof(struct platform_device_id)	#
	.loc 1 149 0
	
->OFF_platform_device_id_name $0 offsetof(struct platform_device_id, name)	#
	.loc 1 151 0
	
->SIZE_mdio_device_id $8 sizeof(struct mdio_device_id)	#
	.loc 1 152 0
	
->OFF_mdio_device_id_phy_id $0 offsetof(struct mdio_device_id, phy_id)	#
	.loc 1 153 0
	
->OFF_mdio_device_id_phy_id_mask $4 offsetof(struct mdio_device_id, phy_id_mask)	#
	.loc 1 155 0
	
->SIZE_zorro_device_id $8 sizeof(struct zorro_device_id)	#
	.loc 1 156 0
	
->OFF_zorro_device_id_id $0 offsetof(struct zorro_device_id, id)	#
	.loc 1 158 0
	
->SIZE_isapnp_device_id $12 sizeof(struct isapnp_device_id)	#
	.loc 1 159 0
	
->OFF_isapnp_device_id_vendor $4 offsetof(struct isapnp_device_id, vendor)	#
	.loc 1 160 0
	
->OFF_isapnp_device_id_function $6 offsetof(struct isapnp_device_id, function)	#
	.loc 1 162 0
	
->SIZE_ipack_device_id $12 sizeof(struct ipack_device_id)	#
	.loc 1 163 0
	
->OFF_ipack_device_id_format $0 offsetof(struct ipack_device_id, format)	#
	.loc 1 164 0
	
->OFF_ipack_device_id_vendor $4 offsetof(struct ipack_device_id, vendor)	#
	.loc 1 165 0
	
->OFF_ipack_device_id_device $8 offsetof(struct ipack_device_id, device)	#
	.loc 1 167 0
	
->SIZE_amba_id $12 sizeof(struct amba_id)	#
	.loc 1 168 0
	
->OFF_amba_id_id $0 offsetof(struct amba_id, id)	#
	.loc 1 169 0
	
->OFF_amba_id_mask $4 offsetof(struct amba_id, mask)	#
	.loc 1 171 0
	
->SIZE_x86_cpu_id $12 sizeof(struct x86_cpu_id)	#
	.loc 1 172 0
	
->OFF_x86_cpu_id_feature $6 offsetof(struct x86_cpu_id, feature)	#
	.loc 1 173 0
	
->OFF_x86_cpu_id_family $2 offsetof(struct x86_cpu_id, family)	#
	.loc 1 174 0
	
->OFF_x86_cpu_id_model $4 offsetof(struct x86_cpu_id, model)	#
	.loc 1 175 0
	
->OFF_x86_cpu_id_vendor $0 offsetof(struct x86_cpu_id, vendor)	#
	.loc 1 177 0
	
->SIZE_cpu_feature $2 sizeof(struct cpu_feature)	#
	.loc 1 178 0
	
->OFF_cpu_feature_feature $0 offsetof(struct cpu_feature, feature)	#
	.loc 1 180 0
	
->SIZE_mei_cl_device_id $36 sizeof(struct mei_cl_device_id)	#
	.loc 1 181 0
	
->OFF_mei_cl_device_id_name $0 offsetof(struct mei_cl_device_id, name)	#
	.loc 1 183 0
	
->SIZE_rio_device_id $8 sizeof(struct rio_device_id)	#
	.loc 1 184 0
	
->OFF_rio_device_id_did $0 offsetof(struct rio_device_id, did)	#
	.loc 1 185 0
	
->OFF_rio_device_id_vid $2 offsetof(struct rio_device_id, vid)	#
	.loc 1 186 0
	
->OFF_rio_device_id_asm_did $4 offsetof(struct rio_device_id, asm_did)	#
	.loc 1 187 0
	
->OFF_rio_device_id_asm_vid $6 offsetof(struct rio_device_id, asm_vid)	#
	.loc 1 190 0
#NO_APP
	xorl	%eax, %eax	# <result>
	ret
.LFE15:
	.size	main, .-main
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
	.long	.LFB15
	.long	.LFE15-.LFB15
	.align 4
.LEFDE0:
	.text
.Letext0:
	.section	.debug_info
	.long	0x95
	.value	0x2
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.Ldebug_line0
	.long	.Letext0
	.long	.Ltext0
	.long	.LASF11
	.byte	0x1
	.long	.LASF12
	.long	.LASF13
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
	.long	.LASF14
	.byte	0x1
	.byte	0x9
	.byte	0x1
	.long	0x41
	.long	.LFB15
	.long	.LFE15
	.byte	0x2
	.byte	0x74
	.sleb128 4
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
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.section	.debug_pubnames,"",@progbits
	.long	0x17
	.value	0x2
	.long	.Ldebug_info0
	.long	0x99
	.long	0x80
	.string	"main"
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
.LASF6:
	.string	"long long unsigned int"
.LASF5:
	.string	"long long int"
.LASF0:
	.string	"signed char"
.LASF9:
	.string	"long int"
.LASF14:
	.string	"main"
.LASF4:
	.string	"unsigned int"
.LASF7:
	.string	"long unsigned int"
.LASF11:
	.string	"GNU C 4.1.2 20080704 (Red Hat 4.1.2-55)"
.LASF13:
	.string	"/usr/src/hw2-bvangoor"
.LASF12:
	.string	"scripts/mod/devicetable-offsets.c"
.LASF10:
	.string	"_Bool"
.LASF2:
	.string	"short int"
.LASF8:
	.string	"char"
.LASF3:
	.string	"short unsigned int"
.LASF1:
	.string	"unsigned char"
	.ident	"GCC: (GNU) 4.1.2 20080704 (Red Hat 4.1.2-55)"
	.section	.note.GNU-stack,"",@progbits
