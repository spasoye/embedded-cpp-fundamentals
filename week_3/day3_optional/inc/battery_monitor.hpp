#ifndef BATTERY_MONITOR_HPP
#define BATTERY_MONITOR_HPP

#include <cstdint>
#include <optional>

class battery_monitor {
private:
    static bool batt_present_;
    static uint8_t batt_percent_;

public:
    static void set_battery_present(bool present) {
        batt_present_ = present;
    }

    static void set_charge(uint8_t percent) {
        if (percent <= 100) {
            batt_percent_ = percent;
        }
    }

    static std::optional<uint8_t> get_charge_percent() {
        if (!batt_present_) {
            // return {}; or
            return std::nullopt;
        }
    }

    static std::optional<uint16_t> get_voltage_mv() {
        if (!batt_present_) {
            return {};
        }

        uint16_t voltage = 3000 + (batt_percent_ * 12);
        return voltage;
    }

    static uint8_t get_charge_or_default(uint8_t default_val) {
        return get_charge_percent().value_or(default_val);
    }
};


inline bool battery_monitor::batt_present_ = false;
inline uint8_t battery_monitor::batt_percent_ = 0;

#endif