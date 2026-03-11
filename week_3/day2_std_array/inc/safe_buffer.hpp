#ifndef SAFE_BUFFER_HPP
#define SAFE_BUFFER_HPP

#include <cstdint>
#include <array>
#include <cstddef>

class UnsafeBuffer {
private:
    uint8_t data_[32];

public:
    uint8_t* data() { return data_; }

    // No size() method - caller must remember size!
    // No bounds checking!
};

// C++ std::array wrapper (new way)
class SafeBuffer {
private:
    std::array<uint8_t, 32> data_;

public:
    std::array<uint8_t, 32>& data() {return data_; }

    size_t size() const { return data_.size(); }

    uint8_t& at(size_t index) { return data_.at(index); }

    uint8_t& operator[](size_t index) { return data_[index]; }
};

#endif // SAFE_BUFFER_HPP