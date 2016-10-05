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
#ifndef __GENERIC_TIME_CODEPROFILER_INLINE__
#define __GENERIC_TIME_CODEPROFILER_INLINE__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "../CodeProfiler.h"

#ifdef GENERIC_NAMESPACE
namespace GENERIC_NAMESPACE {
#endif

//==============================================================================
//	CLASS CodeProfiler
//==============================================================================
template<class _TIMER>
std::map< std::string, Gaussian1d >& CodeProfiler<_TIMER>::Registry::instance()
{
	static Map mRegistry;
	return mRegistry;
}
	
template<class _TIMER>
CodeProfiler<_TIMER>::CodeProfiler(const char *name)
:
	mTimer(),
	mName(name)
{ 
	mTimer.start();
}
	
template<class _TIMER>
CodeProfiler<_TIMER>::~CodeProfiler()
{
	Registry::instance()[mName].addSample(Point1d(mTimer.stop().inSeconds()));
}

template<class _TIMER>
void CodeProfiler<_TIMER>::printReport()
{
	std::map< std::string, Gaussian1d > &map = Registry::instance();
	std::map< std::string, Gaussian1d >::iterator iter;
	
	for (iter = map.begin(); iter != map.end(); ++iter)
	{
		Gaussian1d::Distribution d(iter->second);
		printf("[%s]: %.3fus (stddev: %.3fus) [%d samples]\n",
			iter->first.c_str(),
			d.mean().x*1000000,
			sqrt(d.covariance()[0][0])*1000000,
			(int)round(iter->second.weight())
		);
	}
}
	
#ifdef GENERIC_NAMESPACE
}
#endif

#endif // __GENERIC_TIME_CODEPROFILER_INLINE__

