#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <string.h>

#include <zephyr/drivers/uart.h>
/*
 * Ensure that an overlay for USB serial has been defined.
 */
BUILD_ASSERT(DT_NODE_HAS_COMPAT(DT_CHOSEN(zephyr_console), zephyr_cdc_acm_uart),
	     "Console device is not ACM CDC UART device");

static const struct device *const uart_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_console));

// LED0 from device tree (built-in LED on nRF52840 DK)
#define LED0_NODE DT_ALIAS(led0)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

// Simple C++ class
class Led {
private:
    const struct gpio_dt_spec& spec_;
    bool state_;
    
public:
    Led(const struct gpio_dt_spec& spec) : spec_(spec), state_(false) {
        // Configure GPIO in constructor
        printk("LED construted\n");
        gpio_pin_configure_dt(&spec_, GPIO_OUTPUT_INACTIVE);
    }
    
    ~Led(){
        gpio_pin_configure_dt(&spec_, GPIO_DISCONNECTED);
        printk("LED destructed\n");
    }

    void on() {
        // printk("Turning LED on\n");
        gpio_pin_set_dt(&spec_, 1);
        state_ = true;
    }
    
    void off() {
        // printk("Turning LED off\n");
        gpio_pin_set_dt(&spec_, 0);
        state_ = false;
    }
    
    void toggle() {
        state_ = !state_;
        if (state_) {
            on();
        } else {
            off();
        }
    }
};

int main(void) {
    // Check if LED device is ready
    if (!gpio_is_ready_dt(&led)) {
        return -1;
    }

    k_msleep(2500);
    printk("Hello from USB Serial...\n");

    // Create LED object - constructor configures pin
    {
        Led status_led(led);
        status_led.on();
        k_msleep(1000);
        status_led.off();
        k_msleep(500);
        status_led.toggle();
    }
    
    while (1) {
        k_msleep(500);
    }
    
    return 0;
}