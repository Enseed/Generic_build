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
#ifndef __GENERIC_TIME_FREQUENCYTIMER_INLINE__
#define __GENERIC_TIME_FREQUENCYTIMER_INLINE__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "../FrequencyTimer.h"

#ifdef GENERIC_NAMESPACE
namespace GENERIC_NAMESPACE {
#endif

//==============================================================================
//	CLASS TickingAverage
//==============================================================================
template<class _TICKER, int _SIZE>
TickingAverage<_TICKER, _SIZE>::TickingAverage(const _TICKER &ticker)
:
	mTicker(ticker)
{}

template<class _TICKER, int _SIZE>
TickingAverage<_TICKER, _SIZE>::TickingAverage()
:
	mTicker()
{}

template<class _TICKER, int _SIZE>
typename TickingAverage<_TICKER, _SIZE>::_TYPE TickingAverage<_TICKER, _SIZE>::tick()
{
	mHistory.record(mTicker());
	return mHistory.average();
}

//==============================================================================
//	CLASS TimeIntervalTicker
//==============================================================================
template<class TIMER>
typename TimeIntervalTicker<TIMER>::ReturnType TimeIntervalTicker<TIMER>::operator () ()
{
	ReturnType elapsed = mTimer.stop();
	mTimer.start();
	return elapsed;
}

//==============================================================================
//	CLASS FrequencyTimer
//==============================================================================
template<class TIMER, int SIZE>
FrequencyTimer<TIMER, SIZE>::FrequencyTimer()
:
	mAverage()
{}

template<class TIMER, int SIZE>
double FrequencyTimer<TIMER, SIZE>::tick()
{
	mValue = mAverage.tick();
	return frequency();
}

template<class TIMER, int SIZE>
double FrequencyTimer<TIMER, SIZE>::frequency()
{
	if (mValue == 0)	return 0;
	return 1.0/mValue;
}

#ifdef GENERIC_NAMESPACE
}
#endif

#endif // __GENERIC_TIME_FREQUENCYTIMER_INLINE__

