#include "Logger.h"
#include "asserts.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h>



b8 Init()
{
//TODO: implement logging to file
//TODO: create log file
return 0;
}

void ReportAssertionFailure(const char* expression, const char* file, i32 line, const char* message = nullptr){
    Log(LOG_LEVEL_FATAL, "Assertion Failure: %s\nFile: %s\nLine: %d\nMessage: %s", expression, file, line, message);
}


void Log(LogLevel level, const char *message, ...)
{
    const char* levelString[6] = {"[FATAL]:", "[ERROR]:", "[WARN]:", "[INFO]:", "[DEBUG]:", "[TRACE]:"};
    
    //b8 isError = level < 2;
    
    char outMessage[32000];
    memset(outMessage, 0, 32000);
    __builtin_va_list arg_ptr;
    va_start(arg_ptr, message);
    vsnprintf(outMessage, 32000, message, arg_ptr);
    va_end(arg_ptr);

    char completeOutMessage[32000];
    sprintf(completeOutMessage, "%s %s\n", levelString[level], outMessage);
    printf("%s", outMessage);
}

void ShutDown()
{
    //TODO: close log file
    //TODO: logging write queue entries

}
