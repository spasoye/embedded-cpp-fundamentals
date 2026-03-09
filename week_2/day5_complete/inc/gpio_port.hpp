#ifndef GPIO_PORT_HPP
#define GPIO_PORT_HPP

#include "register.hpp"
#include "gpio_config.hpp"

template<uint32_t BaseAddr>
class GpioPort{
private:
    // nrf52840 registers offset
    static constexpr uint32_t OUT_OFFSET    = 0x504;
    static constexpr uint32_t OUTSET_OFFSET = 0x508;
    static constexpr uint32_t OUTCLR_OFFSET = 0x50C;
    static constexpr uint32_t IN_OFFSET     = 0x510;
    static constexpr uint32_t DIR_OFFSET    = 0x514;
    static constexpr uint32_t DIRSET_OFFSET = 0x518;
    static constexpr uint32_t DIRCLR_OFFSET = 0x51C;

    // Create Register types for each hardware register
    using OutReg     = Register<BaseAddr + OUT_OFFSET>;
    using OutSetReg  = Register<BaseAddr + OUTSET_OFFSET>;
    using OutClrReg  = Register<BaseAddr + OUTCLR_OFFSET>;
    using InReg      = Register<BaseAddr + IN_OFFSET>;
    using DirReg     = Register<BaseAddr + DIR_OFFSET>;
    using DirSetReg  = Register<BaseAddr + DIRSET_OFFSET>;
    using DirClrReg  = Register<BaseAddr + DIRCLR_OFFSET>;

public:
    static void configure_output(PinNumber pin) {
        DirSetReg::write(1U << pin.value());
    }

    static void configure_input(PinNumber pin) {
        DirClrReg::write(1U << pin.value());
    }

    static void set(PinNumber pin, PinState state) {
        if (state == PinState::high) {
            OutSetReg::write(1U << pin.value());
        }
        else {
            OutClrReg::write(1U << pin.value());
        }
    }

    static void set_high(PinNumber pin){
        OutSetReg::write(1U << pin.value());
    }

    static void set_low(PinNumber pin){
        OutClrReg::write(1U << pin.value());
    }

    static PinState read(PinNumber pin){
        return InReg::is_bit_set(pin.value()) ? PinState::high : PinState::low;
    }

    static void toggle(PinNumber pin){
        if (OutReg::is_bit_set(pin.value())) {
            OutClrReg::write(1U << pin.value());
        } else {
            OutSetReg::write(1U << pin.value());
        }
    }
};

using GpioP0 = GpioPort<0x50000000>;


#endif