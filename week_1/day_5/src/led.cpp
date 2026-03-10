#include "led.hpp"
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

Led::Led(const struct gpio_dt_spec& spec) : spec_(spec), state_(false) {
        // Configure GPIO in constructor
        printk("LED construted\n");
        gpio_pin_configure_dt(&spec_, GPIO_OUTPUT_INACTIVE);
    }
    
Led::~Led(){
    gpio_pin_configure_dt(&spec_, GPIO_DISCONNECTED);
    printk("LED destructed\n");
}

void Led::on() {
    // printk("Turning LED on\n");
    gpio_pin_set_dt(&spec_, 1);
    state_ = true;
}

void Led::off() {
    // printk("Turning LED off\n");
    gpio_pin_set_dt(&spec_, 0);
    state_ = false;
}

void Led::toggle() {
    state_ = !state_;
    
    if (state_) {
        on();
    } else {
        off();
    }
}