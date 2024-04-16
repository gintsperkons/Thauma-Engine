#include <test.h>
#include <Core/logger.h>
#include <Core/asserts.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	LOG_WARN("Hello World%d",1);
	TASSERT(1 == 0);
	Logger* logger = Logger::getInstance();
	printTestHi();
	return 0;
}