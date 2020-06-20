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

#include "pwm.h"

#include "port.h"

void PWM_init(void)
{
    // Set PWM pin to outout
    PORT_set_out(PWM_PORT);
    // Set the alternate pin MUX, output PWM to pin PA7
    PORTMUX.CTRLC |= PORTMUX_TCA00_bm;
    // Set TCA as standard PWN with 24KHz cycle.
    TCA0.SINGLE.CTRLB = TCA_SINGLE_CMP0EN_bm | TCA_SINGLE_WGMODE_SINGLESLOPE_gc;
    TCA0.SINGLE.PERBUF = PERIOD_24KHZ;
    TCA0.SINGLE.PER = PERIOD_24KHZ;
    TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1_gc | TCA_SINGLE_ENABLE_bm;
    PWM_duty_cycle(0);
}
