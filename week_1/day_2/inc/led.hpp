#ifndef LED_HPP
#define LED_HPP

#include <zephyr/drivers/gpio.h>

class Led {
    private:
        const struct gpio_dt_spec& spec_;
        bool state_;

    public:
        Led(const struct gpio_dt_spec& spec);
        ~Led();
        void on();
        void off();
        void toggle();

};

#endif