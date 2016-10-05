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
#ifndef __GENERIC_TIME_TIME__
#define __GENERIC_TIME_TIME__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "../Base/Base.h"
#include "../Math/Rational.h"

#ifdef GENERIC_NAMESPACE
namespace GENERIC_NAMESPACE {
#endif
//==============================================================================
//	CLASS Time
//==============================================================================
class Time
{
public:
	typedef Rational ClockRate;
	
public:
	inline static Time now();

	inline static Time fromSeconds(double seconds, const ClockRate &clock);

	inline static const Time& oneSecond();

	inline Time();	//	will be at 0:1:1
	inline Time(int64 value, const ClockRate &clock);
	inline Time(int64 value, int32 num, int32 denom);
	inline Time(const Time& rhs);

	inline bool operator == (const Time& rhs) const;
	inline bool operator != (const Time& rhs) const;

	inline bool operator < (const Time& rhs) const;
	inline bool operator <= (const Time& rhs) const;
	inline bool operator > (const Time& rhs) const;
	inline bool operator >= (const Time& rhs) const;

	inline Time operator + (int64 rhs) const;
	inline Time operator - (int64 rhs) const;
	inline Time operator * (int64 rhs) const;
	inline Time operator / (int64 rhs) const;

	inline Time& operator += (int64 rhs);
	inline Time& operator -= (int64 rhs);
	inline Time& operator *= (int64 rhs);
	inline Time& operator /= (int64 rhs);

	inline Time& operator = (const Time& rhs);
	
	inline Time convertToClock(ClockRate clock) const;
	inline Time convertToClock(int32 num, int32 denom) const;
	inline ClockRate commonClock(const Time &rhs);

	inline void setValue(int64 value);
	inline int64 valueForClock(int32 num, int32 denom) const;
	inline int64 valueForClock(ClockRate clock) const;
	
	inline int64 value()	const;
	inline ClockRate rate() const;

	inline double	inSeconds() const;
	inline double	seconds() const;
	inline int		minutes() const;
	inline int		hours() const;
	
private:
	int64		mValue;
	ClockRate	mRate;
};

static inline Time operator * (const int &lhs, const Time &rhs)
{
	return rhs * lhs;
}

#ifdef GENERIC_NAMESPACE
}
#endif

#include "src/Time.inline.h"

#endif // __GENERIC_TIME_TIME__
