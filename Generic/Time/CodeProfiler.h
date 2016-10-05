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
#ifndef __GENERIC_TIME_CODEPROFILER__
#define __GENERIC_TIME_CODEPROFILER__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "Time.h"
#include "../Math/Gaussian.h"
#include "IntervalTimer.h"
#include <map>

#ifdef GENERIC_NAMESPACE
namespace GENERIC_NAMESPACE {
#endif

//==============================================================================
//	CLASS CodeProfiler
//==============================================================================
template<class _TIMER>
class CodeProfiler
{
private:
	class Registry
	{
	public:
		typedef std::map< std::string, Gaussian1d > Map;
		static Map& instance();
	private:
		Registry();
		Registry(const Registry&);
		Registry& operator = (const Registry&);
	};
	
private:
	CodeProfiler(const CodeProfiler&);
	CodeProfiler& operator =  (const CodeProfiler&);
	
public:
	CodeProfiler(const char *name);
	~CodeProfiler();
	
	static void printReport();
	
private:
	IntervalTimer<_TIMER>	mTimer;
	const char *mName;
};

#define PROFILE_THIS_FUNCTION CodeProfiler<Timer> _function_profile(__FUNCTION__)

#ifdef GENERIC_NAMESPACE
}
#endif

#include "src/CodeProfiler.inline.h"

#endif // __GENERIC_TIME_CODEPROFILER__
