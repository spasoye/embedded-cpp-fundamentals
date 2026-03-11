#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include "state_machine.hpp"

void demo_old_enum_problems() {
    printk ("\n=== Demo old enum problems ===\n");

    // Problem 1: No type safety. Can mix different enums.
    OldState state = OLD_IDLE;
    OldColor color = OLD_RED;

    if (state == OLD_BLUE){
        printk("BUG: state equals color !!!\n");
    }

    // Problem 2: Implicit conversion to int. Can compare with integers.
    int x = OLD_IDLE;

    printk("OLD_IDLE as int: %d\n", x);

    if (state == 0){
        printk("OLD_IDLE equals 0 !!!\n");
    }

    // Problem 3: Name pollution. All enum values are in the global namespace.
    printk("Names: OLD_IDLE, OLD_RED (global pollution)\n");
}

void demo_new_enum_class() {
    printk("\n=== Demo new enum class ===\n");

    State state = State::Idle;
    Color color = Color::Blue;

    // if (state == Color::Red) {}     // ERROR: different types
    // if (state == 0) {}              // ERROR: can't compare to int
    // int x = State::Idle;            // ERROR: no implicit conversion

    printk("\nType safety prevents:\n");
    printk("  ✗ Mixing different enums\n");
    printk("  ✗ Comparing to raw numbers\n");
    printk("  ✗ Implicit int conversion\n");
    
    // Must use explicit scope
    if (state == State::Idle) {
        printk("  ✓ Clear: comparing State to State\n");
    }
}

void demo_led_controller() {
    printk("\n=== Practical: LED Controller ===\n");
    
    LedMode mode = LedMode::Off;
    
    printk("Testing all LED modes:\n\n");

    const LedMode modes[] = {
        LedMode::Off,
        LedMode::FastBlink,
        LedMode::SlowBlink,
        LedMode::SolidOn,
        LedMode::HeartBeat
    };

    for (const auto& m : modes) {
        mode = m;
        printk("Mode: %s\n", to_string(mode));
        
        // Type-safe switch statement
        switch (mode) {
            case LedMode::Off:
                printk("  LED: OFF\n");
                break;
                
            case LedMode::SolidOn:
                printk("  LED: ON (solid)\n");
                break;
                
            case LedMode::SlowBlink:
                printk("  LED: Blinking slowly\n");
                break;
                
            case LedMode::FastBlink:
                printk("  LED: Blinking fast\n");
                break;
                
            case LedMode::HeartBeat:
                printk("  LED: Heartbeat pattern\n");
                break;
        }
        
        k_msleep(1000);
    }
}

void demo_compiler_warnings() {
    printk("\n=== Compiler Warning Demo ===\n");
    
    State state = State::Running;
    
    printk("Complete switch (handles all cases):\n");
    
    // GOOD: Handle all cases
    switch (state) {
        case State::Idle:
            printk("  State: Idle\n");
            break;
        case State::Running:
            printk("  State: Running\n");
            break;
        case State::Error:
            printk("  State: Error\n");
            break;
    }
    
    // If you compile with -Wall, incomplete switch gives warning:
    switch (state) {
        case State::Idle:
            break;
        case State::Running:
            break;
        // Missing State::Error - compiler warns!
    }
    
    printk("\nWith old enums, missing cases go unnoticed.\n");
    printk("With enum class, compiler can warn you!\n");
}

int main(void) {
    printk("\n");
    printk("=============================================\n");
    printk("  Week 3 Day 1: Type-Safe Enums\n");
    printk("=============================================\n");
    
    demo_old_enum_problems();
    k_msleep(2000);
    
    demo_new_enum_class();

    demo_led_controller();

    demo_compiler_warnings();
    
    printk("\n=============================================\n\n");
    
    while (1) {
        k_msleep(1000);
    }
}