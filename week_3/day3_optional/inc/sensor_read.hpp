#ifndef SENSOR_READER_HPP
#define SENSOR_READER_HPP

#include <cstdint>
#include <optional>

class OldSensorRead {
public:
    // Returns -1 on error
    static int16_t read_temperature() {
        // Simulate sensor failure
        bool sensor_ok = false;
        
        if (!sensor_ok) {
            return -1;  // Magic error value - but -1°C is valid!
        }
        return 22;  // 22°C
    }
    
    // Two-parameter pattern (clunky)
    static bool read_humidity(uint8_t* result) {
        bool sensor_ok = false;
        
        if (!sensor_ok) {
            return false;
        }
        *result = 65;  // 65%
        return true;
    }
};


class NewSensorRead{
public:
    static std::optional<uint16_t> read_temperature() {
        bool sensor_ok = false;

        if (!sensor_ok){
            return {};
        }
        return 22;
    }

    static std::optional<uint8_t> read_humidity() {
        bool sensor_ok = false;

        if (!sensor_ok) {
            return std::nullopt;
        }

        return 65;
    }
};

#endif