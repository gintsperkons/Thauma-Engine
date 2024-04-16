#include "logger.h"
#include "asserts.h"
#include <stdio.h>
Logger::Logger()
{
	
}

Logger::~Logger()
{

}

static Logger* instance = nullptr;
Logger* Logger::getInstance()
{
	if (instance == nullptr)
		instance = new Logger();
		return instance;
}

void Logger::log(Level level, const char *format, ...)
{
	const char* levelStr[6] = {"[FATAL]: ", "[ERROR]: ", "[WARN]: ", "[INFO]: ", "[DEBUG]: ", "[TRACE]: "};
	va_list args;
	va_start(args, format);
	printf(levelStr[(int)level]);
	vprintf(format, args);
	va_end(args);
}
void reportAssertionFailure(const char *expression, const char *file, int line, const char *message)
{
	Logger::getInstance()->log(Logger::Level::FATAL, "Assertion failed: %s\nFile: %s\nLine: %d\nMessage: %s\n", expression, file, line, message);
}