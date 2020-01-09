#pragma once

#include <stdint.h>

// Initialize the fan controller
int fanInit(void);

// Release the fan controller
void fanClose(void);

// Set the fan power level
void fanPower(uint8_t s);

// Retrieve the fan RPM. Actually
// return revolutions per second
uint32_t fanRPM(void);
