/*******************************************************************************
 Copyright 2010 Enseed inc.
 
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
#ifndef __GENERIC_IMAGING_RESOLUTION__
#define __GENERIC_IMAGING_RESOLUTION__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include <Generic/Geometry/Size.h>

//==============================================================================
//	FORWARD DECLARATIONS
//==============================================================================
#ifdef GENERIC_NAMESPACE
namespace GENERIC_NAMESPACE {
#endif

//==============================================================================
//	INTERFACE Resolution
//==============================================================================
class Resolution
{
public:
	Resolution(const Size2i &aSize, int aDepth)
	:
		size(aSize),
		depth(aDepth)
	{}

	Resolution()
	:
		size(),
		depth()
	{}

	Resolution(const Size2i &aSize)
	:
		size(aSize),
		depth(32)
	{}

	Resolution(int aWidth, int aHeight)
	:
		size(aWidth, aHeight),
		depth(32)
	{}

	Resolution(int aWidth, int aHeight, int aDepth)
	:
		size(aWidth, aHeight),
		depth(aDepth)
	{}

	void setSize(int aWidth, int aHeight) { size = Size2i(aWidth, aHeight); }

private:
	Size2i size;
	int depth;
};

#ifdef GENERIC_NAMESPACE
}
#endif

#endif // __GENERIC_IMAGING_RESOLUTION__
