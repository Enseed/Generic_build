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
#ifndef __GEOMETRY_BSPLINE__
#define __GEOMETRY_BSPLINE__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
namespace seed {

//==============================================================================
//	CLASS BSplineEvaluator
//==============================================================================

class BSplineEvaluator
{
public:
	template<class T>
	static T eval(const T &p1, const T &p2, const T &p3, const T &p4, float t)
	{
		float t2 = t*t;
		float t3 = t*t2;

		float b1 =      -t3 + 3.0f*t2 - 3.0f*t + 1.0f;
		float b2 =  3.0f*t3 - 6.0f*t2          + 4.0f;
		float b3 = -3.0f*t3 + 3.0f*t2 + 3.0f*t + 1.0f;
		float b4 =       t3;

		return (b1*p1 + b2*p2 + b3*p3 + b4*p4) / 6.0f;
	}
};

//==============================================================================
//	CLASS BSpline
//==============================================================================
class BSpline
{
public:
	template<class T, class ITER>
	static void evalClose(const ITER begin, const ITER end, float t, T *val)
	{
		ASSERT(begin != end);
		
		int ptCount = end-begin;

		int index = static_cast<int>(t*(ptCount-1));
		
		int i1 = index - 1;
		int i2 = index;
		int i3 = index + 1;
		int i4 = index + 2;
		
		if (i1 < 0)			i1 = 0;
		if (i3 >= ptCount)	i3 = ptCount-1;
		if (i4 >= ptCount)	i4 = ptCount-1;
		
		float scale = 1.0f / (ptCount-1);

		t = (t-index*scale)/scale;
		*val = BSplineEvaluator::eval(*(begin+i1), *(begin+i2), *(begin+i3), *(begin+i4), t);
	}
};


} // namespace seed


#endif // __GEOMETRY_BSPLINE__
