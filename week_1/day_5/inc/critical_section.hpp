#ifndef CRITICAL_SECTION_HPP
#define CRITICAL_SECTION_HPP

#include <zephyr/kernel.h>

class critical_section{
    public:
        critical_section();
        ~critical_section();

        critical_section(const critical_section&) = delete;
        critical_section& operator=(const critical_section&) = delete;

    private:
        uint8_t key_;
};



#endif // CRITICAL_SECTION_H