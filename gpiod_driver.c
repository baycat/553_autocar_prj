#include <linux/module.h>
#include <linux/of_device.h>
#include <linux/kernel.h>
#include <linux/gpio/consumer.h>
#include <linux/platform_device.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>

// LED and button pointer declarations
struct gpio_desc *led_gpios;
struct gpio_desc *button_gpios;

/** variable contains pin number o interrupt controller to which GPIO 6 is mapped
to */
unsigned int irq_number;

/**
* @brief Interrupt service routine is called, when interrupt is triggered
*/
static irq_handler_t gpio_irq_handler(unsigned int irq, void *dev_id, struct
pt_regs *regs) {
	// printing when button is pressed
	printk("handling... (button pressed!)\n");

	// get current value of LED and toggle to opposite value
	int led_val;
	led_val = gpiod_get_value(led_gpios);
	gpiod_set_value(led_gpios, !led_val);

	//print value of LED for sanity checking and exit
	printk("led_val %d\n", !led_val);
	return (irq_handler_t) IRQ_HANDLED;
}

/**
* @brief This function is called, when the module is loaded into the kernel
*/

static int led_probe(struct platform_device *pdev) {
	// printing when module is inserted
	printk("gpio_irq: Loading module... ");

	//get button and LED struct pointers
	button_gpios = devm_gpiod_get(&pdev->dev, "button", GPIOD_IN);
	led_gpios = devm_gpiod_get(&pdev->dev, "led", GPIOD_OUT_LOW);

	/* Setup the interrupt to correspond to the button*/
	irq_number = gpiod_to_irq(button_gpios);

	// interrupt error, also interrupt triggered on falling edge
	if(request_irq(irq_number, (irq_handler_t) gpio_irq_handler,

IRQF_TRIGGER_FALLING, "button_irq", NULL) != 0){
	printk("Error!\nCan not request interrupt nr.: %d\n", irq_number);
	gpio_free(led_gpios);
	return -1; // exit with error
	}

	// exit peacefully
	return 0;
}

// remove function
static int led_remove(struct platform_device *pdev)
{
	/*Free the irq and print a message */
	free_irq(irq_number, NULL);
	printk("it's removeddddd\n");
	return 0;
}

static struct of_device_id matchy_match[] = {
	{ .compatible= "opticalencoder", },
	{/* leave alone - keep this here (end node) */},
};

// platform driver object
static struct platform_driver adam_driver = {
	.probe = led_probe,
	.remove = led_remove,
	.driver = {
		.name = "The Rock: this name doesn't even matter",
		.owner = THIS_MODULE,
		.of_match_table = matchy_match,
	},
};

module_platform_driver(adam_driver);

MODULE_DESCRIPTION("424\'s finest");
MODULE_AUTHOR("GOAT");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:adam_driver");
