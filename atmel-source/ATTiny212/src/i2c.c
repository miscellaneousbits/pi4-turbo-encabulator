// I2C Fan Controller for Raspberry Pi 4
#include "i2c.h"
#include "port.h"
#include "rpm.h"

// Pick an I2C slave address for the fan controller
#define I2C_SLAVE_ADDRESS 0x2c

// We are either handling data, or idle.
enum
{
    IDLE_STATE = 0,
    DATA_STATE
};

// Fan control global
// -1 : Fan PWM has been updated
// 0-127 : Nes fan speed for PWM
volatile int8_t g_fan_control = -1;

// Current state starts off idle
static uint8_t state = IDLE_STATE;

// I2C receive handler. Called by interrupt on receiving byte
static inline void i2c_recv(uint8_t b, uint8_t addr)
{
    // address byte
    if (addr)
    {
		// Since we only handle single byte messages, the address
		// is unused so we ignore it, but we to exit idle state
        state = DATA_STATE;
        return;
    }

    // data byte, reject it if idle
    if (state == IDLE_STATE)
        return;
	// Store received byte as new fan speed setting
    g_fan_control = b & 0x7f;
	// Done, drop back to idle state
    state = IDLE_STATE;
}

// I2C request handler. Called by interrupt handler when TX data
// is needed.
static inline uint8_t i2c_req(void)
{
	// Ignore if idle
    if (state == IDLE_STATE)
        return 0;
	// Send latest RPM count, and go idle
    state = IDLE_STATE;
    return g_rotations;
}

void I2C_init()
{
	// Add internal pull ups on I2C clock and data pins
    PORT_set_pull_up(SCL_PORT);
    PORT_set_pull_up(SDA_PORT);
	// Set the I2C controller slave address
    TWI0.SADDR = I2C_SLAVE_ADDRESS << 1;
	// Start the I2C controller with iterrupt enabled
    TWI0.SCTRLB = 0;
    TWI0.SCTRLA = TWI_DIEN_bm | TWI_APIEN_bm | TWI_PIEN_bm | TWI_ENABLE_bm;
}

// I2C interrupt handler
ISR(TWI0_TWIS_vect)
{
    uint8_t sstatus = TWI0.SSTATUS;
    // Data interrupt
    if (sstatus & TWI_DIF_bm)
    {
        if (TWI0.SSTATUS & TWI_DIR_bm)
			// Send
            TWI0.SDATA = i2c_req();
        else
			// Receive
            i2c_recv(TWI0.SDATA, false);
		// Acknowledge transaction
        TWI0.SCTRLB = TWI_SCMD_RESPONSE_gc;
        return;
    }
    // Address or stop interrupt
    if (sstatus & TWI_APIF_bm)
    {
        // address
        if (sstatus & TWI_AP_bm)
        {
			// Discard the address
            i2c_recv(TWI0.SDATA, true);
			// Ack the transaction
            TWI0.SCTRLB = TWI_SCMD_RESPONSE_gc;
        }
        // stop
        else
			// End the transaction
            TWI0.SCTRLB = TWI_SCMD_COMPTRANS_gc;
    }
}
