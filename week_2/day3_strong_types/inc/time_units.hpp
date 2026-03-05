#ifndef TIME_UNITS_HPP
#define TIME_UNITS_HPP

#include <cstdint>

class Milliseconds {
private:
    uint32_t value_;

public:
    explicit Milliseconds(uint32_t ms) : value_(ms) {}

    uint32_t value() const {return value_;}

    Milliseconds operator+(Milliseconds other) const {
        return Milliseconds(value_ + other.value_);
    }
};

class Seconds {
private:
    uint32_t value_;

public:
    explicit Seconds(uint32_t sec) : value_(sec) {}

    uint32_t value() const {return value_;}
    Milliseconds to_milliseconds() const {
        return Milliseconds(value_ * 1000);
    }
    Seconds operator+(Seconds other) const {
        return Seconds(value_ + other.value());
    }
};

#endif // TIME_UNITS_HPP