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

#include <stdio.h>

#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "log.h"
#include "temp.h"

static int fd = -1;

// Temperature from Videocore
int tempOpen(void)
{
    fd = open("/dev/vcio", 0);
    if (fd == -1)
    {
        Log(LOG_ERR, "Can't open Videocore device\n");
        return -1;  // Temp of 0 represents error
    }
    return 0;
}

void tempClose(void)
{
    if (fd >= 0)
        close(fd);
}

// Get current CPU temperature
uint32_t getTemp(void)
{
    uint32_t t = 0;
    unsigned int property[10] = {
        sizeof(property), 0, 0x30006, 8, 4, 0, 0, 0, 0, 0};

    if (ioctl(fd, _IOWR(100, 0, char*), property) == -1)
        Log(LOG_ERR, "Videocore IOCTL failure\n");
    else
        t = property[6] / 1000;

    return t;
}
