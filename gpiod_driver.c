#include <linux/module.h>
#include <linux/of_device.h>
#include <linux/kernel.h>
#include <linux/gpio/consumer.h>
#include <linux/platform_device.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>

// LED and button pointer declarations
//struct gpio_desc *led_gpios;
struct gpio_desc *button_gpios;

/** variable contains pin number to interrupt controller: assigned to P8_03 on BBAI64 */
unsigned int irq_number;

// Time variables
ktime_t currTime;
ktime_t prevTime;
int diff; 

// print timing difference to a separate file
module_param(diff, int, S_IRUGO);

/**
* @brief Interrupt service routine is called, when interrupt is triggered
*/
static irq_handler_t gpio_irq_handler(unsigned int irq, void *dev_id, struct
pt_regs *regs) {
	// calculate timing difference between triggers for ESC
	currTime = ktime_get();
	int temp_time = ktime_to_ns(currTime - prevTime) / 1000000;

	// reject timing below 1ms
	if (temp > 1) {
		diff = temp;
	}

	// observe time difference and update time
	printk("timing difference of: %d\n", diff); 
	prevTime = currTime;

	// finish handling 
	return (irq_handler_t) IRQ_HANDLED;
}

/**
* @brief This function is called, when the module is loaded into the kernel
*/

static int led_probe(struct platform_device *pdev) {
	// printing when module is inserted
	printk("gpio_irq: Loading module... ");

	// get struct pointers
	button_gpios = devm_gpiod_get(&pdev->dev, "button", GPIOD_IN);

	// set up the interrupt to correspond to the encoder
	irq_number = gpiod_to_irq(button_gpios);

	// interrupt error, also interrupt triggered on falling edge
	if(request_irq(irq_number, (irq_handler_t) gpio_irq_handler, IRQF_TRIGGER_FALLING, "button_irq", NULL) != 0){
		printk("Error!\nCan not request interrupt nr.: %d\n", irq_number);
		return -1; // exit with error
	}

	// set up debouncing
	printk("debouncing...\n");
	gpiod_set_debounce(button_gpios, 1000000); // time in microseconds

	// exit peacefully
	printk("done\n");
	return 0;
}

// remove function
static int led_remove(struct platform_device *pdev)
{
	// free the irq and print a message
	free_irq(irq_number, NULL);
	printk("it's removeddddd\n");
	return 0;
}

static struct of_device_id matchy_match[] = {
	{ .compatible= "opticalencoder", }, // our driver is named opticalencoder
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
