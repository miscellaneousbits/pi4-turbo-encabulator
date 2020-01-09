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

#include "clkctrl.h"
#include "i2c.h"
#include "led.h"
#include "pwm.h"
#include "rpm.h"

int main(void)
{
    // Last issued fan speed
    static int8_t last_control = -1;

    // Setup 10MHz clock
    CLKCTRL_init();

    // Is this really necessary?
    for (uint8_t i = 0; i < 8; i++)
        PORT_set_pull_off(i);

    // Enable global interrupt
    sei();

    // Setup needed controls
    LED_init();
    PWM_init();
    RPM_init();
    I2C_init();

    // Enable sleep mode. CPU will halt till next interrupt.
    // NOTE: I2C Clock stretching must be correctly implemented on the host
    // side. This is not the case for Pi4 I2C 0 and 1.
    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_enable();

    for (;;)
    {
        // Go to sleep
        sleep_cpu();
        // Go back to sleep if not new I2C speed data
        if (g_fan_control < 0)
            continue;
        // Extract and reset fan speed
        int8_t control = g_fan_control;
        g_fan_control = -1;
        // Go back to sleep if same as last
        if (control == last_control)
            continue;
        last_control = control;
        // Calculate and set new PWM interval based on speed setting
        PWM_duty_cycle(((uint16_t)control * PERIOD_24KHZ) / FAN_MAX);
    }
}
