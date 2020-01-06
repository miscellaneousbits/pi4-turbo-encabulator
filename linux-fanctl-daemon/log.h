#pragma once

#include <syslog.h>

void LogInit(void);
void Log(int level, char* fmt, ...);
