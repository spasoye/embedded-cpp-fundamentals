#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include "button_handler.hpp"

void old_style_handler(){
    printk("Old style: Button was pressed!\n");
}

void demo_old_style(){
    printk("\n=== OLD C-style Callback ===\n");

    ButtonHandler::register_callback(old_style_handler);

    ButtonHandler::simulate_press();
}

void demo_lambda_style(){
    printk("\n=== NEW lambda callback example ===\n");

    ButtonHandler::register_callback([](){
        printk("Lambda: button was pressed!\n");
    });

    ButtonHandler::simulate_press();
}

void demo_lambda_capture() {
    printk("\n=== Lambda capture (DON'T work for stored callbacks) ===\n");

    /* Lambdas with captures DON'T work for stored callbacks
    int press_cnt = 0;

    ButtonHandler::register_callback([&press_cnt](){
        (*ppress_cnt)++;
        printk("Lambda: pressed %d times\n", *ppress_cnt);
    });

    ButtonHandler::simulate_press();
    ButtonHandler::simulate_press();
    ButtonHandler::simulate_press();

    printk("Final count: %d\n", press_cnt);
    */
    // Lambda with capture
    int count = 0;
    
    auto increment = [&count]() {
        count++;
        printk("Count: %d\n", count);
    };
    
    increment();
    increment();
    increment();
    
    printk("Final count: %d\n", count);
}

int main() {
    printk("\n");
    printk("==========================\n");
    printk("    Week 3 day 4: Lambdas\n");
    printk("==========================\n");

    demo_old_style();
    k_msleep(2000);
    demo_lambda_style();
    k_msleep(2000);
    demo_lambda_capture();
    printk("\n==========================\n\n");

    while (true)
    {
        k_msleep(1000);
    }
}