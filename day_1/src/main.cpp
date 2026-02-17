#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

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
        gpio_pin_configure_dt(&spec_, GPIO_OUTPUT_INACTIVE);
    }
    
    void on() {
        gpio_pin_set_dt(&spec_, 1);
        state_ = true;
    }
    
    void off() {
        gpio_pin_set_dt(&spec_, 0);
        state_ = false;
    }
    
    void toggle() {
        state_ = !state_;
        gpio_pin_set_dt(&spec_, state_);
    }
};

int main(void) {
    // Check if LED device is ready
    if (!gpio_is_ready_dt(&led)) {
        return -1;
    }
    
    // Create LED object - constructor configures pin
    Led status_led(led);
    
    while (1) {
        status_led.toggle();
        k_msleep(200);
    }
    
    return 0;
}