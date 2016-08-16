#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

MODULE_INFO(intree, "Y");

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("pcmcia:m016Cc0081f*fn*pfn00pa*pb*pc*pd*");
MODULE_ALIAS("pcmcia:m018Ac0301f*fn*pfn*pa*pb*pc*pd*");
MODULE_ALIAS("pcmcia:m01BFc2328f*fn*pfn*pa*pb*pc*pd*");
MODULE_ALIAS("pcmcia:m026Fc0301f*fn*pfn*pa*pb*pc*pd*");
MODULE_ALIAS("pcmcia:m026Fc0303f*fn*pfn*pa*pb*pc*pd*");
MODULE_ALIAS("pcmcia:m026Fc0309f*fn*pfn*pa*pb*pc*pd*");
MODULE_ALIAS("pcmcia:m0274c1106f*fn*pfn*pa*pb*pc*pd*");
MODULE_ALIAS("pcmcia:m8A01cC1ABf*fn*pfn*pa*pb*pc*pd*");
MODULE_ALIAS("pcmcia:m021Bc0202f*fn*pfn*pa*pb*pc*pd*");
MODULE_ALIAS("pcmcia:mFFFFc1090f*fn*pfn*pa*pb*pc*pd*");
MODULE_ALIAS("pcmcia:m*c*f*fn*pfn*pa49B020A7pb119CC9FCpc*pd*");
MODULE_ALIAS("pcmcia:m*c*f*fn*pfn*paB4BE14E3pb9A12EB6Apc*pdAB9BE5EF*");
MODULE_ALIAS("pcmcia:m*c*f*fn*pfn*pa0959823BpbAB9BE5EFpc*pd*");
MODULE_ALIAS("pcmcia:m*c*f*fn*pfn*pa552AB682pbBC3B87E1pc*pd*");
MODULE_ALIAS("pcmcia:m*c*f*fn*pfn*pa00FA7BC8pb00E990CCpc*pd*");
MODULE_ALIAS("pcmcia:m*c*f*fn*pfn*paBC477DDEpb78C5F40Bpc*pd*");
MODULE_ALIAS("pcmcia:m*c*f*fn*pfn*pa5261440Fpb436768C5pc*pd*");
MODULE_ALIAS("pcmcia:m*c*f*fn*pfn*pa5261440Fpb730DF72Epc*pd*");
MODULE_ALIAS("pcmcia:m*c*f*fn*pfn*pa5261440Fpb3ABBD061pc*pd*");
MODULE_ALIAS("pcmcia:m*c*f*fn*pfn*pa55632FD5pb66BC2A90pc*pd*");
MODULE_ALIAS("pcmcia:m*c*f*fn*pfn*pa547E66DCpb233ADAC2pc*pd*");
MODULE_ALIAS("pcmcia:m*c*f*fn*pfn*pa0733CC81pb232019A8pc*pd*");
MODULE_ALIAS("pcmcia:m*c*f*fn*pfn*pa481E0094pbF91AF609pc*pd*");
MODULE_ALIAS("pcmcia:m*c*f*fn*pfn*pa9AA79DC3pb40FAD875pc*pd*");
MODULE_ALIAS("pcmcia:m*c*f*fn*pfn*pa281F1C5Dpb7C2ADD04pc*pd*");
MODULE_ALIAS("pcmcia:m*c*f*fn*pfn*pa281F1C5Dpb7EF26116pc*pd*");
MODULE_ALIAS("pcmcia:m*c*f*fn*pfn*pa281F1C5Dpb2E272058pc*pd*");
MODULE_ALIAS("pcmcia:m*c*f*fn*pfn*pa820A67B6pb*pc*pdAB9BE5EF*");
