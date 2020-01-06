// I2C Fan Controller for Raspberry Pi 4
#include "rpm.h"
#include "led.h"

volatile uint8_t g_rotations = 0;

static uint8_t count = 0;

ISR(PORTA_PORT_vect)
{
    count++;
    PORTA.INTFLAGS = PORT_INT3_bm;
}

ISR(RTC_PIT_vect)
{
    g_rotations = count;
    count = 0;
    LED_set(g_rotations);
    RTC.PITINTFLAGS = RTC_PI_bm;
}

void RPM_init(void)
{
    RTC.CLKSEL = RTC_CLKSEL_INT1K_gc;
    RTC.CTRLA = RTC_RTCEN_bm;
    RTC.PITINTCTRL = RTC_PI_bm;
    RTC.PITCTRLA = RTC_PERIOD_CYC512_gc | RTC_PITEN_bm;

    PORT_set_in(RPM_PORT);
    PORT_set_pull_up(RPM_PORT);
    PORT_set_isc(RPM_PORT, PORT_ISC_RISING_gc);
}
