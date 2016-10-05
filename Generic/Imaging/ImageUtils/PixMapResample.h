/*******************************************************************************
 Copyright 2007 Enseed inc.
 
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
#ifndef __GENERIC_IMAGING_IMAGEUTILS_RESAMPLE__
#define __GENERIC_IMAGING_IMAGEUTILS_RESAMPLE__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "../../Math/Rational.h"
#include "../PixMap.declare.deprecated.h"
#include "../../Devel/Debug.h"

namespace seed {

//==============================================================================
//	CLASS PixMapResample
//==============================================================================
class PixMapResample
{
private:
	PixMapResample();

public:
	template<class LHS, class RHS>
	static PixMap<LHS>& nearestNeighbor_hasChanged(const PixMap<RHS> &src, PixMap<LHS> &dst)
	{
		CHECKF(static_cast<void*>(&dst) != static_cast<const void*>(&src), "nearestNeighbor resampling cannot work in-place");

		typename PixMap<LHS>::Row row = dst.begin();
		typename PixMap<RHS>::ConstRow srcRow = src.begin();
		for (int y = 0; row != dst.end(); ++row, ++y)
		{
			int ry = (y * src.height() + src.height()/2) / dst.height();
			typename PixMap<LHS>::Row::Pixel p = row.begin();
			typename PixMap<RHS>::ConstRow::ConstPixel srcP = (srcRow + ry).begin();
			for (int x = 0; p != row.end(); ++p, ++x)
			{
				int rx = (x * src.width() + src.width()/2) / dst.width();
				p.copy(srcP + rx);
			}
		}

		dst.setPixelRatio(Rational(src.width()*dst.height(), dst.width()*src.height()));
		return dst;
	}
};

} // namespace seed

#endif // __GENERIC_IMAGING_IMAGEUTILS_RESAMPLE__
