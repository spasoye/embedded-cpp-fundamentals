#ifndef REGISTER_HPP
#define REGISTER_HPP

#include <cstdint>

template<uint32_t Address>
class Register {
public:
    static void write(uint32_t value) {
        // same as: *(volatile uint32_t*)Address = value;
        *reinterpret_cast<volatile uint32_t*>(Address) = value;
    }

    static uint32_t read() {
        return *reinterpret_cast<volatile uint32_t*>(Address);
    }

    static void set_bits(uint32_t mask) {
        write(read() | mask);
    }

    static void clear_bits(uint32_t mask) {
        write(read() & ~mask);
    }

    static void toggle_bits(uint32_t mask) {
        write(read() ^ mask);
    }

    static bool is_bit_set(uint32_t bit) {
        return (read() & (1U << bit)) != 0;
    }

    static void set_bit(uint32_t bit) {
        write(read() | 1U << bit);
    }

    static void clear_bit(uint32_t bit){
        clear_bits(1U << bit);
    }
};

#endif // REGISTER_HPP