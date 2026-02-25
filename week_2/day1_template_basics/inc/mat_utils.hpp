#ifndef MATH_UTILS_HPP
#define MATH_UTILS_HPP

#include <zephyr/sys/printk.h>

template<typename T>
T max(T a, T b){
    return (a > b) ? a : b;
}

template<typename T>
T clamp(T value, T min, T max){
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

template<typename T, int Size>
class CircularBuffer {
private:
    T buffer_[Size];
    int head_;
    int tail_;
    int count_;

public:
    CircularBuffer() : head_(0), tail_(0), count_(0) {}

    bool push(const T value) {
        if (count_ >= Size){
            printk("Buffer is full.\n");
            return false;
        }
        buffer_[tail_] = value;
        tail_ = (tail_ + 1) % Size;
        count_++;
        return true;
    }

    bool pop(T& value) {
        if (count_ == 0){
            printk("Buffer is empty.\n");
            return false;
        }

        value = buffer_[head_];
        head_ = (head_ + 1) % Size;
        count_--;
        return true;
    }

    int size() const { return count_; }
    bool is_empty() const { return count_ == 0; }
    bool is_full() const { return count_ >= Size; }
};

#endif // MATH_UTILS_HPP