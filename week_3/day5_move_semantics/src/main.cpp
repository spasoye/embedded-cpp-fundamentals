#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include "data_buffer.hpp"

template<typename T>
T&& move_helper(T& obj) {
    return static_cast<T&&>(obj);
}

void demo_copy_expensive() {
    printk("\n=== COPY (expensive) ===\n");
    
    printk("\nCreating buff1:\n");
    data_buffer buff1(1024);

    data_buffer buff2 = buff1;

    printk("\nBoth buffers exist:\n");
    printk(" buff1 size: %zu\n", buff1.size());
    printk(" buff2 size: %zu\n", buff2.size());

    printk("\nCopying buf1 to buf3 (COPY assignment):\n");

    data_buffer buff3(512);
    buff3 = buff1;

    printk("\nAll three buffers exist:\n");
    printk("  buff1 size: %zu\n", buff1.size());
    printk("  buff2 size: %zu\n", buff2.size());
    printk("  buff3 size: %zu\n", buff3.size());
}

void demo_move_cheap() {
    printk("\n=== MOVE (cheap) ===\n");

    printk("\nCreating buff1:\n");
    data_buffer buff1(1024);

    printk("Moving buff1 to buff2 ");
    data_buffer buff2 = move_helper(buff1);

    printk("buff1 size: %zu\n", buff1.size());
    printk("buff2 size: %zu\n", buff2.size());

    data_buffer buff3(512);
    buff3 = move_helper(buff2);

    printk("buff1 size: %zu\n", buff1.size());
    printk("buff2 size: %zu (empty)\n", buff2.size());
    printk("buff3 size: %zu (!empty)\n", buff3.size());
}

data_buffer create_buffer() {
    printk("  Creating temporary buffer\n");
    data_buffer temp(2048);
    return temp;  // Automatic move - temp is temporary
}

void demo_automatic_move() {
    printk("\n=== AUTOMATIC MOVE (return value) ===\n");

    printk("\nCalling create buffer():\n");
    data_buffer buf = create_buffer();

    printk("\nReceived buffer:\n");
    printk("  buf size: %zu\n", buf.size());
}

void demo_copy_vs_move_comparison() {
    printk("\n=== COPY vs MOVE Comparison ===\n");
    
    printk("\n--- Scenario 1: COPY (buf1 still needed) ---\n");
    data_buffer buf1(1024);
    data_buffer buf2 = buf1;  // Copy - need both
    printk("Result: Both exist (buf1: %zu, buf2: %zu)\n", 
           buf1.size(), buf2.size());
    
    k_msleep(1000);
    
    printk("\n--- Scenario 2: MOVE (buf3 no longer needed) ---\n");
    data_buffer buf3(1024);
    data_buffer buf4 = move_helper(buf3);  // Move - don't need buf3
    printk("Result: Only buf4 exists (buf3: %zu, buf4: %zu)\n", 
           buf3.size(), buf4.size());
}

int main(void) {
    printk("\n");
    printk("=============================================\n");
    printk("  Week 3 Day 5: Move Semantics\n");
    printk("=============================================\n");
    printk("\nWatch the constructor/destructor messages!\n");
    
    demo_copy_expensive();
    k_msleep(3000);
    
    demo_move_cheap();
    k_msleep(3000);
    
    demo_automatic_move();
    k_msleep(3000);
    
    demo_copy_vs_move_comparison();
    
    printk("\n=============================================\n");
    printk("Copy = Duplicate data (expensive)\n");
    printk("Move = Transfer ownership (cheap)\n");
    printk("=============================================\n\n");
    
    while (1) {
        k_msleep(1000);
    }
}