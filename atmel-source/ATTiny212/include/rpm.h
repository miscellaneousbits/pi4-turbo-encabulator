// I2C Fan Controller for Raspberry Pi 4
#pragma once
#include "common.h"

extern volatile uint8_t g_rotations;

void RPM_init(void);
