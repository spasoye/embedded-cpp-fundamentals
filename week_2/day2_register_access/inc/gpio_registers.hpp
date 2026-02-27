#ifndef GPIO_REGISTERS_HPP
#define GPIO_REGISTERS_HPP

#include "register.hpp"

// nRF52840 GPIO P0 registers (from datasheet)
namespace GPIO_P0 {
    // Base address for GPIO Port 0
    constexpr uint32_t BASE = 0x50000000;

    // Register offsets
    constexpr uint32_t OUT = 0x504;       // Output register
    constexpr uint32_t OUTSET = 0x508;    // Set bits in OUT
    constexpr uint32_t OUTCLR = 0x50C;    // Clear bits in OUT
    constexpr uint32_t IN = 0x510;        // Input register
    constexpr uint32_t DIR = 0x514;       // Direction register
    constexpr uint32_t DIRSET = 0x518;    // Set bits in DIR
    constexpr uint32_t DIRCLR = 0x51C;    // Clear bits in DIR

    using OUT_REG = Register<BASE + OUT>;
    using OUTSET_REG = Register<BASE + OUTSET>;
    using OUTCLR_REG = Register<BASE + OUTCLR>;
    using IN_REG = Register<BASE + IN>;
    using DIR_REG = Register<BASE + DIR>;
    using DIRSET_REG = Register<BASE + DIRSET>;
    using DIRCLR_REG = Register<BASE + DIRCLR>;
}

#endif // GPIO_REGISTERS_HPP