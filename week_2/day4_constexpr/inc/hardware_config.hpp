#ifndef HARDWARE_CONFIG_HPP
#define HARDWARE_CONFIG_HPP

#include "compile_time_math.hpp"

namespace HardwareConfig {
    // Clock frequencies
    constexpr uint32_t CPU_CLOCK_HZ = 64000000;
    constexpr uint32_t PERIPHERAL_CLOCK_HZ = 16000000;

    // UART configurations
    constexpr uint32_t UART_BAUD_RATE = 115200;
    constexpr uint32_t UART_DIVISOR = calculated_baud_divisor(
        UART_BAUD_RATE, 
        PERIPHERAL_CLOCK_HZ
    );

    constexpr uint32_t SPI_CLOCK_HZ = 8000000;  // 8 MHz
    constexpr uint32_t SPI_DIVISOR = calculated_baud_divisor(
        SPI_CLOCK_HZ,
        PERIPHERAL_CLOCK_HZ
    );

    // Timer configuration (1ms tick)
    constexpr uint32_t TIMER_TICK_MS = 1;
    constexpr uint32_t TIMER_RELOAD = CPU_CLOCK_HZ / 1000 * TIMER_TICK_MS;
    
    // Buffer sizes (power of 2 for efficiency)
    constexpr size_t UART_BUFFER_SIZE = power_of_2(8);   // 256
    constexpr size_t SPI_BUFFER_SIZE = power_of_2(6);    // 64
    constexpr size_t I2C_BUFFER_SIZE = power_of_2(5);    // 32
    
    // Version information with compile-time CRC
    constexpr const char* VERSION_STRING = "v1.2.3";
    constexpr uint8_t VERSION_CRC = crc8(VERSION_STRING, const_strlen(VERSION_STRING));
}

#endif