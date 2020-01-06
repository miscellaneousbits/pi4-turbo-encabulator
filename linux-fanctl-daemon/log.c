#include <stdarg.h>
#include <stdio.h>

#include "log.h"

void LogInit(void)
{
    openlog(NULL, LOG_PID, LOG_DAEMON);
}

void Log(int level, char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vsyslog(level, fmt, args);
}
