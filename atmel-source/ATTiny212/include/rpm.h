// I2C Fan Controller for Raspberry Pi 4
#pragma once
#include "common.h"

// Set by RPM interrupt handler. Contains rev. count/sec.
extern volatile uint8_t g_rotations;

// Setup RPM counter
void RPM_init(void);
