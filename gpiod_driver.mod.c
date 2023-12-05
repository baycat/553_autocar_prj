#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xfec63e19, "module_layout" },
	{ 0x43be31d6, "platform_driver_unregister" },
	{ 0xad64c90a, "__platform_driver_register" },
	{ 0xfe990052, "gpio_free" },
	{ 0x92d5838e, "request_threaded_irq" },
	{ 0x7998ad9c, "gpiod_to_irq" },
	{ 0x936bb658, "devm_gpiod_get" },
	{ 0x62f2b36, "gpiod_set_value" },
	{ 0x92da672c, "gpiod_get_value" },
	{ 0xc5850110, "printk" },
	{ 0xc1514a3b, "free_irq" },
};

MODULE_INFO(depends, "");

