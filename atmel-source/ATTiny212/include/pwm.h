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
#include "clkctrl.h"

// Fan speed range 0-127
#define FAN_MAX 127u
// Fan PWM period
#define PERIOD_24KHZ ((uint16_t)(F_CPU / 24000u))

// Setup pWM
void PWM_init(void);

// Set PWM duty cycle
static inline void PWM_duty_cycle(uint16_t duty)
{
    TCA0.SINGLE.CMP0BUF = duty;
}
