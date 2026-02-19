#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <zephyr/drivers/gpio.h>

class Button {
public:
    Button(const struct gpio_dt_spec& spec);
    ~Button();
    
    bool is_pressed() const;

private:
    const struct gpio_dt_spec& spec_;
};

#endif