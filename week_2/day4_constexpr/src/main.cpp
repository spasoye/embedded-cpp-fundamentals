#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include "compile_time_math.hpp"
#include "hardware_config.hpp"
#include "lookup_table.hpp"

void demo_basic_constexpr() {
    printk("\n=== Basic constexpr Demo ===\n");
    
    // These are calculated by compiler, not CPU!
    constexpr uint32_t baud = calculated_baud_divisor(115200, 160000000);
    constexpr uint32_t mask = set_bit(0,5);
    constexpr uint32_t power = power_of_2(10);

    printk("Compile time calculated baud divisor: %u\n", baud);
    printk("Mask: 0x%06X\n", mask);
    printk("2^10: %u\n", power);
}

void demo_hardware_config() {
        printk("\n=== Hardware Configuration ===\n");
    
    printk("CPU Clock: %u Hz\n", HardwareConfig::CPU_CLOCK_HZ);
    printk("Peripheral Clock: %u Hz\n", HardwareConfig::PERIPHERAL_CLOCK_HZ);
    printk("\n");
    
    printk("UART Configuration:\n");
    printk("  Baud Rate: %u\n", HardwareConfig::UART_BAUD_RATE);
    printk("  Divisor: %u (compile-time calculated)\n", HardwareConfig::UART_DIVISOR);
    printk("\n");
    
    printk("SPI Configuration:\n");
    printk("  Clock: %u Hz\n", HardwareConfig::SPI_CLOCK_HZ);
    printk("  Divisor: %u (compile-time calculated)\n", HardwareConfig::SPI_DIVISOR);
    printk("\n");
    
    printk("Buffer Sizes (power of 2):\n");
    printk("  UART: %u bytes\n", HardwareConfig::UART_BUFFER_SIZE);
    printk("  SPI: %u bytes\n", HardwareConfig::SPI_BUFFER_SIZE);
    printk("  I2C: %u bytes\n", HardwareConfig::I2C_BUFFER_SIZE);
    printk("\n");
    
    printk("Version: %s\n", HardwareConfig::VERSION_STRING);
    printk("Version CRC: 0x%02X (compile-time calculated)\n", HardwareConfig::VERSION_CRC);
}

void demo_compile_vs_runtime() {
    printk("\n=== Compile-Time vs Runtime ===\n");
    
    uint32_t start, end;
    
    // Runtime calculation
    start = k_cycle_get_32();
    volatile uint32_t runtime_result = 16000000 / 115200;
    end = k_cycle_get_32();
    uint32_t runtime_cycles = end - start;
    
    printk("Runtime calculation: %u cycles\n", runtime_cycles);
    printk("Result: %u\n", runtime_result);
    
    // Compile-time calculation
    start = k_cycle_get_32();
    constexpr uint32_t compiletime_result = 16000000 / 115200;
    volatile uint32_t temp = compiletime_result;  // Force read
    end = k_cycle_get_32();
    uint32_t compiletime_cycles = end - start;
    
    printk("\nCompile-time calculation: %u cycles\n", compiletime_cycles);
    printk("Result: %u\n", compiletime_result);
    
    printk("\nSavings: ~%d cycles per use!\n", 
           (int32_t)runtime_cycles - (int32_t)compiletime_cycles);
}

void demo_string_operations() {
    printk ("\n=== Compile-Time String Operations ===\n");

    constexpr const char* fw_version = "FW_v2.1.0";
    constexpr size_t len = const_strlen(fw_version);
    constexpr uint8_t checksum = crc8(fw_version, len);

    printk("Firmware: %s\n", fw_version);
    printk("Length (compile time): %u\n", len);
    printk("CRC8 (compile time): 0x%02X\n", checksum);
}

void demo_lookup_table() {
    printk("\n=== Compile time lookup table ===\n");

    constexpr SineLookupTable<64> sine_table;

    printk("Sine lookup table size: %u\n", sine_table.size());
    printk("First 8 entires:\n");
    for(size_t i=0; i < 8; i++){
        printk("  sine[%u] = %d\n", i, sine_table.get(i));
    }

    printk("\nEntire table created at compile time!\n");
    printk("Zero runtime initialization cost.\n");
}

void demo_real_world_usage() {
    printk("\n=== Real-World Usage Example ===\n");
    
    printk("Configuring UART peripheral:\n");
    printk("  Writing divisor %u to UART_BRR register\n", 
           HardwareConfig::UART_DIVISOR);
    printk("  (This value was calculated during compilation)\n");
    printk("\n");
    
    // Simulated UART setup
    volatile uint32_t* UART_BRR = (volatile uint32_t*)0x40000008;
    *UART_BRR = HardwareConfig::UART_DIVISOR;  // Just a constant write!
    
    printk("Configuring buffers:\n");
    uint8_t uart_buffer[HardwareConfig::UART_BUFFER_SIZE];
    uint8_t spi_buffer[HardwareConfig::SPI_BUFFER_SIZE];
    
    printk("  UART buffer: %u bytes\n", sizeof(uart_buffer));
    printk("  SPI buffer: %u bytes\n", sizeof(spi_buffer));
    printk("  (Sizes calculated at compile time)\n");
}

int main(void) {
    printk("\n");
    printk("=============================================\n");
    printk("  Week 2 Day 4: constexpr Magic\n");
    printk("=============================================\n");
    printk("\n");
    printk("Moving calculations from runtime to compile-time:\n");
    printk("  - Faster code (no CPU cycles wasted)\n");
    printk("  - Smaller code (constants vs calculations)\n");
    printk("  - Type-safe (compile-time validation)\n");
    printk("\n");
    
    demo_basic_constexpr();
    k_msleep(2000);
    
    demo_hardware_config();
    k_msleep(2000);
    
    demo_compile_vs_runtime();
    k_msleep(2000);
    
    demo_string_operations();
    k_msleep(2000);
    
    demo_lookup_table();
    k_msleep(2000);
    
    demo_real_world_usage();
    
    printk("\n=============================================\n");
    printk("constexpr = Free computation at compile time!\n");
    printk("=============================================\n\n");
    
    while (1) {
        k_msleep(1000);
    }
}