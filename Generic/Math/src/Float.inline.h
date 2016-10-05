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
#ifndef __GENERIC_MATH_FLOATUTILS_INLINE__
#define __GENERIC_MATH_FLOATUTILS_INLINE__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "../Float.h"
#include <cmath>
#include <sstream>
#include <string.h>

namespace seed {

//==============================================================================
//	CLASS Float
//==============================================================================
double Float::frexp(double value, int *exp)
{
	return std::frexp(value, exp);
}

double Float::abs(double val)
{
	return std::fabs(val);
}

double Float::ceil(double val)
{
	return std::ceil(val);
}

double Float::floor(double val)
{
	return std::floor(val);
}

int Float::round(double val)
{
	if (val > 0)
		return static_cast<int>(val + 0.5);
	else
		return static_cast<int>(val - 0.5);
}

float Float::cos(float theta)
{
	return ::cos(theta);
}

double Float::cos(double theta)
{
	return ::cos(theta);
}

float Float::sin(float theta)
{
	return ::sin(theta);
}

double Float::sin(double theta)
{
	return ::sin(theta);
}

double Float::pow(double num, double exp)
{
	return ::pow(num, exp);
}

float Float::pow(float num, float exp)
{
	return ::pow(num, exp);
}

double Float::fmod(double a, double m)
{
	return ::fmod(a, m);
}

float Float::fmod(float a, float m)
{
	return ::fmod(a, m);
}

std::string Float::serialize(float var)
{
	std::stringstream strstream;
	strstream << var;
	return strstream.str();
}

float Float::deSerialize(const std::string &str)
{
	float retVal = 0;
	std::stringstream strstream(str);
	strstream >> retVal;
	return retVal;
}

template<class T>
T Float::max(T a, T b)
{
	return a > b ? a : b;
}

template<class T>
T Float::min(T a, T b)
{
	return a < b ? a : b;
}

} // namespace seed


#endif // __MK_MATH_FLOAT_INLINE__
