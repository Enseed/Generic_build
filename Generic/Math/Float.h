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
#ifndef __GENERIC_MATH_FLOATUTILS__
#define __GENERIC_MATH_FLOATUTILS__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include <cmath>
#include <cfloat>
#include <string>

namespace seed {

template<class T>
class FloatEpsilon;

// FIXME find actual value, this is just a guess
template<> struct FloatEpsilon<float> {	static float value() 	{ return 0.0001f; } };
template<> struct FloatEpsilon<double> {	static double value() 	{ return 0.0000001; } };


//==============================================================================
//	CLASS Float
//==============================================================================
class Float
{
public:
	inline static double frexp(double value, int *exp);
	inline static double abs(double val);
	inline static double ceil(double val);
	inline static double floor(double val);
	inline static int round(double val);
	inline static float cos(float theta);
	inline static double cos(double theta);
	inline static float sin(float theta);
	inline static double sin(double theta);
	inline static double pow(double num, double exp);
	inline static float pow(float num, float exp);
	inline static double fmod(double a, double m);
	inline static float fmod(float a, float m);

	inline static std::string serialize(float var);
	inline static float deSerialize(const std::string &str);


#ifdef max
#undef max
#endif // def max
	template<class T> inline static T max(T a, T b);
	template<class T> inline static T max(T a, T b, T c) { return max(max(a, b), c); }
	template<class T> inline static T max(T a, T b, T c, T d) { return max(max(a, b), max(c, d)); }
	template<class T> inline static T max(T a, T b, T c, T d, T e) { return max(max(a, b), max(c, d), e); }
	template<class T> inline static T max(T a, T b, T c, T d, T e, T f) { return max(max(a, b), max(c, d), max(e, f)); }
	template<class T> inline static T max(T a, T b, T c, T d, T e, T f, T g) { return max(max(a, b), max(c, d), max(e, f), g); }
	template<class T> inline static T max(T a, T b, T c, T d, T e, T f, T g, T h) { return max(max(a, b), max(c, d), max(e, f), max(g, h)); }

#ifdef min
#undef min
#endif // def min
	template<class T> inline static T min(T a, T b);
	template<class T> inline static T min(T a, T b, T c) { return min(min(a, b), c); }
	template<class T> inline static T min(T a, T b, T c, T d) { return min(min(a, b), min(c, d)); }
	template<class T> inline static T min(T a, T b, T c, T d, T e) { return min(min(a, b), min(c, d), e); }
	template<class T> inline static T min(T a, T b, T c, T d, T e, T f) { return min(min(a, b), min(c, d), min(e, f)); }
	template<class T> inline static T min(T a, T b, T c, T d, T e, T f, T g) { return min(min(a, b), min(c, d), min(e, f), g); }
	template<class T> inline static T min(T a, T b, T c, T d, T e, T f, T g, T h) { return min(min(a, b), min(c, d), min(e, f), min(g, h)); }

	template<class T>
	static T epsilon()
	{
		return FloatEpsilon<T>::value();
	}

	template<class T>
	static bool epsilonEquals(const T &lhs, const T &rhs)
	{
		const T diff = lhs - rhs;
		return (diff < epsilon<T>()) && (-diff < epsilon<T>());
	}

	template<class T> inline static T clamp(T val, T minVal, T maxVal)
	{
		return min(max(val, minVal), maxVal);
	}

	enum 
	{
		kNumberOfMantissaDigits = FLT_MANT_DIG
	};
};

} // namespace seed


#include "src/Float.inline.h"

#endif // __GENERIC_MATH_FLOATUTILS__
