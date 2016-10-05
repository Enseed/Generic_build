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
#ifndef __GENERIC_MATH_MOVINGAVERAGE__
#define __GENERIC_MATH_MOVINGAVERAGE__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include <vector>

#ifdef GENERIC_NAMESPACE
namespace GENERIC_NAMESPACE {
#endif

//==============================================================================
//	CLASS MovingQueue
//==============================================================================
template<class _TYPE, int _SIZE>
class MovingQueue
{
public:
	MovingQueue();
	void record(const _TYPE &value);
	_TYPE& operator [] (int index);
	int size();

private:
	std::vector<_TYPE> mHistory;
	int mSampleCount;
};


//==============================================================================
//	CLASS MovingAverage
//==============================================================================
template<class _TYPE, int _SIZE>
class MovingAverage
{
public:
	MovingAverage();

	void record(const _TYPE &value);
	_TYPE average();

private:
	MovingQueue<_TYPE, _SIZE> mMovingQueue;
};

#ifdef GENERIC_NAMESPACE
}
#endif

//==============================================================================
//	INLINED CODE
//==============================================================================
#include "src/MovingAverage.inline.h"


#endif // __GENERIC_MATH_MOVINGAVERAGE__

