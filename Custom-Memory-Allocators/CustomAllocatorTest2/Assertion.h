#ifndef _ASSERTION_H_
#define _ASSERTION_H_

#include <stdio.h>

inline void ReportAssertionFailure( const char* Expression, const char* FileName, int LineNumber )
{
	printf( "ASSERTION FAILED! ( %s ) in file: %s, line %i", Expression, FileName, LineNumber );
}

#if _DEBUG && ASSERTIONS_ENABLED

#define DebugBreak() __asm { int 3 }

#define ASSERT(expr) \
	if (expr) { } else { \
		ReportAssertionFailure(#expr, __FILE__, __LINE__ ); \
		DebugBreak(); \
	}
#else

#define ASSERT(expr)

#endif

#endif