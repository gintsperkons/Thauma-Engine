#pragma once

#include "define.h"

#define LOG_WARN_ENABLED 1
#define LOG_INFO_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1

#if TRELEASE == 1
#define LOG_DEBUG_ENABLED 0
#define LOG_TRACE_ENABLED 0
#endif


typedef enum LogLevel
{
    LOG_LEVEL_FATAL = 0,
    LOG_LEVEL_ERROR = 1,
    LOG_LEVEL_WARN = 2,
    LOG_LEVEL_INFO = 3,
    LOG_LEVEL_DEBUG = 4,
    LOG_LEVEL_TRACE = 5

} LogLevel;


b8 Init();
void ShutDown();
TAPI void Log(LogLevel level, const char* message, ...);

#define TFATAL(message, ...) Log(LOG_LEVEL_FATAL, message, ##__VA_ARGS__)
#define TERROR(message, ...) Log(LOG_LEVEL_ERROR, message, ##__VA_ARGS__)
#if LOG_WARN_ENABLED
#define TWARN(message, ...) Log(LOG_LEVEL_WARN, message, ##__VA_ARGS__)
#else
#define TWARN(message, ...)
#endif
#if LOG_INFO_ENABLED
#define TINFO(message, ...) Log(LOG_LEVEL_INFO, message, ##__VA_ARGS__)
#else
#define TINFO(message, ...)
#endif
#if LOG_DEBUG_ENABLED
#define TDEBUG(message, ...) Log(LOG_LEVEL_DEBUG, message, ##__VA_ARGS__)
#else
#define TDEBUG(message, ...)
#endif
#if LOG_TRACE_ENABLED
#define TTRACE(message, ...) Log(LOG_LEVEL_TRACE, message, ##__VA_ARGS__)
#else
#define TTRACE(message, ...)
#endif



