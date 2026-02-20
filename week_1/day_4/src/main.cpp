#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/gpio.h>

#include "critical_section.hpp"
#include "led.hpp"
#include "button.hpp"

#define LED0_NODE DT_ALIAS(led0)
#define BUTTON0_NODE DT_ALIAS(sw0)

static const struct gpio_dt_spec red_led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec btn = GPIO_DT_SPEC_GET(BUTTON0_NODE, gpios);

volatile uint32_t shared_counter = 0;
volatile bool data_ready = false;

void unsafe_increment_counter(uint32_t value) {
    printk("\n--- UNSAFE (C-style) ---\n");
    
    unsigned int key = irq_lock();
    printk("Interrupts disabled...\n");
    
    shared_counter += value;
    
    if (shared_counter > 100) {
        printk("ERROR: Counter too high!\n");
        // TODO: demonstrate what happens if we forget to unlock here
        // BUG! Forgot to call irq_unlock(key)
        // Interrupts stay disabled - SYSTEM HANGS!
        // return;  // ← If this was here, we'd be in trouble
    }
    
    irq_unlock(key);
    printk("Interrupts restored\n");
    printk("Counter: %u\n", shared_counter);
}

void safe_increment_counter(uint32_t value) {
    printk("\n--- SAFE (C++ RAII) ---\n");
    
    {
        critical_section cs;  // Interrupts disabled
        
        shared_counter += value;
        
        if (shared_counter > 100) {
            printk("ERROR: Counter too high!\n");
            return;  // ← Destructor STILL runs! Interrupts restored!
        }
        
        data_ready = true;
        
    }  // ← Destructor runs - interrupts restored automatically
    
    printk("Counter: %u\n", shared_counter);
}

// Nested critical sections (Zephyr handles this correctly)
void nested_critical_example() {
    printk("\n--- NESTED CRITICAL SECTIONS ---\n");
    
    {
        critical_section outer;  // Lock 1
        printk("Outer critical section\n");
        
        shared_counter++;
        
        {
            critical_section inner;  // Lock 2 (nested)
            printk("  Inner critical section\n");
            
            shared_counter++;
            
        }  // Inner unlock
        
        printk("Back to outer\n");
        shared_counter++;
        
    }  // Outer unlock - interrupts fully restored here
    
    printk("Counter: %u\n", shared_counter);
}

void multi_exit_example(int mode) {
    printk("\n--- MULTIPLE EXIT PATHS (mode=%d) ---\n", mode);
    
    {
        critical_section cs;
        
        shared_counter += 10;
        
        if (mode == 1) {
            printk("Early exit 1, counter: %u\n", shared_counter);
            return;  // Destructor runs
        }
        
        shared_counter += 5;
        
        if (mode == 2) {
            printk("Early exit 2, counter: %u\n", shared_counter);
            return;  // Destructor runs
        }
        
        shared_counter += 3;
        
    }  // Destructor runs on normal exit too
    
    printk("Normal exit, Counter: %u\n", shared_counter);
}

int main(void) {
    Led r_led(red_led);
    Button usr_btn(btn);
    
    printk("\n");
    printk("=============================================\n");
    printk("  Day 4: CriticalSection RAII Demo\n");
    printk("=============================================\n");
    printk("\n");
    printk("Demonstrating automatic interrupt restoration\n");
    printk("even with early returns and errors.\n");
    printk("\n");
    
    // Initial demonstrations
    k_msleep(1000);
    
    safe_increment_counter(10);
    k_msleep(500);
    
    safe_increment_counter(20);
    k_msleep(500);
    
    nested_critical_example();
    k_msleep(500);
    
    multi_exit_example(1);  // Normal path
    k_msleep(500);
    
    multi_exit_example(2);  // Early exit 1
    k_msleep(500);
    
    multi_exit_example(0);  // Early exit 2
    k_msleep(500);
    
    // Reset for interactive demo
    shared_counter = 0;
    printk("\n");
    printk("=== Interactive Demo ===\n");
    printk("Press button to increment counter safely\n");
    printk("\n");
    
    while (1) {
        if (usr_btn.is_pressed()) {
            r_led.on();
            
            safe_increment_counter(1);
            
            k_msleep(300);  // Debounce
            
        } else {
            r_led.off();
        }
        
        k_msleep(10);
    }
    
    return 0;
}