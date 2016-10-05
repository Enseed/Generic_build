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
#ifndef __GENERIC_BASE_ENDIAN__
#define __GENERIC_BASE_ENDIAN__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "Types.h"

//------------------------------------------------------------------------------
// Swap Macros
#define GENERIC_SWAP64_MACRO(val) \
	((((val) & 0xFF00000000000000ULL) >> 56) | (((val) & 0x00FF000000000000ULL) >> 40) | \
	 (((val) & 0x0000FF0000000000ULL) >> 24) | (((val) & 0x000000FF00000000ULL) >>  8) | \
	 (((val) & 0x00000000FF000000ULL) <<  8) | (((val) & 0x0000000000FF0000ULL) << 24) | \
	 (((val) & 0x000000000000FF00ULL) << 40) | (((val) & 0x00000000000000FFULL) << 56))
#define GENERIC_SWAP32_MACRO(val) ((((val) >> 24) & 0x000000FF) | (((val) >> 8) & 0x0000FF00) | \
							  (((val) << 8) & 0x00FF0000) | (((val) << 24) & 0xFF000000))
#define GENERIC_SWAP16_MACRO(val) ((((val) >> 8) & 0x00FF) | (((val) << 8) & 0xFF00))

#define GENERIC_SWAP64(val) GENERIC_SWAP64_MACRO(val)
#define GENERIC_SWAP32(val) GENERIC_SWAP32_MACRO(val)
#define GENERIC_SWAP16(val) GENERIC_SWAP16_MACRO(val)

static inline float GENERIC_SWAP32F(float v)
{
	uint32 *i32v = (uint32*)&v;
	*i32v = GENERIC_SWAP32(*i32v);
	return *(float*)i32v;
}

static inline double GENERIC_SWAP64F(double v)
{
	uint64 *i64v = (uint64*)&v;
	*i64v = GENERIC_SWAP64(*i64v);
	return *(double*)i64v;
}

//------------------------------------------------------------------------------
// IO Based on Endianness
#ifdef TARGET_BIG_ENDIAN
#define _TOBE32(val) (val)
#define _TOBE16(val) (val)
#define _TOLE32(val) GENERIC_SWAP32(val)
#define _TOLE16(val) GENERIC_SWAP16(val)
#define _TOBE32F(val) (val)
#define _TOBE64F(val) (val)
#define _TOLE32F(val) GENERIC_SWAP32F(val)
#define _TOLE64F(val) GENERIC_SWAP64F(val)
#define _32BIT_BYTE0_OFFSET 24
#define _32BIT_BYTE1_OFFSET 16
#define _32BIT_BYTE2_OFFSET 8
#define _32BIT_BYTE3_OFFSET 0
#else
#define _TOBE32(val) GENERIC_SWAP32(val)
#define _TOBE16(val) GENERIC_SWAP16(val)
#define _TOLE32(val) (val)
#define _TOLE16(val) (val)
#define _TOBE32F(val) GENERIC_SWAP32F(val)
#define _TOBE64F(val) GENERIC_SWAP64F(val)
#define _TOLE32F(val) (val)
#define _TOLE64F(val) (val)
#define _32BIT_BYTE0_OFFSET 0
#define _32BIT_BYTE1_OFFSET 8
#define _32BIT_BYTE2_OFFSET 16
#define _32BIT_BYTE3_OFFSET 24
#endif

#define _FROMBE32(val) _TOBE32(val)
#define _FROMBE16(val) _TOBE16(val)
#define _FROMLE32(val) _TOLE32(val)
#define _FROMLE16(val) _TOLE16(val)
#define _FROMBE32F(val) _TOBE32F(val)
#define _FROMBE64F(val) _TOBE64F(val)
#define _FROMLE32F(val) _TOLE32F(val)
#define _FROMLE64F(val) _TOLE64F(val)

#endif	//	__GENERIC_BASE_ENDIAN__
