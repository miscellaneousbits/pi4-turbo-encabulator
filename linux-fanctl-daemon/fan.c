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

#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "fan.h"
#include "log.h"

#define RPI4
//#define RPI3

// Interval count, only used with debug log level
int file_i2c = -1;

#ifdef RPI3
static const char* i2c_device = "/dev/i2c-1";
// /boot/config.txt edits
// dtparam=i2c_arm=on
#endif

#ifdef RPI4
static const char* i2c_device = "/dev/i2c-3";
// /boot/config.txt edits
// #dtparam=i2c_arm=on
// dtoverlay=i2c3,pins_2_3
#endif

// Initialize the fan controller
int fanInit(void)
{
  // Communicate via I2C
  if ((file_i2c = open(i2c_device, O_RDWR)) < 0) {
    Log(LOG_ERR, "Failed to open the i2c bus\n");
    return -1;
    }

    const int addr = 0x2c;  //<<<<<The I2C address of the slave
    if (ioctl(file_i2c, I2C_SLAVE, addr) < 0)
    {
        Log(LOG_ERR, "Failed to acquire bus access and/or talk to slave.\n");
        return -1;
    }
    return 0;
}

// Release the fan controller
void fanClose(void)
{
    if (file_i2c >= 0)
        close(file_i2c);
}

// Set the fan power level
void fanPower(uint8_t s)
{
  // Set new fan speed by sending single byte (values = 0-127)
  if (write(file_i2c, &s, sizeof(s)) != sizeof(s))
    Log(LOG_ERR, "Failed to write to the i2c bus.\n");
}

// Retrieve the fan RPM
uint32_t fanRPM(void)
{
  // Retrieve RPM (atually revs per sec.) by reading
  // single byte.
  uint8_t rpm;
  if (read(file_i2c, &rpm, sizeof(rpm)) != sizeof(rpm))
    Log(LOG_ERR, "Failed to read to the i2c bus.\n");
  // Convert RPS to RPM
  return (uint32_t)rpm * 60;
}
