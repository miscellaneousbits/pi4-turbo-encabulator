// I2C Fan Controller for Raspberry Pi 4
#pragma once

#include <avr/builtins.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sleep.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "port.h"

#define SDA_PORT 1
#define SCL_PORT 2
#define RPM_PORT 3
#define LED_PORT 6
#define PWM_PORT 7
