// I2C Fan Controller for Raspberry Pi 4
#include "led.h"
#include "rpm.h"

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
