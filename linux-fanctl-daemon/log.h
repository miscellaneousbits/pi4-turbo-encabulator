#pragma once

#include <syslog.h>

// Setup logging
void LogInit(void);

// Log message (printf style with severity)
void Log(int level, char* fmt, ...);
