#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include "mat_utils.hpp"

void demo_template_functions()
{
    int max_int = max(10, 20);
    printk("Max of 10 and 20 is: %d\n", max_int);

    float max_float = max(1.23f, 4.56f);
    printk("Max of 1.23 and 4.56 is %.2f\n", max_float);

    int clamped = clamp(150, 0, 100);
    printk("clamp(150, 0, 100) = %d\n", clamped);
}

void demo_template_class()
{
    printk("\n==== Template Class ====\n");
    CircularBuffer<int, 5> int_buffer;

    printk("Pushing: 10, 20, 30\n");
    int_buffer.push(10);
    int_buffer.push(20);
    int_buffer.push(30);
    printk("Buffer size: %d\n", int_buffer.size());

    int value;
    int_buffer.pop(value);
    printk("Popped: %d\n", value);
    printk("Buffer size: %d\n", int_buffer.size());
    
    // Different type, different size - completely separate class!
    CircularBuffer<float, 10> float_buffer;
    float_buffer.push(1.23f);
    float_buffer.push(4.56f);
    printk("Float buffer size: %d\n", float_buffer.size());
}

int main() {
    printk("\n");
    printk("=========================================\n");
    printk("  Week 2 Day 1: Template Basics\n");
    printk("=========================================\n");
    printk("\n");
    printk("Concepts:\n");
    printk("  - Template functions (generic code)\n");
    printk("  - Template classes (type-safe containers)\n");
    printk("  - Compile-time type checking\n");
    printk("  - Zero runtime overhead\n");
    printk("\n");
    
    demo_template_functions();
    demo_template_class();
    
    printk("\n=========================================\n\n");
    
    while (1) {
        k_msleep(1000);
    }
}