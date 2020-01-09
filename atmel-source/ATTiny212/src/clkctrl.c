// I2C Fan Controller for Raspberry Pi 4
#include "clkctrl.h"
#include "protected.h"

// Initialize system clocks
void CLKCTRL_init(void)
{
    // Set internal (master) clock to 20Mhz
    protected_write_io(
        (void*)&CLKCTRL.MCLKCTRLA, CCP_IOREG_gc, CLKCTRL_CLKSEL_OSC20M_gc);
    // Set CPU clock to 10MHz
    protected_write_io((void*)&CLKCTRL.MCLKCTRLB, CCP_IOREG_gc,
        CLKCTRL_PDIV_2X_gc | CLKCTRL_PEN_bm);
}
