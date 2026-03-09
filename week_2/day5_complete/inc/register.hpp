#ifndef REGISTER_HPP
#define REGISTER_HPP

#include <cstdint>

template<uint32_t addr>
class Register {
public:
    static void write(uint32_t value) {
        // usual embedded c: *(volatile uint32_t*)addr = value;
        *reinterpret_cast<volatile uint32_t*>(addr) = value;
    }

    static uint32_t read() {
        return *reinterpret_cast<volatile uint32_t*>(addr);
    }

    static void set_bit(uint8_t bit) {
        write(read() | (1U << bit));
    }

    static void clear_bit(uint8_t bit) {
        write(read() & ~(1U << bit));
    }

    static void set_bits(uint32_t mask) {
        write(read() | mask);
    }

    static void clear_bits(uint8_t mask) {
        write(read() & ~mask);
    }

    static bool is_bit_set(uint8_t bit) {
        return *reinterpret_cast<volatile uint32_t*>(addr) & (1U << bit);
    }
};

#endif