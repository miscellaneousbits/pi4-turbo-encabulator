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
#include "common.h"

// Port pull-up enable
enum port_pull_mode
{
    PORT_PULL_OFF = 0,
    PORT_PULL_UP,
};

// Port direction
enum port_dir
{
    PORT_DIR_IN = 0,
    PORT_DIR_OUT
};

// Enable/disable port's pull up resistor
static inline void PORT_set_pull_mode(
    const uint8_t pin, const enum port_pull_mode pull_mode)
{
    volatile uint8_t* port_pin_ctrl = ((uint8_t*)&PORTA + 0x10 + pin);

    if (pull_mode == PORT_PULL_UP)
        *port_pin_ctrl |= PORT_PULLUPEN_bm;
    else
        *port_pin_ctrl &= ~PORT_PULLUPEN_bm;
}

// Enable port's pull up resistor
static inline void PORT_set_pull_up(const uint8_t pin)
{
    *((uint8_t*)&PORTA + 0x10 + pin) |= PORT_PULLUPEN_bm;
}

// Disable port's pull up resistor
static inline void PORT_set_pull_off(const uint8_t pin)
{
    *((uint8_t*)&PORTA + 0x10 + pin) &= ~PORT_PULLUPEN_bm;
}

// Set port to output
static inline void PORT_set_out(const uint8_t pin)
{
    VPORTA.DIR |= (1 << pin);
}

// Set port to input
static inline void PORT_set_in(const uint8_t pin)
{
    VPORTA.DIR &= ~(1 << pin);
}

// Set port mode (input/output)
static inline void PORT_set_dir(const uint8_t pin, const enum port_dir dir)
{
    switch (dir)
    {
    case PORT_DIR_IN:
        VPORTA.DIR &= ~(1 << pin);
        break;
    case PORT_DIR_OUT:
        VPORTA.DIR |= (1 << pin);
        break;
    default:
        break;
    }
}

// Set output port's value
static inline void PORT_set_level(const uint8_t pin, const bool level)
{
    if (level)
        VPORTA.OUT |= (1 << pin);
    else
        VPORTA.OUT &= ~(1 << pin);
}

// Get port's value
static inline bool PORT_get_level(const uint8_t pin)
{
    return VPORTA.IN & (1 << pin);
}

// Enable port interrupt
static inline void PORT_set_isc(const uint8_t pin, const PORT_ISC_t isc)
{
    volatile uint8_t* port_pin_ctrl = ((uint8_t*)&PORTA + 0x10 + pin);

    *port_pin_ctrl = (*port_pin_ctrl & ~PORT_ISC_gm) | isc;
}
