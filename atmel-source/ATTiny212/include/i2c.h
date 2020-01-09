// I2C Fan Controller for Raspberry Pi 4
#pragma once

#include "common.h"

// Set by main to new fan speed
extern volatile int8_t g_fan_control;

// Setup I2C interface
void I2C_init(void);
