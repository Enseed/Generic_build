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
#ifndef __GENERIC_MATH_INTOPS__
#define __GENERIC_MATH_INTOPS__

//==============================================================================
//	MACROS
//==============================================================================


//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
//#include "boost/numeric/conversion/cast.hpp"
#include <typeinfo>
#include <stdint.h>

namespace seed {
//==============================================================================
//	CLASS IntUtils
//==============================================================================
class IntOps
{
public:
	//--------------------------------------------------------------------------
	//
	static int32_t safeInt32Add(int32_t a, int32_t b) throw(std::bad_cast)
	{
		long long lla = a;
		long long llb = b;
		
//		return boost::numeric_cast<int32_t>(lla+llb); // FIXME
		return lla+llb;
	}
	

	//--------------------------------------------------------------------------
	//
	static int32_t safeInt32Mult(int32_t a, int32_t b) throw(std::bad_cast)
	{
		long long lla = a;
		long long llb = b;
// 		return boost::numeric_cast<int32_t>(lla*llb); // FIXME
		return lla*llb;
	}
};

} // namespace seed


#endif // __GENERIC_MATH_INTOPS__
