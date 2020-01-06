// I2C Fan Controller for Raspberry Pi 4
#include "clkctrl.h"
#include "protected.h"

void CLKCTRL_init(void)
{
    protected_write_io((void*)&CLKCTRL.MCLKCTRLA, CCP_IOREG_gc, CLKCTRL_CLKSEL_OSC20M_gc);             // 20MHz Internal
    protected_write_io((void*)&CLKCTRL.MCLKCTRLB, CCP_IOREG_gc, CLKCTRL_PDIV_2X_gc | CLKCTRL_PEN_bm);  // 10MHz sys
}
