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

#include <stdarg.h>
#include <stdio.h>

#include "log.h"

// As daemon we output to system log
void LogInit(void)
{
    openlog(NULL, LOG_PID, LOG_DAEMON);
}

// Send printf result to log at severity
void Log(int level, char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vsyslog(level, fmt, args);
}
