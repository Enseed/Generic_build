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
#ifndef __GENERIC_MATH_MATH__
#define __GENERIC_MATH_MATH__

//==============================================================================
//	MACROS
//==============================================================================

// windows.h #define min and max
#undef min
#undef max

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================

#ifdef GENERIC_NAMESPACE
namespace GENERIC_NAMESPACE {
#endif

//==============================================================================
//	CLASS IntUtils
//==============================================================================
class Math
{
public:
	template <class T>
	static T min(const T &v1, const T &v2)
	{
		return v1 < v2 ? v1 : v2;
	}
		
	template <class T>
	static T max(const T &v1, const T &v2)
	{
		return v1 < v2 ? v2 : v1;
	}
};

#ifdef GENERIC_NAMESPACE
}
#endif

#endif // __GENERIC_MATH_MATH__
