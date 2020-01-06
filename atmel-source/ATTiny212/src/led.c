// I2C Fan Controller for Raspberry Pi 4
#include "led.h"

void LED_init(void)
{
    PORT_set_out(LED_PORT);
    PORT_set_pull_off(LED_PORT);
    PORT_set_level(LED_PORT, false);
}
