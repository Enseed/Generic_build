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
#ifndef __GENERIC_DEBUG__
#define __GENERIC_DEBUG__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "../Base/Base.h"

#include <cstdarg>
#include <cstdio>
#include <cstdlib>

namespace seed {

//------------------------------------------------------------------------------
//
inline void DebugDie(const char *file,  int line, const char *func);
inline void DebugDief(const char *file,  int line, const char * func, const char *message, ...);

#define DIE()			do {	seed::DebugDie(__FILE__, __LINE__, GENERIC_CURRENT_FUNCTION_NAME);	} while (false)
#define DIEF(str, ...)	do {	seed::DebugDief(__FILE__, __LINE__, GENERIC_CURRENT_FUNCTION_NAME, str, ## __VA_ARGS__);	} while(false)

//==============================================================================
//	DEBUG MACROS
//==============================================================================
#ifndef TARGET_DEBUG

#define FIXMEF(str, ...)	do {} while(false)
#define FIXME(str)			do {} while(false)

#define ASSERT(expr)		do {} while(false)
#define ASSERTF(expr, message, ...)	do {} while(false)

#define ASSERT_ELSE(expr, alternative) do { if (!(expr)) {alternative} } while (false)
#define ASSERTF_ELSE(expr, alternative, message, ...) do { if (!(expr)) {alternative} } while (false)

#define CHECK(expr)			do {} while(false)
#define CHECKF(expr, message, ...)	do {} while(false)

#define CHECK_ELSE(expr, alternative) do { if (!(expr)) {alternative} } while (false)
#define CHECKF_ELSE(expr, alternative, message, ...) do { if (!(expr)) {alternative} } while (false)

#define TRACE(str)		do {} while(false)
#define TRACEF(str, ...)	do {} while(false)

#define VERIFY(str)		(!!(str))
#define VERIFYF(str, ...)	(!!(str))

#else

//==============================================================================
//	FIXME
//==============================================================================

//	FIXME is intended to print an annoying message at runtime about something
//	that is not done correctly in the code.  Alternatively, you may put
//	FIXME in comments, and we will occasionally search our code base for FIXME
//	comments. But when it's very important, nothing beats a runtime FIXME!
inline void DebugFixmef(const char *file, const char *func, int line, const char *str, ...);
inline void DebugFixme(const char *str, const char *file, const char *func, int line);

#define FIXME(str)			do {	seed::DebugFixme(str, __FILE__, GENERIC_CURRENT_FUNCTION_NAME, __LINE__);	} while (false)
#define FIXMEF(str, ...)	do {	seed::DebugFixmef(__FILE__, GENERIC_CURRENT_FUNCTION_NAME, __LINE__, str, ## __VA_ARGS__);	} while(false)

//==============================================================================
//	ASSERT
//==============================================================================
//	ASSERT will print a message and exit if the expression fails
inline void DebugAssert(const char * expr, const char * file, int line, const char * func);
inline void DebugAssertf(const char * expr, const char * file, int line, const char * func, const char *message, ...);

#ifndef ASSERT
#define ASSERT(expr)		do {	if (!(expr))	seed::DebugAssert(#expr, __FILE__, __LINE__, GENERIC_CURRENT_FUNCTION_NAME);	} while (false)
#define ASSERT_ELSE(expr, alternative) do { if (!(expr)) { seed::DebugAssert(#expr, __FILE__, __LINE__, GENERIC_CURRENT_FUNCTION_NAME); {alternative} } } while (false)
#endif

//	ASSERTF will print a message and exit if the expression fails
#define ASSERTF(expr, message, ...)	do {	if (!(expr))	seed::DebugAssertf(#expr, __FILE__, __LINE__, GENERIC_CURRENT_FUNCTION_NAME, message, ## __VA_ARGS__);	} while(false)
#define ASSERTF_ELSE(expr, alternative, message, ...) do { if (!(expr)) { seed::DebugAssertf(#expr, __FILE__, __LINE__, GENERIC_CURRENT_FUNCTION_NAME, message, ## __VA_ARGS__); {alternative} } } while (false)

//==============================================================================
//	CHECK
//==============================================================================
//	CHECK will print a message if the expression fails but will continue.
//------------------------------------------------------------------------------
//
inline void MkCheckf(const char * expr, const char * file, int line, const char * func, const char *message, ...);
inline void MkCheck(const char * expr, const char * file, int line, const char * func);

#define CHECK(expr)		do {	if (!(expr))	seed::MkCheck(#expr, __FILE__, __LINE__, GENERIC_CURRENT_FUNCTION_NAME);	} while (false)
#define CHECK_ELSE(expr, alternative) do { if (!(expr)) { seed::MkCheck(#expr, __FILE__, __LINE__, GENERIC_CURRENT_FUNCTION_NAME); {alternative} } } while (false)
#define CHECKF(expr, message, ...)		do {	if (!(expr))	seed::MkCheckf(#expr, __FILE__, __LINE__, GENERIC_CURRENT_FUNCTION_NAME, message, ## __VA_ARGS__);	} while(false)
#define CHECKF_ELSE(expr, alternative, message, ...) do { if (!(expr)) { seed::MkCheckf(#expr, __FILE__, __LINE__, GENERIC_CURRENT_FUNCTION_NAME, message, ## __VA_ARGS__); {alternative} } } while (false)

//==============================================================================
//	TRACE
//==============================================================================
//	TRACE is intended to print some traces of execution and be sure that nothing is done in release mode
inline void DebugTracef(const char *file, const char *func, int line, const char *str, ...);
inline void DebugTrace(const char *str, const char *file, const char *func, int line);

#define TRACE(str)		do {	seed::DebugTrace(str, __FILE__, GENERIC_CURRENT_FUNCTION_NAME, __LINE__);	} while(false)
#define TRACEF(str, ...)	do {	seed::DebugTracef(__FILE__, GENERIC_CURRENT_FUNCTION_NAME, __LINE__, str, ## __VA_ARGS__);	} while(false)

//==============================================================================
//	VERIFY
//==============================================================================
//	VERIFY returns whether the condition is true or false. In addition, in debug,
//	it will also assert.
inline bool DebugVerify(bool checked, const char * expr, const char * file, int line, const char * func);
inline bool DebugVerifyf(bool checked, const char * expr, const char * file, int line, const char * func, const char *message, ...);

#define VERIFY(expr) seed::DebugVerify(!!(expr), #expr, __FILE__, __LINE__, GENERIC_CURRENT_FUNCTION_NAME)
#define VERIFYF(expr, message, ...)	seed::DebugVerifyf(!!(expr), #expr, __FILE__, __LINE__, GENERIC_CURRENT_FUNCTION_NAME, message, ## __VA_ARGS__)

#endif	//	TARGET_DEBUG

} // namespace seed

#include "src/Debug.inline.h"

#endif // __GENERIC_DEBUG__
