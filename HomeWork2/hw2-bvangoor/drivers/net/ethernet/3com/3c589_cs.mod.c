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

MODULE_ALIAS("pcmcia:m0101c0562f*fn00pfn*pa*pb*pc*pd*");
MODULE_ALIAS("pcmcia:m*c*f*fn00pfn*paF03E4E77pb*pc*pd*");
MODULE_ALIAS("pcmcia:m0101c0589f*fn*pfn*pa*pb*pc*pd*");
MODULE_ALIAS("pcmcia:m*c*f*fn*pfn*pa58D93FC4pb992C2202pc*pd*");
MODULE_ALIAS("pcmcia:m0101c0035f*fn00pfn*pa*pb*pc*pd*");
MODULE_ALIAS("pcmcia:m0101c003Df*fn00pfn*pa*pb*pc*pd*");
