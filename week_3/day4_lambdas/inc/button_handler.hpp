#ifndef BUTTON_HANDLER_HPP
#define BUTTON_HANDLER_HPP

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <functional>

// C-styled callback type
typedef void (*ButtonCallback)(void);

// using ButtonCallback = std::function<void()>;

class ButtonHandler {
private:
    static ButtonCallback callback_;

public:
    static void register_callback(ButtonCallback callback) {
        callback_ = callback;
    }

    static void simulate_press(){
        printk("\nButton pressed!\n");
        if (callback_ != nullptr) {
            callback_();
        }
    }
};

inline ButtonCallback ButtonHandler::callback_ = nullptr;

#endif  //BUTTON_HANDLER_HPP