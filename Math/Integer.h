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
#ifndef __GENERIC_MATH_INTEGER__
#define __GENERIC_MATH_INTEGER__

//==============================================================================
//	MACROS
//==============================================================================

#ifdef MK_DEBUG
#include "IntOps.h"
#endif

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "../Base/Types.h"
#include <cstdlib>
#include <climits>
#include <string>
#include <sstream>

// windows.h #define min and max
#undef min
#undef max

namespace seed {
//==============================================================================
//	CLASS Integer
//==============================================================================
class Integer
{
public:
	//	Returns the greatest power of 2 smaller than the value
	static uint32 floorPow2( uint32 x )
	{
		//	From Hacker's Delight, First Edition, p.46
		//	This code could be otimized on processors with 
		//	an instruction to count the number of leading zeros (nlz), see
		//	the book if you need to optimize this...
		
		x = x | (x >> 1);
		x = x | (x >> 2);
		x = x | (x >> 4);
		x = x | (x >> 8);
		x = x | (x >> 16);

		return x - (x >> 1);
	}

	//	Returns the smallest power of 2 greater than the value
	static uint32 ceilPow2( uint32 x )
	{
		//	From Hacker's Delight, First Edition, p.47
		x = x - 1;
		x = x | (x >> 1);
		x = x | (x >> 2);
		x = x | (x >> 4);
		x = x | (x >> 8);
		x = x | (x >> 16);

		return x + 1;
	}

	// Returns 2 to the power of x.
	static uint32 pow2( uint32 x )
	{
		return uint32(1 << x);
	}

	static bool isPow2(uint32 value)
	{
		return (value & (~value + 1)) == value;
		
		// value & (value - 1) would be faster...
	}

	static int min(int v1, int v2)
	{
		return v1 < v2 ? v1 : v2;
	}
		
	static int max(int v1, int v2)
	{
		return v1 < v2 ? v2 : v1;
	}

	static uint abs(int val)
	{
		return uint(::abs(val));
	}

	static int gcd(int a, int b)
	{
		int min = Integer::min((int)Integer::abs(a), (int)Integer::abs(b));
		int max = Integer::max((int)Integer::abs(a), (int)Integer::abs(b));

		// gcd(x, 0) == abs(x)
		if (min == 0)
			return max;

		// Find gcd(a, b) using the Euclid's algorithm
		int mod;
		while ((mod = max % min) > 0)
		{
			max = min;
			min = mod;
		}

		if (min == 0)
			return 1;
		else
			return min;
	}
	
	inline static std::string serialize(int var)
	{
		std::stringstream strstream;
		strstream << var;
		return strstream.str();
	}

	inline static int deSerialize(const std::string &str)
	{
		int retVal = 0;
		std::stringstream strstream(str);
		strstream >> retVal;
		return retVal;
	}

	static int lcm(int a, int b) throw()
	{
#ifdef MK_DEBUG
		return IntOps::safeInt32Mult(a, b) / gcd(a, b);
#else
		return a * b / gcd(a, b);
#endif
	}
	
	static signed int sintMin() { return INT_MIN; }
	static signed int sintMax() { return INT_MAX; }
};

} // namespace seed


#endif // __GENERIC_MATH_INTEGER__
