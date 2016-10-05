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
#ifndef __GENERIC_TIME_FREQUENCYTIMER__
#define __GENERIC_TIME_FREQUENCYTIMER__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "../Math/MovingAverage.h"
#include "IntervalTimer.h"

#ifdef GENERIC_NAMESPACE
namespace GENERIC_NAMESPACE {
#endif

//==============================================================================
//	CLASS FrequencyTimer
//==============================================================================
template<class _TICKER, int _SIZE>
class TickingAverage
{
public:
	typedef typename _TICKER::ReturnType _TYPE;

	TickingAverage(const _TICKER &ticker);
	TickingAverage();
	_TYPE tick();

private:
	MovingAverage<_TYPE, _SIZE> mHistory;
	_TICKER mTicker;
};

template <class TIMER>
class TimeIntervalTicker
{
public:
	typedef double ReturnType;
	ReturnType operator () ();

private:
	IntervalTimer<TIMER> mTimer;
};

//==============================================================================
//	CLASS FrequencyTimer
//==============================================================================
template<class TIMER, int SIZE=100>
class FrequencyTimer
{
private:
	TickingAverage<TimeIntervalTicker<TIMER>, 100> mAverage;
	double mValue;

public:
	FrequencyTimer();
	double tick();
	double frequency();
};

#ifdef GENERIC_NAMESPACE
}
#endif

//==============================================================================
//	INLINED CODE
//==============================================================================
#include "src/FrequencyTimer.inline.h"

#endif // __GENERIC_TIME_FREQUENCYTIMER__

