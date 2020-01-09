// I2C Fan Controller for Raspberry Pi 4
#include "led.h"

// Setup LED control
void LED_init(void)
{
	// Set pin to output, no pullup, initially off
    PORT_set_out(LED_PORT);
    PORT_set_pull_off(LED_PORT);
    PORT_set_level(LED_PORT, false);
}
