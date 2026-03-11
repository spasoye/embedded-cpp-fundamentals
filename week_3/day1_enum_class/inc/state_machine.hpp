#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include <cstdint>

enum OldState{
    OLD_IDLE,
    OLD_RUNNING,
    OLD_ERROR    
};

enum OldColor {
    OLD_RED,
    OLD_GREEN,
    OLD_BLUE
};

// New way - enum class
enum class State: uint8_t {
    Idle,
    Running,
    Error
};

enum class Color: uint8_t {
    Red,
    Green,
    Blue
};

enum class LedMode: uint8_t {
    Off,
    SolidOn,
    SlowBlink,
    FastBlink,
    HeartBeat
};

inline const char* to_string(LedMode mode) {
    switch (mode)
    {
        case LedMode::Off :         return "Off";
        case LedMode::SolidOn:      return "SolidOn";
        case LedMode::SlowBlink:    return "SlowBlink";
        case LedMode::FastBlink:    return "FastBlink";
        case LedMode::HeartBeat:    return "HeartBeat";
        default:                    return "Unknown";
    }
};

#endif // STATE_MACHINE_HPP