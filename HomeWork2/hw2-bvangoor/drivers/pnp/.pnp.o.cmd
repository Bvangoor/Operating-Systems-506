cmd_drivers/pnp/pnp.o := ld -m elf_i386   -r -o drivers/pnp/pnp.o drivers/pnp/core.o drivers/pnp/card.o drivers/pnp/driver.o drivers/pnp/resource.o drivers/pnp/manager.o drivers/pnp/support.o drivers/pnp/interface.o drivers/pnp/quirks.o drivers/pnp/system.o 
