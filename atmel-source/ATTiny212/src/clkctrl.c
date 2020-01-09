/*
    This file is part of the pi4-turbo-encabulator.

    pi4-turbo-encabulator is free software: you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version.

    pi4-turbo-encabulator is distributed in the hope that it will be
    useful, but WITHOUT ANY WARRANTY; without even the implied warranty
    of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <https://www.gnu.org/licenses/>.
*/

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
