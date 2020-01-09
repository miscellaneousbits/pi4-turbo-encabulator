// I2C Fan Controller for Raspberry Pi 4
#include "port.h"
#include "pwm.h"

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
