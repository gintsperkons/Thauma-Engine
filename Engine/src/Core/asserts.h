#pragma once

#include "define.h"

#define TASSERTIONS_ENABLED 1

#ifdef TASSERTIONS_ENABLED
#if _MSC_VER
#include <intrin.h>
#define DebugBreak() __debugbreak()
#else
#define DebugBreak() __builtin_trap()
#endif

TAPI void ReportAssertionFailure(const char* expression, const char* file, i32 line, const char* message);

#define TASSERT(expression)    {                                            \
    if (expression) {}                                                      \
    else                                                                    \
    {                                                                       \
        ReportAssertionFailure(#expression, __FILE__, __LINE__, "");        \
        DebugBreak();                                                       \
    }                                                                       \
}

#define TASSERT_MSG(expression,message)   {                                     \
    if (expression) {}                                                          \
    else                                                                        \
    {                                                                           \
        ReportAssertionFailure(#expression, __FILE__, __LINE__, message);       \
        DebugBreak();                                                           \
    }                                                                           \
}
#ifdef TDEBUG
#define TASSERT_DEBUG(expression)   {                                       \
    if (expression) {}                                                      \
    else                                                                    \
    {                                                                       \
        ReportAssertionFailure(#expression, __FILE__, __LINE__, "");        \
        DebugBreak();                                                       \
    }                                                                       \
}

#else   
#define TASSERT_DEBUG(expression)
#endif

#else
#define TASSERT(expression)
#define TASSERT_MSG(expression,message)
#define TASSERT_DEBUG(expression)
#endif


