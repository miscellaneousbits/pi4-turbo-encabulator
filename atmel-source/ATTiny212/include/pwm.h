// I2C Fan Controller for Raspberry Pi 4
#pragma once
#include "common.h"

#include "clkctrl.h"

#define FAN_MAX 127u
#define PERIOD_24KHZ ((uint16_t)(F_CPU / 24000u))

void PWM_init(void);

static inline void PWM_duty_cycle(uint16_t duty)
{
    TCA0.SINGLE.CMP0BUF = duty;
}
