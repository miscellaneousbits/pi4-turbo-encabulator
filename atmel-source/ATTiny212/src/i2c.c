// I2C Fan Controller for Raspberry Pi 4
#include "i2c.h"
#include "rpm.h"

#define I2C_SLAVE_ADDRESS 0x2c

enum
{
    IDLE_STATE = 0,
    DATA_STATE
};

volatile int8_t g_fan_control = -1;

static uint8_t state = IDLE_STATE;

static inline void i2c_recv(uint8_t b, uint8_t addr)
{
    // address byte
    if (addr)
    {
        state = DATA_STATE;
        return;
    }

    // data byte
    if (state == IDLE_STATE)
        return;
    g_fan_control = b & 0x7f;
    state = IDLE_STATE;
}

static inline uint8_t i2c_req(void)
{
    if (state == IDLE_STATE)
        return 0;
    state = IDLE_STATE;
    return g_rotations;
}

void I2C_init()
{
    PORT_set_pull_up(SCL_PORT);
    PORT_set_pull_up(SDA_PORT);
    TWI0.SADDR = I2C_SLAVE_ADDRESS << 1;
    TWI0.SCTRLB = 0;
    TWI0.SCTRLA = TWI_DIEN_bm | TWI_APIEN_bm | TWI_PIEN_bm | TWI_ENABLE_bm;
}

ISR(TWI0_TWIS_vect)
{
    uint8_t sstatus = TWI0.SSTATUS;
    // Data interrupt
    if (sstatus & TWI_DIF_bm)
    {
        if (TWI0.SSTATUS & TWI_DIR_bm)
            TWI0.SDATA = i2c_req();
        else
            i2c_recv(TWI0.SDATA, false);
        TWI0.SCTRLB = TWI_SCMD_RESPONSE_gc;
        return;
    }
    // Address or stop interrupt
    if (sstatus & TWI_APIF_bm)
    {
        // address
        if (sstatus & TWI_AP_bm)
        {
            i2c_recv(TWI0.SDATA, true);
            TWI0.SCTRLB = TWI_SCMD_RESPONSE_gc;
        }
        // stop
        else
            TWI0.SCTRLB = TWI_SCMD_COMPTRANS_gc;
    }
}
