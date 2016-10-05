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
#ifndef __GEOMETRY_BEZIER__
#define __GEOMETRY_BEZIER__

#include "../Devel/Debug.h"

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
namespace seed {

//==============================================================================
//	CLASS BSplineEvaluator
//==============================================================================

class BezierEvaluator
{
public:
	template<class T>
	static T evalQuadratic(const T &from, const T &control, const T &to, float t)
	{
		float b1 = (1-t)*(1-t);
		float b2 = 2*t*(1-t);
		float b3 = t*t;

		return (b1*from + b2*control + b3*to);
	}

	template<class T>
	static T evalCubic(const T &from, const T &control1, const T &control2, const T &to, float t)
	{
		float b1 = (1-t)*(1-t)*(1-t);
		float b2 = 3*t*(1-t)*(1-t);
		float b3 = 3*t*t*(1-t);
		float b4 = t*t*t;

		return (b1*from + b2*control1 + b3*control2 + b4*to);
	}
};

//==============================================================================
//	CLASS BSpline
//==============================================================================
class BezierCurve
{
public:
	template<class T, class ITER>
	static void evalQuadratic(const ITER begin, const ITER end, float t, T *val)
	{
		ASSERT(begin != end);
		
		int ptCount = end-begin;

		//---------------------------------------------------------------------
		// There are (n-1)/2 segments in the curve:
		//
		//      2
		//     ---
		//   -    -
		//  1       3       5
		//            -   -
		//             ---
		//              4
		//
		//---------------------------------------------------------------------
		int nbSegments = (ptCount-1)/2;

		int index = static_cast<int>(t*(nbSegments));
		if (index >= nbSegments)	*val = *(begin+ptCount-1);
		else if (index < 0)			*val = *(begin);
		else
		{
			int i1 = index*2+0;
			int i2 = index*2+1;
			int i3 = index*2+2;
		
			float scale = 1.0f / (nbSegments);

			t = (t-index*scale)/scale;
			*val = BezierEvaluator::evalQuadratic(*(begin+i1), *(begin+i2), *(begin+i3), t);
		}
	}

	template<class T, class ITER>
	static void evalCubic(const ITER begin, const ITER end, float t, T *val)
	{
		ASSERT(begin != end);
		
		int ptCount = end-begin;

		//---------------------------------------------------------------------
		// There are (n-1)/3 segments in the curve:
		//
		//  2       3
		//     ---
		//   -    -
		//  1       4       7
		//            -   -
		//             ---
		//          5       6
		//
		//---------------------------------------------------------------------
		int nbSegments = (ptCount-1)/3;

		int index = static_cast<int>(t*(nbSegments));
		if (index >= nbSegments)	*val = *(begin+ptCount-1);
		else if (index < 0)			*val = *(begin);
		else
		{
			int i1 = index*3+0;
			int i2 = index*3+1;
			int i3 = index*3+2;
			int i4 = index*3+3;
		
			float scale = 1.0f / (nbSegments);

			t = (t-index*scale)/scale;
			*val = BezierEvaluator::evalCubic(*(begin+i1), *(begin+i2), *(begin+i3), *(begin+i4), t);
		}
	}
};


} // namespace seed


#endif // __GEOMETRY_BEZIER__
