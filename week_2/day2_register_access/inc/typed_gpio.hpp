#ifndef TYPED_GPIO_HPP
#define TYPED_GPIO_HPP
#include "gpio_registers.hpp"
#include <zephyr/sys/printk.h>

template<uint32_t Pin>
class TypedGPIO {
public:
    static_assert(Pin < 32, "Pin number must be between 0 and 31");

    static void configure_output(){
        GPIO_P0::DIRSET_REG::write(1U << Pin);
    }

    static void configure_input(){
        GPIO_P0::DIRCLR_REG::write(1U << Pin);
    }

    static void set_high(){
        GPIO_P0::OUTSET_REG::write(1U << Pin);
    }

    static void set_low(){
        GPIO_P0::OUTCLR_REG::write(1U << Pin);
    }

    static void toggle() {
        if (GPIO_P0::OUT_REG::is_bit_set(Pin)) {
            set_low();
        } else {
            set_high();
        }
    }
    
    static bool read() {
        return GPIO_P0::IN_REG::is_bit_set(Pin);
    }
};


#endif // TYPED_GPIO_HPP