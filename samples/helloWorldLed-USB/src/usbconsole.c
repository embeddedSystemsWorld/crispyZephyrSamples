// ---- zephyr includes --------------------------------------------------------
#include <zephyr.h>
// #include <device.h>
// #include <devicetree.h>
// #include <drivers/gpio.h>

#include <usb/usb_device.h>
#include <drivers/uart.h>

// #include "error.h"

// ---- module include- --------------------------------------------------------
#include "usbconsole.h"


// ---- logging includes/defines -----------------------------------------------
#include <logging/log.h>
#define CONFIG_STATUS_LOG_LEVEL   LOG_LEVEL_INF
LOG_MODULE_REGISTER(usbconsole, CONFIG_STATUS_LOG_LEVEL);

#define NO_ERR 0

#define GEN_ERR -1


int usbconole_init(void) {
    const struct device *dev = device_get_binding(
            CONFIG_UART_CONSOLE_ON_DEV_NAME);
    uint32_t dtr = 0U;
    uint32_t baudrate;
    int ret;    
    
    LOG_INF("init");  
    
    if (!dev) {
        LOG_ERR("CDC ACM device not found");
        return (GEN_ERR);
    }

    ret = usb_enable(NULL);
    if (ret != 0) {
        LOG_ERR("Failed to enable USB");
        return (GEN_ERR);
    }

// 	ring_buf_init(&ringbuf, sizeof(ring_buffer), ring_buffer);

    LOG_INF("Wait for DTR");

    uint32_t timeout = 0;
    while (true) {
        uart_line_ctrl_get(dev, UART_LINE_CTRL_DTR, &dtr);
        if (dtr) {
            break;
        } else {
            /* Give CPU resources to low priority threads. */
            k_sleep(K_MSEC(100));
            
            if (timeout > 10) {
                return (-ETIME);
            }
            else {
                timeout++;
            }
        }
    }

    LOG_INF("DTR set");

    /* They are optional, we use them to test the interrupt endpoint */
    ret = uart_line_ctrl_set(dev, UART_LINE_CTRL_DCD, 1);
    if (ret) {
        LOG_WRN("Failed to set DCD, ret code %d", ret);
    }

    ret = uart_line_ctrl_set(dev, UART_LINE_CTRL_DSR, 1);
    if (ret) {
        LOG_WRN("Failed to set DSR, ret code %d", ret);
    }

    /* Wait 1 sec for the host to do all settings */
    k_busy_wait(1000000);

    ret = uart_line_ctrl_get(dev, UART_LINE_CTRL_BAUD_RATE, &baudrate);
    if (ret) {
        LOG_WRN("Failed to get baudrate, ret code %d", ret);
    } else {
        LOG_INF("Baudrate detected: %d", baudrate);
    }
    return (NO_ERR);
}
