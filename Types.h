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
#ifndef __GENERIC_BASE_TYPES__
#define __GENERIC_BASE_TYPES__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "Config.h"


#ifdef __cplusplus
extern "C" {
#endif


//------------------------------------------------------------------------------
//	Basic types
#if defined( TARGET_ADOBE_TYPES )
typedef int64_t		int64;
typedef uint64_t			uint64;
typedef int64_t		sint64;
typedef signed long			int32;
typedef unsigned long		uint32;
typedef signed long			sint32;
typedef unsigned int		uint;
typedef signed int			sint;
typedef int16_t		int16;
typedef uint16_t			uint16;
typedef int16_t		sint16;
typedef int8_t		int8;
typedef uint8_t				uint8;
typedef int8_t		sint8;
typedef intptr_t			intptr;

/*#elif defined ( TARGET_TIFF_TYPES )

typedef int64_t		int64;
typedef uint64_t			uint64;
typedef int64_t		sint64;
typedef signed int			int32;
typedef unsigned int		uint32;
typedef signed int			sint32;
typedef unsigned int		uint;
typedef signed int			sint;
typedef int16_t		int16;
typedef uint16_t			uint16;
typedef int16_t				sint16;
typedef int8_t				int8;
typedef uint8_t				uint8;
typedef signed char			sint8;
typedef intptr_t			intptr;

*/
#else

typedef int64_t				int64;
typedef uint64_t			uint64;
typedef int64_t				sint64;
typedef int32_t				int32;
typedef uint32_t			uint32;
typedef int32_t				sint32;
typedef unsigned int		uint;
typedef signed int			sint;
typedef int16_t				int16;
typedef uint16_t			uint16;
typedef int16_t				sint16;
typedef int8_t				int8;
typedef uint8_t				uint8;
typedef int8_t				sint8;
typedef uintptr_t			intptr;


#endif

/// strings
typedef uint8				char8;
typedef uint16				char16;
typedef uint32				char32;
typedef wchar_t				wchar; // utf character, size is according to compiler



#ifdef __cplusplus


}
#endif

#endif // __GENERIC_BASE_TYPES__
