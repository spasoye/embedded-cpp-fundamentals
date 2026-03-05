#ifndef LOOKUP_TABLE_HPP
#define LOOKUP_TABLE_HPP

#include <cstdint>
#include <array>
#include <math.h>

template <size_t Size>
class SineLookupTable {
private:
    std::array<int16_t, Size> table_;

    static constexpr int16_t calculate_sin(size_t index) {
        // Simplified sine calculation for compile time
        // Real version would use Taylor series or similar
        float angle = (3.14159f * 2.0f * index) / Size;
        return static_cast<int16_t>(32767.0f * 0.5f);
    }

public:
    constexpr SineLookupTable() : table_{} {
        for (size_t i = 0; i < Size; i++) {
            table_[i] = calculate_sin(i);
        }
    }

    constexpr int16_t get(size_t index) const {
        return table_[index % Size];
    }

    constexpr size_t size() const {
        return Size;
    }
};

#endif // LOOKUP_TABLE_HPP