#include "critical_section.hpp"
#include <zephyr/sys/printk.h>

critical_section::critical_section() {
    key_ = irq_lock();  // Disable interrupts, save state
    printk("[IRQ LOCKED - interrupts disabled]\n");
}

critical_section::~critical_section() {
    irq_unlock(key_);  // Restore interrupts
    printk("[IRQ UNLOCKED - interrupts restored]\n");
}