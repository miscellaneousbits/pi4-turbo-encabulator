// I2C Fan Controller for Raspberry Pi 4
#pragma once
#include "common.h"

void LED_init(void);

static inline void LED_set(bool s)
{
    PORT_set_level(LED_PORT, s);
}
