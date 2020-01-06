// I2C Fan Controller for Raspberry Pi 4
#pragma once
#include "common.h"

void protected_write_io(void* addr, uint8_t magic, uint8_t value);
