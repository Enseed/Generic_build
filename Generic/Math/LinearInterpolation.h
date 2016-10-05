/*******************************************************************************
 Copyright 2009 Enseed inc.
 
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

#ifndef __GENERIC_MATH_LINEARINTERPOLATION__
#define __GENERIC_MATH_LINEARINTERPOLATION__

namespace seed {

	
//================================================================================
//	CLASS LinearInterpolation
//================================================================================
// Interpolate between two values.   
// Range of interpolation is usually between 0 and 1.

template<class T>
class LinearInterpolation
{
public:
	static T compute(const T &start, const T &end, float value)
	{
//		return start * (1 - value) + end * value;
//		return start - start * value + end * value;
//		return start + end * value - start * value;
		return start + value * (end - start);
	}

	LinearInterpolation(const T &start, const T &end)
	:
		_start(start),
		_end(end)
	{}

	T compute(float value)
	{
		return compute(_start, _end, value);
	}

private:
	T _start;
	T _end;
};

} // namespace seed


#endif // __GENERIC_MATH_LINEARINTERPOLATION__