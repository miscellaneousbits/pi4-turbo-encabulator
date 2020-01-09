/*
    This file is part of the pi4-turbo-encabulator.

    pi4-turbo-encabulator is free software: you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version.

    pi4-turbo-encabulator is distributed in the hope that it will be
    useful, but WITHOUT ANY WARRANTY; without even the implied warranty
    of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

// AVR helpers
#include <avr/builtins.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sleep.h>

// Standard C
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

// Pin function assignments
#define SDA_PORT 1
#define SCL_PORT 2
#define RPM_PORT 3
#define LED_PORT 6
#define PWM_PORT 7
