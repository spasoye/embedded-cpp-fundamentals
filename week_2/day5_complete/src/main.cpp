#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include "gpio_pin.hpp"

using red_led = GpioPin<15>;

void demo_type_safety() {
    printk("\n=== Type Safety Demo ===\n");
    
    printk("Type-safe operations:\n");
    printk("  ✓ red_led::set_high() - Clear intent\n");
    printk("  ✓ red_led::set(PinState::High) - Explicit state\n");
    printk("\n");
    
    printk("These WON'T compile (commented out):\n");
    printk("  ✗ red_led::set(1) - Wrong type\n");
    printk("  ✗ red_led::set_high(15) - Shouldn't need pin number\n");
    printk("\n");
    
    // Demonstrate type-safe operations
    red_led::set(PinState::high);
    k_msleep(500);
    red_led::set(PinState::low);
    k_msleep(500);
    
    // These would cause compile errors:
    // red_led::set(1);           // ERROR: int is not PinState
    // red_led::set_high(15);     // ERROR: no parameter expected
}

int main(void){
    red_led::configure_output();
    printk("Blinking LED three times...\n");

    for (uint8_t cnt = 0; cnt < 3; cnt++){
        red_led::set_high();
        k_msleep(500);
        red_led::set_low();
        k_msleep(500);
    }

    demo_type_safety();
    
    printk("Done!\n");

    while (1) {
        k_msleep(1000);
    }
}

