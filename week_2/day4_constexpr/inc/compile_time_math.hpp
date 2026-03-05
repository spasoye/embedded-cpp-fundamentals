#ifndef COMPILE_TIME_MATH_HPP
#define COMPILE_TIME_MATH_HPP

#include <cstdint>

constexpr uint32_t calculated_baud_divisor (uint32_t baud, uint32_t clock){
    return clock / baud;
}

constexpr uint32_t set_bit (uint32_t value, uint8_t bit) {
    return value | (1U << bit);
}

constexpr uint32_t clear_bit (uint32_t value, uint8_t bit) {
    return value & ~(1U << bit);
}

constexpr uint32_t power_of_2(uint8_t exponent) {
    return (exponent == 0) ? 1 : power_of_2(exponent - 1);
}

template<typename T, size_t N>
constexpr size_t array_size(const T (&)[N]) {
    return N;
}

constexpr uint8_t crc8(const char* data, size_t len) {
    uint8_t crc = 0x00;
    for (size_t i = 0; i < len; ++i) {
        crc ^= static_cast<uint8_t>(data[i]);
        for (uint8_t j = 0; j < 8; ++j) {
            crc = (crc & 0x80) ? (crc << 1) ^ 0x07 : (crc << 1);
        }
    }
    return crc;
}

constexpr uint32_t const_strlen(const char* str) {
    return *str ? 1 + const_strlen(str + 1) : 0;
}

#endif