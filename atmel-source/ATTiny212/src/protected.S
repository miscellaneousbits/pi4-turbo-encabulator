// I2C Fan Controller for Raspberry Pi 4
#include <avr/io.h>

/*  void protected_write_io(void* addr, uint8_t magic, uint8_t value); */

    .global protected_write_io
    .section .text.protected_write_io, "ax", @progbits
    .type protected_write_io, @function

protected_write_io:
	movw    r30, r24                /* Load addr into Z */
	out     CCP, r22                /* Start CCP handshake */
	st      Z, r20                  /* Write value to I/O register */
	ret                             /* Return to caller */

	.size   protected_write_io, . - protected_write_io

