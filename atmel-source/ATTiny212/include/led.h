// I2C Fan Controller for Raspberry Pi 4
#pragma once
#include "common.h"
#include "port.h"

// Setup LED control
void LED_init(void);

// Turn ON/OFF LED
static inline void LED_set(bool s)
{
    PORT_set_level(LED_PORT, s);
}
