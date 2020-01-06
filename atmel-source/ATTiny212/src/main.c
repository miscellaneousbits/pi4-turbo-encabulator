// I2C Fan Controller for Raspberry Pi 4
#include "clkctrl.h"
#include "i2c.h"
#include "led.h"
#include "pwm.h"
#include "rpm.h"

int main(void)
{
    static int8_t last_control = -1;

    CLKCTRL_init();
    for (uint8_t i = 0; i < 8; i++)
        PORT_set_pull_off(i);

    sei();

    LED_init();
    PWM_init();
    RPM_init();
    I2C_init();

    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_enable();

    for (;;)
    {
        sleep_cpu();
        if (g_fan_control < 0)
            continue;
        int8_t control = g_fan_control;
        g_fan_control = -1;
        if (control != last_control)
        {
            last_control = control;
            PWM_duty_cycle(((uint16_t)control * PERIOD_24KHZ) / FAN_MAX);
        }
    }
}
