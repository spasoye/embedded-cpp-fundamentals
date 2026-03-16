#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include "sensor_read.hpp"
#include "battery_monitor.hpp"

void demo_old_style_problems() {
    printk("\n=== Old C-Style Error Handling ===\n");
    
    // Problem 1: Magic value
    int16_t temp = OldSensorRead::read_temperature();
    printk("Temperature: %d°C\n", temp);

    if (temp == -1) {
        printk("  Sensor error detected\n");
    } else {
        printk("  But wait, -1°C is a valid temperature!\n");
    }

    uint8_t humidity;
    bool success = OldSensorRead::read_humidity(&humidity);
    
    if (success) {
        printk("Humidity: %u%%\n", humidity);
    } else {
        printk("Humidity sensor failed\n");
    }
    
    // Problem 3: Easy to forget check
    printk("\nCommon bug - forgot to check return:\n");
    uint8_t hum;
    OldSensorRead::read_humidity(&hum);  // Forgot to check!

    printk("Humidity: %u%% (might be garbage!)\n", hum);
}

void demo_new_optional() {
    printk("\n=== New std::optional example ===\n");

    auto temp = NewSensorRead::read_temperature();

    if (temp.has_value()) {
        printk("Temperature: %d°C\n", temp.value());
    } else {
        printk("Temperature sensor failed\n");
    }

    auto humidity = NewSensorRead::read_humidity();

    if (humidity) {  // Implicit bool conversion
        printk("Humidity: %u%%\n", *humidity);  // Dereference like pointer
    } else {
        printk("Humidity sensor failed\n");
    }
    
    // Can't forget to check - compiler forces you!
    printk("\nType safety:\n");
    printk("  Can't use value without checking has_value()\n");
    printk("  Can't confuse error with valid data\n");
}

void demo_battery_monitor() {
    printk("\n=== Battery Monitor with std::optional ===\n");
    
    // Scenario 1: No battery present
    printk("\nScenario 1: No battery\n");
    battery_monitor::set_battery_present(false);
    
    auto charge = battery_monitor::get_charge_percent();
    auto voltage = battery_monitor::get_voltage_mv();
    
    if (charge.has_value()) {
        printk("  Charge: %u%%\n", charge.value());
    } else {
        printk("  Charge: Not available (no battery)\n");
    }
    
    if (voltage.has_value()) {
        printk("  Voltage: %umV\n", voltage.value());
    } else {
        printk("  Voltage: Not available (no battery)\n");
    }

    // Using value_or() for default
    uint8_t display_charge = battery_monitor::get_charge_or_default(0);
    printk("  Display shows: %u%% (default)\n", display_charge);
    
    k_msleep(1000);
    
    // Scenario 2: Battery present, low charge
    printk("\nScenario 2: Battery low (15%%)\n");
    battery_monitor::set_battery_present(true);
    battery_monitor::set_charge(15);
    
    charge = battery_monitor::get_charge_percent();
    voltage = battery_monitor::get_voltage_mv();
    
    if (charge && voltage) {  // Both have values
        printk("  Charge: %u%%\n", *charge);
        printk("  Voltage: %umV\n", *voltage);
        
        if (*charge < 20) {
            printk("  ⚠ LOW BATTERY WARNING!\n");
        }
    }
    
    k_msleep(1000);
    
    // Scenario 3: Battery present, good charge
    printk("\nScenario 3: Battery healthy (85%%)\n");
    battery_monitor::set_charge(85);
    
    charge = battery_monitor::get_charge_percent();
    voltage = battery_monitor::get_voltage_mv();
    
    if (charge && voltage) {
        printk("  Charge: %u%%\n", *charge);
        printk("  Voltage: %umV\n", *voltage);
        printk("  ✓ Battery OK\n");
    }
    
    // Demonstrate value_or
    printk("\nUsing value_or() for safe defaults:\n");
    battery_monitor::set_battery_present(false);
    uint8_t safe_charge = battery_monitor::get_charge_or_default(100);
    printk("  Charge (or 100 if missing): %u%%\n", safe_charge);
}

int main(void) {
    printk("\n");
    printk("=============================================\n");
    printk("  Week 3 Day 3: std::optional\n");
    printk("=============================================\n");
    
    demo_old_style_problems();
    k_msleep(2000);
    
    demo_new_optional();

    demo_battery_monitor();
    
    printk("\n=============================================\n\n");
    
    while (1) {
        k_msleep(1000);
    }
}