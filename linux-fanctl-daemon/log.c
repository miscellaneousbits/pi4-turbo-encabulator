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
