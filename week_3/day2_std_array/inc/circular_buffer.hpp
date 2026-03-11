#ifndef CIRCULAR_BUFFER_HPP
#define CIRCULAR_BUFFER_HPP

#include <cstddef>
#include <array>

template <typename T, size_t N>
class CircularBuffer {
private:
    std::array<T, N> buffer_;
    size_t head_;
    size_t tail_;
    size_t count_;

public:
    CircularBuffer() : head_(0), tail_(0), count_(0){}

    bool push(T value){
        if (count_ >= buffer_.size()){
            return false;
        }

        buffer_[tail_] = value;
        tail_ = (tail_ + 1) % buffer_.size();
        count_++;
        return true;
    }

    bool pop(T& value){
        if (count_ == 0) { 
            return false;
        }

        value = buffer_[head_];
        head_ = (head_ + 1) % buffer_.size();
        count_--;
        return true;
    }

    size_t size() { return count_; }
    size_t capacity() { return buffer_.size(); }
    bool is_empty() { return count_ == 0; }
    bool is_full() { return count_ >= buffer_.size();}
};

#endif // CIRCULAR_BUFFER_HPP