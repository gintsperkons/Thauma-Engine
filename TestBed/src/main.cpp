#include "main.h"
#include <Core/asserts.h>

int main()
{
    Log(LOG_LEVEL_FATAL,"This is a fatal error %f", 3.14f);
    TASSERT(1 == 0);
    return 0;
}