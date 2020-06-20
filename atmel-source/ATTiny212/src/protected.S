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

#include <avr/io.h>

/*  void protected_write_io(void* addr, uint8_t magic, uint8_t value); */

 .global protected_write_io
 .section .text.protected_write_io, "ax", @progbits
 .type protected_write_io, @function

protected_write_io:
    movw    r30, r24 /* Load addr into Z */
    out     CCP, r22 /* Start CCP handshake */
    st      Z, r20   /* Write value to I/O register */
    ret              /* Return to caller */

 .size   protected_write_io, . - protected_write_io

