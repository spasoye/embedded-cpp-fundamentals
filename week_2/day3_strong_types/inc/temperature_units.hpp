#ifndef TEMPERATURE_UNITS_HPP
#define TEMPERATURE_UNITS_HPP

class Celsius {
private:
    float value_;

public:
    explicit Celsius(float temp) : value_(temp) {}

    float value() const { return value_; }
};

class Fahrenheit {
private:
    float value_;

public:
    explicit Fahrenheit(float temp) : value_(temp) {}
    
    float value() const { return value_; }
    
    // Convert to Celsius
    Celsius to_celsius() const {
        return Celsius((value_ - 32.0f) * 5.0f / 9.0f);
    }
};

inline Fahrenheit to_fahrenheit(Celsius c) {
    return Fahrenheit(c.value() * 9.0f / 5.0f + 32.0f);
}

#endif