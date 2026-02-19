#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/uart.h>
#include "led.hpp"
#include "button.hpp"

BUILD_ASSERT(DT_NODE_HAS_COMPAT(DT_CHOSEN(zephyr_console), zephyr_cdc_acm_uart),
	     "Console device is not ACM CDC UART device");

#define LED0_NODE    DT_ALIAS(led0)
#define BUTTON0_NODE DT_ALIAS(sw0)

static const struct gpio_dt_spec led_spec = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec btn_spec = GPIO_DT_SPEC_GET(BUTTON0_NODE, gpios);

int main(void) {
    const struct device *const console_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_console));
    uint32_t dtr = 0;

    /* Wait for host to open the serial port (DTR signal) */
    while (!dtr) {
        uart_line_ctrl_get(console_dev, UART_LINE_CTRL_DTR, &dtr);
        k_sleep(K_MSEC(100));
    }

    Led led(led_spec);
    Button button(btn_spec);

    printk("USB console ready\n");

    while (1) {
        if (button.is_pressed()) {
            led.on();
        } else {
            led.off();
        }
        k_msleep(10);
    }
}