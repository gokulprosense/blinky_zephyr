/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>

/* 500 msec = 0.5 sec */
#define SLEEP_TIME_MS   500

/* The pin number for the LED on the Thingy:52.*/
#define LED_PIN         DT_ALIAS_LED0_GPIOS_PIN

/* Define the LED device name */
#define LED0_NODE       DT_ALIAS(led0)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

int main(void)
{
    int ret;

    if (!device_is_ready(led.port)) {
        return -1;
    }

    ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        return -1;
    }

    while (1) {
        gpio_pin_set(led.port, led.pin, 1); // Turn the LED on
        k_msleep(SLEEP_TIME_MS);
        
        gpio_pin_set(led.port, led.pin, 0); // Turn the LED off
        k_msleep(SLEEP_TIME_MS);
    }

    return 0;
}

	

