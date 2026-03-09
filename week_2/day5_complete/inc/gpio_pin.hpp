#ifndef GPIO_PIN_HPP
#define GPIO_PIN_HPP

#include "gpio_port.hpp"

template<uint8_t Pin, typename Port = GpioP0>
class GpioPin {
private:
    static constexpr PinNumber pin_num_{Pin};

public:
    static_assert(Pin < 32, "Pin number must be 0-31");

    static void configure_output() {
        Port::configure_output(pin_num_);
    }

    static void configure_input() {
        Port::configure_input(pin_num_);
    }

    static void set_high() {
        Port::set_high(pin_num_);
    }

    static void set_low() {
        Port::set_low(pin_num_);
    }

    static void set(PinState state) {
        Port::set(pin_num_, state);
    }

    static void toggle() {
        Port::toggle(pin_num_);
    }

    static PinState read() {
        return Port::read(pin_num_);
    }

    static bool is_high() {
        return read() == PinState::high;
    }

    static bool is_low() {
        return read() == PinState::low;
    }
};

#endif