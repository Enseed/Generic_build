/*******************************************************************************
Copyright 2008 Enseed inc.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

Author: Gaspard Petit
*******************************************************************************/
#ifndef __GENERIC_DEVEL_DEBUG_INLINE_H__
#define __GENERIC_DEVEL_DEBUG_INLINE_H__


//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "../Debug.h"

#ifdef GENERIC_DEBUG_IN_COLORS
#define FANCY_COLOR_RED_BEGIN  "\033[31m"
#define FANCY_COLOR_BLUE_BEGIN  "\033[36m"
#define FANCY_COLOR_END  "\033[0m"
#else
#define FANCY_COLOR_RED_BEGIN  ""
#define FANCY_COLOR_BLUE_BEGIN  ""
#define FANCY_COLOR_END  ""
#endif

#ifdef WIN32
#include <Generic/Base/win/Windows.h>
#include <crtdbg.h>
#include <cassert>
#ifdef DEBUG_BREAK
#undef DEBUG_BREAK
#endif // DEBUG_BREAK
#define DEBUG_BREAK _CrtDbgBreak()
#else
#define DEBUG_BREAK *((long*)NULL) = 0xDEADBEEF
#endif

namespace seed {

inline void ShowError(const char *aMsgHeader, const char *file,  int line, const char *func, const char *aMsg);

//------------------------------------------------------------------------------
//
inline void DebugDie(const char *file,  int line, const char *func)
{
	char msg[4096] = {0};
	std::sprintf(msg + strlen(msg), "--- Process will now exit ---");
	ShowError("Fatal Error", file, line, func, msg);
	exit(0);
}

//------------------------------------------------------------------------------
//
inline void DebugDief(const char *file,  int line, const char * func, const char *message, ...)
{
	char msg[4096] = {0};

	va_list args;
	va_start(args, message);
	std::vsprintf(msg + strlen(msg), message, args);
	std::sprintf(msg + strlen(msg), "\n\n");
	va_end(args);

	std::sprintf(msg + strlen(msg), "--- Process will now exit ---");

	ShowError("Fatal Error", file, line, func, msg);
	exit(0);
}

//------------------------------------------------------------------------------
//
inline void DebugAssert(const char *expr, const char *file,  int line, const char *func)
{
	char msg[4096] = {0};
	std::sprintf(msg + strlen(msg), "Expression: %s\n", expr);
	ShowError("Condition Failed", file, line, func, msg);
}

//------------------------------------------------------------------------------
//
inline void DebugAssertf(const char *expr, const char *file,  int line, const char * func, const char *message, ...)
{
	char msg[4096] = {0};

	std::sprintf(msg + strlen(msg), "Expression: %s\n\n", expr);

	va_list args;
	va_start(args, message);
	std::vsprintf(msg + strlen(msg), message, args);
	va_end(args);

	
	ShowError("Condition Failed", file, line, func, msg);
}

//------------------------------------------------------------------------------
//
inline void DebugFixme(const char *str, const char *file, const char *func,  int line)
{
	std::fprintf(stderr, "%sFIXME: %s\n       %s (line %d)\n       ", FANCY_COLOR_RED_BEGIN, file, func, line);
	std::fprintf(stderr, "%s", str);
	std::fprintf(stderr, "\n%s", FANCY_COLOR_END);
	std::fflush(stderr);
}

//------------------------------------------------------------------------------
//
inline void DebugFixmef(const char *file, const char *func, int line, const char *str, ...)
{
	va_list args;
	va_start(args, str);

	std::fprintf(stderr, "%sFIXME: %s\n       %s (line %d)\n       ", FANCY_COLOR_RED_BEGIN, file, func, line);
	std::vfprintf(stderr, str, args);
	std::fprintf(stderr, "\n%s", FANCY_COLOR_END);
	std::fflush(stderr);

	va_end(args);
}

inline void MkCheckf(const char *expr, const char *file,  int line, const char *func, const char *message, ...)
{
	va_list args;
	va_start(args, message);

	std::fprintf(stderr, "%sCHECK FAILED: %s (%s, line %d, %s)\n%s", FANCY_COLOR_RED_BEGIN, expr, file, line, func, FANCY_COLOR_END);
	std::vfprintf(stderr, message, args);
	std::fflush(stderr);

	va_end(args);
}

//------------------------------------------------------------------------------
//
inline void MkCheck(const char *expr, const char *file,  int line, const char *func)
{
	std::fprintf(stderr, "%sCHECK FAILED: %s (%s, line %d, %s)\n%s", FANCY_COLOR_RED_BEGIN, expr, file, line, func, FANCY_COLOR_END);
	std::fflush(stderr);
}

//------------------------------------------------------------------------------
//
inline void DebugTrace(const char *str, const char *file, const char *func,  int line)
{
	std::fprintf(stderr, "%sNOTE: %s\n      %s (line %d)\n      ", FANCY_COLOR_RED_BEGIN, file, func, line);
	std::fprintf(stderr, "%s", str);
	std::fprintf(stderr, "\n%s", FANCY_COLOR_END);
	std::fflush(stderr);
}

//------------------------------------------------------------------------------
//
inline void DebugTracef(const char *file, const char *func, int line, const char *str, ...)
{
	va_list args;
	va_start(args, str);

	std::fprintf(stderr, "%sNOTE: %s\n      %s (line %d)\n      ", FANCY_COLOR_RED_BEGIN, file, func, line);
	std::vfprintf(stderr, str, args);
	std::fprintf(stderr, "\n%s", FANCY_COLOR_END);
	std::fflush(stderr);

	va_end(args);
}


inline bool DebugVerify(bool checked, const char * expr, const char * file, int line, const char * func)
{
	if (checked)
		return true;

	char msg[4096] = {0};
	std::sprintf(msg + strlen(msg), "Expression: %s\n", expr);
	ShowError("Verification Failed", file, line, func, msg);
	return false;
}

inline bool DebugVerifyf(bool checked, const char * expr, const char * file, int line, const char * func, const char *message, ...)
{
	if (checked)
		return true;

	char msg[4096] = {0};
	std::sprintf(msg + strlen(msg), "Expression: %s\n\n", expr);

	va_list args;
	va_start(args, message);
	std::vsprintf(msg + strlen(msg), message, args);
	va_end(args);
	
	ShowError("Verification Failed", file, line, func, msg);
	return false;
}

#ifdef WIN32
inline void ShowError(const char *aMsgHeader, const char *file,  int line, const char *func, const char *aMsg)
{
	static int sIsShowingError = false;

	if (!sIsShowingError)
	{
		sIsShowingError = true;

		char msg[4096] = {0};
		std::sprintf(msg + strlen(msg), "File: %s\n", file);
		std::sprintf(msg + strlen(msg), "Line: %d\n", line);
		std::sprintf(msg + strlen(msg), "Function: %s\n", func);
		std::sprintf(msg + strlen(msg), "%s", aMsg);

		int msgboxID = MessageBoxA(NULL, msg, aMsgHeader, MB_ICONERROR | MB_ABORTRETRYIGNORE | MB_DEFBUTTON2);
		switch (msgboxID)
		{
		case IDABORT:
			exit(0);
			break;
		case IDRETRY:
			DEBUG_BREAK;
			break;
		case IDIGNORE:
			break;
		}

		sIsShowingError = false;
	}
}

#else

inline void ShowError(const char *aMsgHeader, const char *file,  int line, const char *func, const char *aMsg)
{
	const char msg[4096] = {0};
	std::sprintf(msg + strlen(msg), "%s\n\n", aMsg);
	std::sprintf(msg + strlen(msg), "File: %s\n", file);
	std::sprintf(msg + strlen(msg), "Line: %d\n", line);
	std::sprintf(msg + strlen(msg), "Function: %s", func);

	std::fprintf(stderr, "===============================================================================\n");
	std::fprintf(stderr, "[%s]\n", aMsgHeader);
 	std::fprintf(stderr, "-------------------------------------------------------------------------------\n");
	std::fprintf(stderr, "%s\n", msg);
 	std::fprintf(stderr, "===============================================================================\n");
 	std::fflush(stderr);
}

#endif


} // namespace seed




#endif // ] __GENERIC_DEVEL_DEBUG_INLINE_H__
