#include "spi_session.hpp"
#include <zephyr/drivers/spi.h>
#include <zephyr/sys/printk.h>
#include "led.hpp"
#include "button.hpp"

#define SPI_NODE     DT_NODELABEL(spi#)
#define LED0_NODE    DT_ALIAS(led0)
#define BUTTON0_NODE DT_ALIAS(sw0)

static const struct gpio_dt_spec led_spec = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec btn_spec = GPIO_DT_SPEC_GET(BUTTON0_NODE, gpios);
/* Demonstration 
const struct device* spi_dev = DEVICE_DT_GET(SPI_NODE);
*/
// Simulate reading flash chip ID
void read_flash_id() {
    printk("\n=== Reading Flash ID ===\n");
    
    uint8_t manufacturer_id;
    uint8_t device_id[2];
    
    {
        SpiSession spi(nullptr);  // SPI enabled HERE
        
        spi.transfer_byte(0x9F, nullptr);          // JEDEC ID command
        spi.transfer_byte(0x00, &manufacturer_id);
        spi.transfer_byte(0x00, &device_id[0]);
        spi.transfer_byte(0x00, &device_id[1]);
        
    }  // ← SPI disabled HERE automatically!
    
    // Process data WITHOUT SPI consuming power
    printk("Manufacturer: 0x%02X\n", manufacturer_id);
    printk("Device: 0x%02X%02X\n", device_id[0], device_id[1]);
    printk("=== Flash read complete ===\n\n");
}

// Simulate writing to flash
void write_flash_byte(uint32_t address, uint8_t data) {
    printk("\n=== Writing to Flash ===\n");
    printk("Address: 0x%06X, Data: 0x%02X\n", address, data);
    
    {
        SpiSession spi(nullptr);  // SPI enabled
        
        // Write enable command
        spi.transfer_byte(0x06, nullptr);
        
    }  // SPI disabled
    
    k_msleep(1);  // Small delay (SPI not consuming power)
    
    {
        SpiSession spi(nullptr);  // SPI enabled again
        
        // Page program command
        spi.transfer_byte(0x02, nullptr);
        spi.transfer_byte((address >> 16) & 0xFF, nullptr);
        spi.transfer_byte((address >> 8) & 0xFF, nullptr);
        spi.transfer_byte(address & 0xFF, nullptr);
        spi.transfer_byte(data, nullptr);
        
    }  // SPI disabled
    
    printk("=== Write complete ===\n\n");
}

int main() {
    Led led(led_spec);
    Button button(btn_spec);
    
    printk("\n=== Day 3: SPI Session RAII Demo ===\n\n");
    
    // Demonstrate RAII scope control
    read_flash_id();
    k_msleep(1000);
    read_flash_id();
    
    // Main loop
    while (1) {
        if (button.is_pressed()) {
            led.on();
            read_flash_id();  // SPI only active during this call
        } else {
            led.off();
        }
        
        k_msleep(100);
    }
}