#pragma once
#include "Define.h"

#define ASSERTIONS_ENABLED

#ifdef ASSERTIONS_ENABLED
#if _MSC_VER
#include <intrin.h>
#define debugBreak() __debugbreak()
#else
#define debugBreak() __builtin_trap()
#endif // _MSV_VER

TAPI void reportAssertionFailure(const char* expression, const char* file, int line, const char* message = nullptr);

#define TASSERT(expr) \
{ \
	if (expr) {} \
	else \
	{ \
		reportAssertionFailure(#expr, __FILE__, __LINE__); \
		debugBreak(); \
	} \
}

#define TASSERT_MSG(expr, msg) \
{ \
	if (expr) {} \
	else \
	{ \
		reportAssertionFailure(#expr, __FILE__, __LINE__, msg); \
		debugBreak(); \
	} \
}
#ifdef TDEBUG
#define TASSERT_DEBUG(expr)  \
{ \
	if (expr) {} \
	else \
	{ \
		reportAssertionFailure(#expr, __FILE__, __LINE__); \
		debugBreak(); \
	} \
}
#else
#define TASSERT_DEBUG(expr)
#endif // TDEBUG

#else 
#define TASSERT(expr)
#define TASSERT_MSG(expr, msg)
#define TASSERT_DEBUG(expr)


#endif // ASSERTIONS_ENABLED
