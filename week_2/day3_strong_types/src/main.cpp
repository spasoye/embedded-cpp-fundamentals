#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include "time_units.hpp"
#include "temperature_units.hpp"

void delay(Milliseconds ms) {
    k_msleep(ms.value());
}

void set_timeout(Milliseconds timeout){
    printk("Timeout set to %u ms\n", timeout.value());
}

void set_interval(Seconds interval) {
    printk("Interval set to %u seconds\n", interval.value());
}

// Temperature display
void display_temperature(Celsius temp) {
    printk("Temperature: %.1f °C\n", temp.value());
}

void demo_time_safety() {
    printk("\n=== Time Unit Safety ===\n");

    Milliseconds short_delay(100);
    Seconds long_delay(2);

    printk("Short delay:%u ms\n", short_delay.value());
    delay(short_delay);

    printk("Long delay: %u seconds\n", long_delay.value());
    delay(long_delay.to_milliseconds());

    printk("\nType safety prevents:\n");
    printk("  ✗ delay(5) - ambiguous units\n");
    printk("  ✗ delay(Seconds(5)) - wrong type\n");
    printk("  ✓ delay(Milliseconds(5000)) - clear!\n");
}

int main() {
    demo_time_safety();

    while(true) {
        k_msleep(1000);
    }
}