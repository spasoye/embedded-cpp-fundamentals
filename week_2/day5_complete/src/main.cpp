#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include "gpio_pin.hpp"

using red_led = GpioPin<15>;

int main(void){
    red_led::configure_output();
    printk("Blinkig LED three times...\n");

    for (uint8_t cnt = 0; cnt < 3; cnt++){
        red_led::set_high();
        k_msleep(500);
        red_led::set_low();
        k_msleep(500);
    }

    printk("Done!\n");

    while (1) {
        k_msleep(1000);
    }
}

