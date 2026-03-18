#ifndef DATA_BUFFER_HPP
#define DATA_BUFFER_HPP

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <cstdint>


class data_buffer
{
private:
    /* data */
    uint8_t* data_;
    size_t size_;

public:
    data_buffer(size_t size): size_(size), data_(new uint8_t[size]) {
        printk(" [Constructor] Created buffer of %zu bytes\n", size_);

        for (size_t i = 0; i < size_; i++) {
            data_[i] = i % 256;
        }
    }

    ~data_buffer() {
        printk("  [Destructor] Freeing buffer of %zu bytes\n", size_);
        delete[] data_;
    }

    data_buffer(const data_buffer& other) : size_(other.size_) {
        printk(" [COPY constructor] Copying %zu bytes (EXPENSIVE!)\n", size_);
        data_ = new uint8_t[size_];
        memcpy(data_, other.data_, size_);
    }

    data_buffer& operator=(const data_buffer& other){
        printk("  [COPY Assignment] Copying %zu bytes (EXPENSIVE!)\n", other.size_);
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            data_ = new uint8_t[size_];
            memcpy(data_, other.data_, size_);
        }
        return *this;
    }

    data_buffer(data_buffer&& other) noexcept : 
        data_(other.data_), size_(other.size_) {
            printk("  [MOVE Constructor] Moving %zu bytes (CHEAP!)\n", size_);
            other.data_ = nullptr;
            other.size_ = 0;
    }

    data_buffer& operator=(data_buffer&& other) noexcept {
        printk("  [MOVE Assignment] Moving %zu bytes (CHEAP!)\n", other.size_);
        if (this != &other) {
            delete[] data_;

            data_ = other.data_;
            size_ = other.size_;

            other.data_ = nullptr;
            other.size_ = 0;
        }

        return *this;
    }
    size_t size() { return size_; }
    uint8_t* data() { return data_; }
};

#endif //DATA_BUFFER_HPP