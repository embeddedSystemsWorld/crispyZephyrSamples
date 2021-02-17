/*
 * Copyright (c) 2020 Thomas Popp
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>

#include "usbconsole.h"

// ---- logging includes/defines -----------------------------------------------
#include <logging/log.h>
#include <logging/log_ctrl.h>
#define CONFIG_APP_LOG_LEVEL           LOG_LEVEL_DBG
LOG_MODULE_REGISTER(app, CONFIG_APP_LOG_LEVEL);


// ---- defines LED0 for the LED pin -------------------------------------------
// the devicetree node identifier for the "led0" alias.
#define LED0_NODE DT_ALIAS(led0)

#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
#define LED0	DT_GPIO_LABEL(LED0_NODE, gpios)
#define PIN	DT_GPIO_PIN(LED0_NODE, gpios)
#define FLAGS	DT_GPIO_FLAGS(LED0_NODE, gpios)
#else
// a build error here means your board isn't set up to blink an LED.
#error "Unsupported board: led0 devicetree alias is not defined"
#define LED0	""
#define PIN	0
#define FLAGS	0
#endif

// LED cycle defs
#define LED0_CYCLE_TIME 1000
#define LED0_ON_TIME     100
#define LED0_OFF_TIME   LED0_CYCLE_TIME - LED0_ON_TIME

// -----------------------------------------------------------------------------
void main (void) {
    const struct device *dev;
    int rc;

    rc = usbconole_init();
    
    // init the LED
    dev = device_get_binding(LED0);
    if (dev == NULL) {
        return;
    }

    rc = gpio_pin_configure(dev, PIN, GPIO_OUTPUT_ACTIVE | FLAGS);
    if (rc < 0) {
        return;
    }  
    
    // run the loop for ever    
    while (true) {
        LOG_INF("Hello World from %s board!", CONFIG_BOARD);
        gpio_pin_set(dev, PIN, (int)true);
        k_msleep(LED0_ON_TIME);        
        gpio_pin_set(dev, PIN, (int)false);
        k_msleep(LED0_OFF_TIME);        
    }

}
