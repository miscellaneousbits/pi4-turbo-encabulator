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

#include "rpm.h"

#include "led.h"

// Updated once per second with rotation count
volatile uint8_t g_rotations = 0;

// Local rotation count
static uint8_t count = 0;

// RPM pin edge detect interrupt
ISR(PORTA_PORT_vect)
{
    // Increment local rotations
    count++;
    // Clear interrupt status
    PORTA.INTFLAGS = PORT_INT3_bm;
}

// Per half second interval timer interrupt, which is convenient
// since fan ulses twice per rotation
ISR(RTC_PIT_vect)
{
    // Update the globals rotation count
    g_rotations = count;
    // Reset the local rotation count
    count = 0;
    // Turn on the green LED if the fan is turning
    LED_set(g_rotations);
    // Clear interrupt status
    RTC.PITINTFLAGS = RTC_PI_bm;
}

void RPM_init(void)
{
    // set the RTC/PIT for interrupt every 1/2 sec.
    RTC.CLKSEL = RTC_CLKSEL_INT1K_gc;
    RTC.CTRLA = RTC_RTCEN_bm;
    RTC.PITINTCTRL = RTC_PI_bm;
    RTC.PITCTRLA = RTC_PERIOD_CYC512_gc | RTC_PITEN_bm;

    // Set the RPM pin to input with edge detect interrupt.
    PORT_set_in(RPM_PORT);
    PORT_set_pull_up(RPM_PORT);
    PORT_set_isc(RPM_PORT, PORT_ISC_RISING_gc);
}
