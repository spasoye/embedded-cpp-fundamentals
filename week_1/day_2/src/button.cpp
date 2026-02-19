#include "button.hpp"
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>

Button::Button(const struct gpio_dt_spec& spec) : spec_(spec){
    gpio_pin_configure_dt(&spec_, GPIO_INPUT);
    printk("Button constructed\n");
}

Button::~Button(){
    gpio_pin_configure_dt(&spec_, GPIO_DISCONNECTED);
    printk("Button destructed\n");
}

bool Button::is_pressed() const{
    return gpio_pin_get_dt(&spec_) == 0; 
}