#ifndef SPI_SESSION_HPP
#define SPI_SESSION_HPP

#include <zephyr/drivers/spi.h>
#include <zephyr/kernel.h>

class SpiSession {
public:
    SpiSession(const struct device* spi_dev);
    ~SpiSession();

    int transfer_byte(uint8_t tx_byte, uint8_t* rx_byte);

    // TODO: wtf
    SpiSession(const SpiSession&) = delete;
    SpiSession& operator=(const SpiSession&) = delete;

private:
    const struct device* spi_dev_;
};

#endif