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
#ifndef __ITL_PIXELCONVERTER_RANGE_H__
#define __ITL_PIXELCONVERTER_RANGE_H__

//==============================================================================
// CLASS ConvertComponentRange
//==============================================================================
template<
	typename SRC_STORAGE, typename DST_STORAGE,

	typename SRC_COMPONENT=typename SRC_STORAGE::ComponentType,
	int SRC_MIN_NUM=SRC_STORAGE::MIN_NUM, int SRC_MIN_DEN=SRC_STORAGE::MIN_DEN,
	int SRC_MAX_NUM=SRC_STORAGE::MAX_NUM, int SRC_MAX_DEN=SRC_STORAGE::MAX_DEN,

	typename DST_COMPONENT=typename DST_STORAGE::ComponentType,
	int DST_MIN_NUM=DST_STORAGE::MIN_NUM, int DST_MIN_DEN=DST_STORAGE::MIN_DEN,
	int DST_MAX_NUM=DST_STORAGE::MAX_NUM, int DST_MAX_DEN=DST_STORAGE::MAX_DEN>
struct ConvertComponentRange
{
	static DST_COMPONENT eval(const SRC_COMPONENT &src)
	{
		const SRC_COMPONENT smin = SRC_COMPONENT(SRC_MIN_NUM) / SRC_COMPONENT(SRC_MIN_DEN);
		const SRC_COMPONENT smax = SRC_COMPONENT(SRC_MAX_NUM) / SRC_COMPONENT(SRC_MAX_DEN);
		const DST_COMPONENT dmin = DST_COMPONENT(DST_MIN_NUM) / DST_COMPONENT(DST_MIN_DEN);
		const DST_COMPONENT dmax = DST_COMPONENT(DST_MAX_NUM) / DST_COMPONENT(DST_MAX_DEN);
		
		// range = max - min might not be representable in the component's type
		// e.g. 
		//		uint8 max = 127, min = -128;
		//		uint8 range = max - min; // we expect 255, but we get -1
		
		// Eventually, we'd want to use the unsigned type, or figure out a way
		// to do these conversions safely.  For instance, using an unsigned int
		// to compute the new value of an int component will not be good enough
		// since we might overflow:
		//		src * srange / drange overflows with int
		//
		// so for the moment, we keep it safe using a double and we'll
		// specialize and fix later...
		
		const double srange = smax - smin;
		const double drange = dmax - dmin;
		
		float temp1 = float(src - smin) / float(srange);
		if (temp1 < 0) temp1 = 0;
		if (temp1 > 1) temp1 = 1;
		double temps2 = temp1 * drange + dmin;
		return DST_COMPONENT(temps2);
//		return DST_COMPONENT((src - smin) * drange / srange) + dmin; 
	}
};

// special case, src range is [0-1]
template<typename SRC_STORAGE, typename DST_STORAGE, typename SRC_COMPONENT, typename DST_COMPONENT, int DST_MIN, int DST_MAX>
struct ConvertComponentRange<SRC_STORAGE, DST_STORAGE, SRC_COMPONENT, 0, 1, 1, 1, DST_COMPONENT, DST_MIN, 1, DST_MAX, 1>
{
	static DST_COMPONENT eval(const SRC_COMPONENT &src)
	{
		const DST_COMPONENT dmin = DST_MIN;
		const DST_COMPONENT dmax = DST_MAX;
		
		// we could consider using an unsigned type here, but check for overflow
		const double drange = dmax - dmin;
		
		double tmp = src;
		if (tmp < 0) tmp = 0;
		if (tmp > 1) tmp = 1;

		return DST_COMPONENT(tmp * drange) + dmin; 
	}
};

// special case, dst range is [0-1]
template<typename SRC_STORAGE, typename DST_STORAGE, typename SRC_COMPONENT, int SRC_MIN, int SRC_MAX, typename DST_COMPONENT>
struct ConvertComponentRange<SRC_STORAGE, DST_STORAGE, SRC_COMPONENT, SRC_MIN, 1, SRC_MAX, 1, DST_COMPONENT, 0, 1, 1, 1>
{
	static DST_COMPONENT eval(const SRC_COMPONENT &src)
	{
		const SRC_COMPONENT smin = SRC_MIN;
		const SRC_COMPONENT smax = SRC_MAX;
				
		const double srange = smax - smin;

		return DST_COMPONENT((src - smin) / srange); 
	}
};


// special case, src and dst range is [0-1]
template<typename SRC_STORAGE, typename DST_STORAGE, typename SRC_COMPONENT, typename DST_COMPONENT>
struct ConvertComponentRange<SRC_STORAGE, DST_STORAGE, SRC_COMPONENT, 0, 1, 1, 1, DST_COMPONENT, 0, 1, 1, 1>
{
	static DST_COMPONENT eval(const SRC_COMPONENT &src)
	{
		return DST_COMPONENT(src);
	}
};


// special case, src range = dst range (no conversion required)
template<typename SRC_STORAGE, typename DST_STORAGE, typename SRC_COMPONENT, int MIN_NUM, int MIN_DEN, int MAX_NUM, int MAX_DEN, typename DST_COMPONENT> 
struct  ConvertComponentRange<SRC_STORAGE, DST_STORAGE, SRC_COMPONENT, MIN_NUM, MIN_DEN, MAX_NUM, MAX_DEN, DST_COMPONENT, MIN_NUM, MIN_DEN, MAX_NUM, MAX_DEN>
{
	static DST_COMPONENT eval(const SRC_COMPONENT &src)
	{	return DST_COMPONENT(src);	}
};

#endif // __ITL_PIXELCONVERTER_RANGE_H__



