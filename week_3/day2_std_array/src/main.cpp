#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <array>
#include "safe_buffer.hpp"
#include "circular_buffer.hpp"

void demo_c_array_problems() {
    printk ("\n=== C array problems ===\n");

    uint8_t buffer[10];

    for(int i = 0; i < 10; i++){
        buffer[i] = i;
    }

    printk("Buffer filled with 0-9\n");

    // Problem 1: No size information
    printk("sizeof(buffer) = %zu\n", sizeof(buffer));

    // Problem 2: Can write pass the end (undefined behaviour)
    // buffer[15] = 99;  // Compiles! Might crash, might corrupt memory
    printk("Can write buffer[15] - no compiler error!\n");

    // Problem 3: Loses size when passed to function
    printk("When passed to function, loses size info\n");
}

void demo_std_array() {
    k_msleep(2000);
    printk("\n=== std::array solution ===\n");

    std::array<uint8_t, 10> buffer;

    for (size_t i = 0; i < buffer.size(); i++) {
        buffer[i] = i;
    }

    printk("Buffer filled with 0-9\n");
    printk("buffer.size() = %zu\n (always known size)", buffer.size());

    // Safe access with bounds checking
    // buffer.at(15);  // Would assert/abort in embedded
    printk("buffer.at(15) would catch out-of-bounds!\n");

    printk("Content of buffer: ");
    for (const auto& val: buffer) {
        printk("%d ", val);
    }
    printk("\n");
}

void demo_circular_buffer() {
    printk("\n=== Circular Buffer with std::array ===\n");
    CircularBuffer<uint8_t, 5> buffer;
    
    printk("Created circular buffer with capacity %zu\n", buffer.capacity());
    printk("Current size of buffer: %zu\n\n", buffer.size());

    printk("Pushing values 10, 20, 30, 40, 50...\n");
    buffer.push(10);
    buffer.push(20);
    buffer.push(30);
    buffer.push(40);
    buffer.push(50);

    printk("Buffer size: %zu\n", buffer.size());
    printk("Buffer full: %s\n", buffer.is_full() ? "yes":"no");

    // Try to push when full
    printk("\nTrying to push 60 (buffer full)...\n");
    if (!buffer.push(60)) {
        printk("  Failed - buffer full!\n");
    }

    printk("\nPopping values:\n");
    uint8_t value;
    for (int i = 0; i < 3; i++) {
        if (buffer.pop(value)) {
            printk("  Popped: %u\n", value);
        }
    }
    
    printk("Buffer size after popping: %zu\n", buffer.size());

    // Push more (wraps around)
    printk("\nPushing 60, 70, 80 (will wrap around)...\n");
    buffer.push(60);
    buffer.push(70);
    buffer.push(80);

    printk("Buffer size: %zu\n", buffer.size());
    
    // Pop all remaining
    printk("\nPopping all remaining:\n");
    while (buffer.pop(value)) {
        printk("  Popped: %u\n", value);
    }

    printk("\nBuffer empty: %s\n", buffer.is_empty() ? "yes" : "no");
}

int main(void) {
    printk("\n");
    printk("=============================================\n");
    printk("  Week 3 Day 2: std::array Safety\n");
    printk("=============================================\n");
    
    demo_c_array_problems();
    k_msleep(2000);
    
    demo_std_array();
    
    demo_circular_buffer();
    printk("\n=============================================\n\n");
    
    while (1) {
        k_msleep(1000);
    }
}