#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include "typed_gpio.hpp"

using Led0 = TypedGPIO<15>; // LED0 is connected to pin 13
// using Led1 = TypedGPIO<14>; // LED1 is connected to pin 14
// using Led2 = TypedGPIO<15>; // LED2 is connected to pin 15
// using Led3 = TypedGPIO<16>; // LED3 is connected to pin 16

void demo_basic_register_access() {
    printk("Demo: Basic Register Access\n");

    printk("Setting pin 13 hight via OUTSET register\n");
    GPIO_P0::OUTSET_REG::write(1U << 13);

    printk("Reading OUT register: 0x%08X\n", GPIO_P0::OUT_REG::read());

    printk("Clearing pin 13 via OUTCLR register\n");
    GPIO_P0::OUTCLR_REG::clear_bits(1U << 13);

    printk("Reading OUT register: 0x%08X\n", GPIO_P0::OUT_REG::read());
}

void demo_typed_gpio() {
    printk("Demo: Typed GPIO demo\n");

    Led0::configure_output();
    // Led1::configure_output();
    // Led2::configure_output();
    // Led3::configure_output();

    printk("\nTurning all LEDs on...\n");
    Led0::set_high();
    // Led1::set_high();
    // Led2::set_high();
    // Led3::set_high();

    printk("\nTurning all LEDs off...\n");
    Led0::set_low();
    // Led1::set_low();
    // Led2::set_low();
    // Led3::set_low();
}

void demo_led_patterns() {
    printk("\n=== LED Pattern Demo ===\n");
    
    // Running light
    printk("Running light pattern\n");
    for (int i = 0; i < 3; i++) {
        Led0::set_high(); k_msleep(100); Led0::set_low();
        // // Led1::set_high(); k_msleep(100); Led1::set_low();
        // // Led2::set_high(); k_msleep(100); Led2::set_low();
        // // Led3::set_high(); k_msleep(100); Led3::set_low();
    }
    
    // Toggle pattern
    printk("Toggle pattern\n");
    for (int i = 0; i < 5; i++) {
        Led0::toggle();
        // Led1::toggle();
        // Led2::toggle();
        // Led3::toggle();
        k_msleep(200);
    }
    
    // All off
    Led0::set_low();
    // Led1::set_low();
    // Led2::set_low();
    // Led3::set_low();
}

int main(void) {
    printk("\n");
    printk("=============================================\n");
    printk("  Week 2 Day 2: Type-Safe Register Access\n");
    printk("=============================================\n");
    printk("\n");
    printk("Concepts:\n");
    printk("  - Template-based register wrapper\n");
    printk("  - Compile-time address validation\n");
    printk("  - Type-safe hardware access\n");
    printk("  - static_assert for constraints\n");
    printk("  - Zero runtime overhead\n");
    printk("\n");
    
    demo_basic_register_access();
    k_msleep(1000);
    
    demo_typed_gpio();
    k_msleep(1000);
    
    demo_led_patterns();
    k_msleep(1000);
    
    
    printk("\n=== Interactive Demo ===\n");
    printk("LEDs will blink in sequence continuously\n\n");
    
    // Continuous demo
    while (1) {
        Led0::toggle();
        k_msleep(250);
        
        // Led1::toggle();
        k_msleep(250);
        
        // Led2::toggle();
        k_msleep(250);
        
        // Led3::toggle();
        k_msleep(250);
    }
    
    return 0;
}