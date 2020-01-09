// I2C Fan Controller for Raspberry Pi 4
#pragma once
#include "common.h"

// Run CPU at 10MHz
#define F_CPU 10000000u

// Initialize system clocks
void CLKCTRL_init(void);
