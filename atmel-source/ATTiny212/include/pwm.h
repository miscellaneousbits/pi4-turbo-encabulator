// I2C Fan Controller for Raspberry Pi 4
#pragma once
#include "common.h"

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
