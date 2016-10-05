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
#ifndef __GENERIC_MATH_MOVINGAVERAGE_INLINE__
#define __GENERIC_MATH_MOVINGAVERAGE_INLINE__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "../MovingAverage.h"

#ifdef GENERIC_NAMESPACE
namespace GENERIC_NAMESPACE {
#endif

//==============================================================================
//	CLASS MovingQueue
//==============================================================================
template<class _TYPE, int _SIZE>
MovingQueue<_TYPE, _SIZE>::MovingQueue()
:
	mHistory(),
	mSampleCount()
{}

template<class _TYPE, int _SIZE>
void MovingQueue<_TYPE, _SIZE>::record(const _TYPE &value)
{
	mHistory.push_back(value);
	if (mHistory.size() > _SIZE)
		mHistory.erase(mHistory.begin());
}

template<class _TYPE, int _SIZE>
_TYPE& MovingQueue<_TYPE, _SIZE>::operator [] (int index)
{
	return mHistory[index];
}

template<class _TYPE, int _SIZE>
int MovingQueue<_TYPE, _SIZE>::size()
{
	return mHistory.size();
}

//==============================================================================
//	CLASS MovingAverage
//==============================================================================
template<class _TYPE, int _SIZE>
MovingAverage<_TYPE, _SIZE>::MovingAverage()
:
	mMovingQueue()
{}
	
template<class _TYPE, int _SIZE>
void MovingAverage<_TYPE, _SIZE>::record(const _TYPE &value)
{
	mMovingQueue.record(value);
}

template<class _TYPE, int _SIZE>
_TYPE MovingAverage<_TYPE, _SIZE>::average()
{
	_TYPE accum = _TYPE(0);

	if (mMovingQueue.size() == 0)
		return accum;

	for (int i = 0; i < mMovingQueue.size(); ++i)
		accum += mMovingQueue[i];

	return accum / mMovingQueue.size();
}

#ifdef GENERIC_NAMESPACE
}
#endif

#endif // __GENERIC_MATH_MOVINGAVERAGE_INLINE__

