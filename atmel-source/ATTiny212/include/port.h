// I2C Fan Controller for Raspberry Pi 4
#pragma once
#include "common.h"

#define SDA_PORT 1
#define SCL_PORT 2
#define RPM_PORT 3
#define LED_PORT 6
#define PWM_PORT 7

enum port_pull_mode
{
    PORT_PULL_OFF = 0,
    PORT_PULL_UP,
};

enum port_dir
{
    PORT_DIR_IN = 0,
    PORT_DIR_OUT
};

static inline void PORT_set_pull_mode(const uint8_t pin, const enum port_pull_mode pull_mode)
{
    volatile uint8_t* port_pin_ctrl = ((uint8_t*)&PORTA + 0x10 + pin);

    if (pull_mode == PORT_PULL_UP)
        *port_pin_ctrl |= PORT_PULLUPEN_bm;
    else
        *port_pin_ctrl &= ~PORT_PULLUPEN_bm;
}

static inline void PORT_set_pull_up(const uint8_t pin)
{
    *((uint8_t*)&PORTA + 0x10 + pin) |= PORT_PULLUPEN_bm;
}

static inline void PORT_set_pull_off(const uint8_t pin)
{
    *((uint8_t*)&PORTA + 0x10 + pin) &= ~PORT_PULLUPEN_bm;
}

static inline void PORT_set_out(const uint8_t pin)
{
    VPORTA.DIR |= (1 << pin);
}

static inline void PORT_set_in(const uint8_t pin)
{
    VPORTA.DIR &= ~(1 << pin);
}

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

static inline void PORT_set_level(const uint8_t pin, const bool level)
{
    if (level)
        VPORTA.OUT |= (1 << pin);
    else
        VPORTA.OUT &= ~(1 << pin);
}

static inline bool PORT_get_level(const uint8_t pin)
{
    return VPORTA.IN & (1 << pin);
}

static inline void PORT_set_isc(const uint8_t pin, const PORT_ISC_t isc)
{
    volatile uint8_t* port_pin_ctrl = ((uint8_t*)&PORTA + 0x10 + pin);

    *port_pin_ctrl = (*port_pin_ctrl & ~PORT_ISC_gm) | isc;
}
