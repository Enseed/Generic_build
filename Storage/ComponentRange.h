/*******************************************************************************
 Copyright 2009 Enseed Inc. & Gaspard Petit <gaspardpetit@enseed.com>
 
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
*******************************************************************************/
#ifndef __ITL_COMPONENTRANGE_H__
#define __ITL_COMPONENTRANGE_H__

//==============================================================================
//	FILE ComponentRange.h
//==============================================================================
// Just a wrapper around numeric_limits which can be provided to define the
// default range of pixel components.
//
// USAGE:
//
//     DefaultRange<unsigned char>::max(); // will return 255;
//     DefaultRange<unsigned char>::min(); // will return 0;
//
//------------------------------------------------------------------------------

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include <limits>

// we should probably just use boost's integer_traits (e.g. integer_traits<T>::const_max)
template<class T>
class ConstRange;

template<> struct ConstRange<char> {
	static const char const_min = -128;
	static const char const_max = 127;
};

template<> struct ConstRange<double> {
	static const int const_min = 0;
	static const int const_max = 1;
};

template<> struct ConstRange<unsigned char> {
	static const unsigned char const_min = 0;
	static const unsigned char const_max = 255;
};

template<> struct ConstRange<unsigned short> {
	static const unsigned short const_min = 0;
	static const unsigned short const_max = 65535;
};

template<> struct ConstRange<unsigned long> {
	static const unsigned long const_min = 0;
	static const unsigned long const_max = 4294967295;
};

template<> struct ConstRange<float> {
	static const int const_min = 0;
	static const int const_max = 1;
};


//==============================================================================
//	CLASS DefaultRange
//==============================================================================
template<typename T>
class DefaultRange
{
public:
	static const int MIN_NUM = ConstRange<T>::const_min;
	static const int MIN_DEN = 1;
	static const int MAX_NUM = ConstRange<T>::const_max;
	static const int MAX_DEN = 1;

#ifdef min // windows defines min...
#undef min
#endif

#ifdef max // windows defines max...
#undef max
#endif

	static T min() { return std::numeric_limits<T>::min(); }
	static T max() { return std::numeric_limits<T>::max(); }
};


//==============================================================================
//	CLASS DefaultRange
//==============================================================================
template<typename T, int MIN_N, int MIN_D, int MAX_N, int MAX_D>
class ComponentRange
{
public:
	static const int MIN_NUM = MIN_N;
	static const int MIN_DEN = MIN_D;
	static const int MAX_NUM = MAX_N;
	static const int MAX_DEN = MAX_D;
	
	static T min() { return T(MIN_NUM) / T(MIN_DEN); }
	static T max() { return T(MAX_NUM) / T(MAX_DEN); }
};


template<int N>
struct TemplatePowerOf2;

template<int N>
struct TemplatePowerOf2 { static const int POW2 = 2*TemplatePowerOf2<N-1>::POW2; };

template<>
struct TemplatePowerOf2<0> { static const int POW2 = 1; };

//==============================================================================
//	CLASS DefaultRange
//==============================================================================
template<int NBBITS>
class BitRange
{
public:
	static const int MIN_NUM = 0;
	static const int MIN_DEN = 1;
	static const int MAX_NUM = TemplatePowerOf2<NBBITS>::POW2 - 1;
	static const int MAX_DEN = 1;
	
	static int min() { return (MIN_NUM) / (MIN_DEN); }
	static int max() { return (MAX_NUM) / (MAX_DEN); }
};


#endif // __ITL_COMPONENTRANGE_H__
