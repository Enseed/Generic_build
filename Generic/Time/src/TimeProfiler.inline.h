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
#include "../TimeProfiler.h"

#ifdef GENERIC_NAMESPACE
namespace GENERIC_NAMESPACE {
#endif

//==============================================================================
//	CLASS TimeProfiler
//==============================================================================
//------------------------------------------------------------------------------
//
template<class _TIMER>
TimeProfiler::TimeProfiler()
:
	mIsCounting(false),
	mCycleTime(0,1,1),
	mTotalTime(0,1,1),
	mCycles(0)
{}
	
//------------------------------------------------------------------------------
//
template<class _TIMER>
TimeProfiler::TimeProfiler(const TimeProfiler &rhs)
:
	mIsCounting(rhs.mIsCounting),
	mCycleTime(rhs.mCycleTime),
	mTotalTime(rhs.mTotalTime),
	mCycles(rhs.mCycles)
{}

//------------------------------------------------------------------------------
//
template<class _TIMER>
TimeProfiler::~TimeProfiler()
{}

//------------------------------------------------------------------------------
//
template<class _TIMER>
TimeProfiler& TimeProfiler::operator=(const TimeProfiler &rhs)
{
	mIsCounting = rhs.mIsCounting;
	mCycleTime = rhs.mCycleTime;
	mTotalTime = rhs.mTotalTime;
	mCycles = rhs.mCycles;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class _TIMER>
void TimeProfiler::start()
{
	mTotalTime = Time(0,1,1);
	mCycleTime = Time(0,1,1);
	mCycles = 0;
	mTimer.start();
	mIsCounting = true;
}

//------------------------------------------------------------------------------
//
template<class _TIMER>
void TimeProfiler::pause()
{
	Time elapsed = mTimer.stop();

	mCycleTime = mCycleTime.convertToClock(elapsed.rate());
	mCycleTime += elapsed.value();
	mIsCounting = false;
}

//------------------------------------------------------------------------------
//
template<class _TIMER>
void TimeProfiler::resume()
{
	mTimer.start();
	mIsCounting = true;
}

//------------------------------------------------------------------------------
//
template<class _TIMER>
void TimeProfiler::endCycle()
{
	bool wasCounting = mIsCounting;
	
	if (wasCounting)
		pause();

	mTotalTime = mTotalTime.convertToClock(mCycleTime.rate());
	mTotalTime += mCycleTime.value();
	++mCycles;
	mCycleTime = Time(0,1,1);
	
	if (wasCounting)
		resume();
}

//------------------------------------------------------------------------------
//
template<class _TIMER>
void TimeProfiler::stop()
{
	mIsCounting = false;
}

//------------------------------------------------------------------------------
//
template<class _TIMER>
Time TimeProfiler::averageTime()
{
	if (mCycles == 0)	return Time(0,1,1);
	return mTotalTime / mCycles;
}

//------------------------------------------------------------------------------
//
template<class _TIMER>
Time TimeProfiler::totalTime()
{
	return mTotalTime;
}

//------------------------------------------------------------------------------
//
template<class _TIMER>
int TimeProfiler::cycles()
{
	return mCycles;
}

#ifdef GENERIC_NAMESPACE
}
#endif

