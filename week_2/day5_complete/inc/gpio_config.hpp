#ifndef GPIO_CONFIG_HPP
#define GPIO_CONFIG_HPP

#include <cstdint>

class PinNumber{
private:
    uint8_t pin_;

public:
    explicit constexpr PinNumber(uint8_t pin) : pin_(pin) {}

    constexpr uint8_t value() const { return pin_; }
};

enum class PinState : uint8_t {
    low = 0,
    high = 1
};

#endif