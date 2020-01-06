// I2C Fan Controller for Raspberry Pi 4
#pragma once
#include "common.h"

extern volatile int8_t g_fan_control;

void I2C_init(void);
