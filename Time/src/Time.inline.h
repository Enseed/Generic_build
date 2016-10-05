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
//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "../Time.h"
#include "../../Math/Float.h"
#include "../../Devel/Debug.h"

#ifdef GENERIC_NAMESPACE
namespace GENERIC_NAMESPACE {
#endif

//==============================================================================
//	CLASS Time
//==============================================================================
//------------------------------------------------------------------------------
//
//Time Time::endOfTheWorld()
//{
//	// make this 10 days from now... 
//	// (why do I have the feeling that I am doing something wrong?)
//	Time ahora = now();
//	return ahora + (10 * 24 * 60 * 60 * Time::oneSecond()).valueForClock(ahora.rate());
//}

//------------------------------------------------------------------------------
//
Time Time::fromSeconds(double seconds, const ClockRate &clock)
{
	double scaled = seconds * clock.toDouble();
	int64 rounded;
	if (scaled > 0)
		rounded = static_cast<int64>(scaled + 0.5);
	else
		rounded = static_cast<int64>(scaled - 0.5);

	return Time(rounded, clock);
}

//------------------------------------------------------------------------------
//
const Time& Time::oneSecond()
{
	static Time sOneSecond(1, 1, 1);
	return sOneSecond;
}

//------------------------------------------------------------------------------
//
Time::Time()
:
	mValue(0),
	mRate(1, 1)
{}

//------------------------------------------------------------------------------
//
Time::Time(int64 value, const ClockRate &clock)
:
	mValue(value),
	mRate(clock)
{}

//------------------------------------------------------------------------------
//
Time::Time(int64 value, int32 num, int32 denom)
:
	mValue(value),
	mRate(num, denom)
{}

//------------------------------------------------------------------------------
//
Time::Time(const Time& rhs)
:
	mValue(rhs.mValue),
	mRate(rhs.mRate)
{}

//------------------------------------------------------------------------------
//
bool Time::operator == (const Time& rhs) const
{
	return ((mValue == rhs.mValue) && (mRate == rhs.mRate));
}

//------------------------------------------------------------------------------
//
bool Time::operator != (const Time& rhs) const
{
	return ((mValue != rhs.mValue) || (mRate != rhs.mRate));
}

//------------------------------------------------------------------------------
//
bool Time::operator < (const Time& rhs) const
{
	return mValue * mRate.denominator() * rhs.mRate.numerator() < rhs.mValue * rhs.mRate.denominator() * mRate.numerator();
}

//------------------------------------------------------------------------------
//
bool Time::operator <= (const Time& rhs) const
{
	return mValue * mRate.denominator() * rhs.mRate.numerator() <= rhs.mValue * rhs.mRate.denominator() * mRate.numerator();
}

//------------------------------------------------------------------------------
//
bool Time::operator > (const Time& rhs) const
{
	return mValue * mRate.denominator() * rhs.mRate.numerator() > rhs.mValue * rhs.mRate.denominator() * mRate.numerator();
}

//------------------------------------------------------------------------------
//
bool Time::operator >= (const Time& rhs) const
{
	return mValue * mRate.denominator() * rhs.mRate.numerator() >= rhs.mValue * rhs.mRate.denominator() * mRate.numerator();
}

//------------------------------------------------------------------------------
//
Time& Time::operator = (const Time& rhs)
{
	mValue = rhs.mValue;
	mRate = rhs.mRate;
	return *this;
}

//------------------------------------------------------------------------------
//
Time Time::operator + (int64 rhs) const
{
	Time t = *this;
	t += rhs;
	return t;
}

//------------------------------------------------------------------------------
//
Time Time::operator - (int64 rhs) const
{
	Time t = *this;
	t -= rhs;
	return t;
}

//------------------------------------------------------------------------------
//
Time Time::operator * (int64 rhs) const
{
	Time t = *this;
	t *= rhs;
	return t;
}

//------------------------------------------------------------------------------
//
Time Time::operator / (int64 rhs) const
{
	Time t = *this;
	t /= rhs;
	return t;
}

//------------------------------------------------------------------------------
//
Time& Time::operator += (int64 rhs)
{
//	FIXME("Should check for overflows!");
	setValue(value() + rhs);
	return *this;
}

//------------------------------------------------------------------------------
//
Time& Time::operator -= (int64 rhs)
{
//	FIXME("Should check for underflows!");
	setValue(value() - rhs);
	return *this;
}

//------------------------------------------------------------------------------
//
Time& Time::operator *= (int64 rhs)
{
//	FIXME("Should check for overflows!");
	setValue(value() * rhs);
	return *this;
}

//------------------------------------------------------------------------------
//
Time& Time::operator /= (int64 rhs)
{
	setValue(value() / rhs);
	return *this;
}

//------------------------------------------------------------------------------
//
Time Time::convertToClock(ClockRate clock) const
{
	int64 num = rate().numerator() * clock.denominator();
	int64 denom = rate().denominator() * clock.numerator();

	ASSERT(num != 0);

	int64 newValue = static_cast<int64>(value() * (static_cast<double>(denom) / num));
	// should round
	return Time(newValue, clock);
}

//------------------------------------------------------------------------------
//
int64 Time::valueForClock(ClockRate clock) const
{
	return convertToClock(clock).value();
}


//------------------------------------------------------------------------------
//
Time Time::convertToClock(int32 num, int32 denom) const
{
	return convertToClock(ClockRate(num, denom));
}

//------------------------------------------------------------------------------
//
int64 Time::valueForClock(int32 num, int32 denom) const
{
	return convertToClock(num, denom).value();
}

//------------------------------------------------------------------------------
//
double Time::seconds() const
{
	return inSeconds() - ( (hours() * 60 + minutes()) * 60 );
}

//------------------------------------------------------------------------------
//
int Time::minutes() const
{
	return static_cast<int>( (inSeconds() / 60) - hours() * 60 );
}

//------------------------------------------------------------------------------
//
int Time::hours() const
{
	return static_cast<int>( (inSeconds() / 3600) );
}

//------------------------------------------------------------------------------
//
int64 Time::value()	const
{
	return mValue;
}

Time::ClockRate Time::commonClock(const Time &rhs)
{
	ClockRate cr1 = ~mRate;
	ClockRate cr2 = ~rhs.mRate;
	
	ClockRate::putOnLCD(&cr1, &cr2);
	
	if (cr1.numerator() == cr2.numerator())
		return ~cr1;
	else
		return ~ClockRate(1, cr1.denominator());
}

//------------------------------------------------------------------------------
//
void Time::setValue(int64 value)
{
	mValue = value;
}

//------------------------------------------------------------------------------
//
Time::ClockRate Time::rate() const
{
	return mRate;
}

//------------------------------------------------------------------------------
//
double Time::inSeconds() const
{
	return static_cast<double>(mValue) / mRate.toDouble();
}

#ifdef GENERIC_NAMESPACE
}
#endif
