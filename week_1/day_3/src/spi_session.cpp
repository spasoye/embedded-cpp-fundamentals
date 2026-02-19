#include "spi_session.hpp"
#include <zephyr/drivers/spi.h>
#include <zephyr/sys/printk.h>
// TODO: fiddle with prj.conf ?
#include <zephyr/random/random.h>
#include <zephyr/kernel.h>

SpiSession::SpiSession(const struct device* spi_dev) : spi_dev_(spi_dev) {
    /*
        * This is dummy example and no actual SPI transfer is performed. In a real implementation, you would set up the SPI configuration and perform necessary initialization here. This is just to demonstrate how to structure the class and handle the SPI device.
    */
    if (!device_is_ready(spi_dev_)) {
        printk("SPI device not ready\n");
    }
    printk("SPI session started\n");
}

SpiSession::~SpiSession() {
    printk("SPI session ended\n");

}

int SpiSession::transfer_byte(uint8_t tx_byte, uint8_t* rx_byte){
    printk("SPI transfer TX=0x%02X", tx_byte);

    /*
        * simulate a delay for the SPI transfer. In a real implementation, you would perform the actual SPI transfer.
    */
    if (rx_byte) {
        // Random byte
        *rx_byte = sys_rand8_get();
        printk(" RX=0x%02X\n", *rx_byte);
    }
    printk("\n");

    return 0;
}

