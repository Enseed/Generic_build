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
#ifndef __GENERIC_IMAGING_IMAGEUTILS_CONVOLUTION__
#define __GENERIC_IMAGING_IMAGEUTILS_CONVOLUTION__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "../PixMap.declare.deprecated.h"
#include <limits>

#ifdef min // Windows.h...
#undef min
#endif

#ifdef max
#undef max
#endif

namespace seed {

//==============================================================================
//	CLASS PixMapConvolutionClampMinMax
//==============================================================================
class PixMapConvolutionClampMinMax
{
public:
	template<typename _IType, typename _OType>
	void operator()(const _IType &inValue, _OType *outValue)
	{
		if (inValue > std::numeric_limits<_OType>::max())
			*outValue = std::numeric_limits<_OType>::max();
		else if (inValue < std::numeric_limits<_OType>::min())
			*outValue = std::numeric_limits<_OType>::min();
		else
			*outValue = static_cast<_OType>(inValue);
	}
};

//==============================================================================
//	CLASS PixMapConvolutionNoClamp
//==============================================================================
class PixMapConvolutionNoClamp
{
public:
	template<typename _IType, typename _OType>
	void operator()(const _IType &inValue, _OType *outValue)
	{
		*outValue = static_cast<_OType>(inValue);
	}
};

//==============================================================================
//	CLASS PixMapConvolutionNoScale
//==============================================================================
class PixMapConvolutionNoScale
{
public:
	template<typename _IType, typename _OType>
	void operator()(const _IType &inValue, _OType *outValue)
	{
		*outValue = static_cast<_OType>(inValue);
	}
};


//==============================================================================
//	CLASS PixMapConvolutionScaleShiftRight
//==============================================================================
template<int _RShift>
class PixMapConvolutionScaleShiftRight
{
public:
	template<typename _IType, typename _OType>
	void operator()(const _IType &inValue, _OType *outValue)
	{
		*outValue = static_cast<_OType>(inValue >> _RShift);
	}
};

//==============================================================================
//	CLASS PixMapConvolutionScaleShiftRight2
//==============================================================================
class PixMapConvolutionScaleShiftRight2
{
public:
	PixMapConvolutionScaleShiftRight2(int rightShift)
	:
		mRightShift(rightShift)
	{}
	
public:
	template<typename _IType, typename _OType>
	void operator()(const _IType &inValue, _OType *outValue)
	{
		*outValue = static_cast<_OType>(inValue >> mRightShift);
	}

private:
	int mRightShift;
};

//==============================================================================
//	CLASS PixMapConvolutionScaleMultiply
//==============================================================================
template<typename _MType=double>
class PixMapConvolutionScaleMultiply
{
public:
	PixMapConvolutionScaleMultiply(_MType factor)
	:
		mFactor(factor)
	{}
	
public:
	template<typename _IType, typename _OType>
	void operator()(const _IType &inValue, _OType *outValue)
	{
		*outValue = static_cast<_OType>(inValue * mFactor);
	}

private:
	_MType mFactor;
};

//==============================================================================
//	CLASS PixMapConvolutionOutOfBoundRepeat
//==============================================================================
class PixMapConvolutionOutOfBoundRepeat
{
public:
	template<typename _IType>
	typename _IType::ConstPixel clamp(const PixMap<_IType> &image, int x, int y) const
	{
		if (x < 0)	x = 0;
		else if (x >= image.width()) x = image.width()-1;

		if (y < 0)	y = 0;
		else if (y >= image.height()) y = image.height()-1;
		
		return (image.begin() + y).begin() + x;
	}


	//	tl() is called for a pixel that is on top left of the image
	template<typename _IType>
	typename _IType::ConstPixel tl(const PixMap<_IType> &image, int x, int y) const
	{
		return clamp(image, x, y);
	}

	//	t() is called for a pixel that is on top of the image
	template<typename _IType>
	typename _IType::ConstPixel t(const PixMap<_IType> &image, int x, int y) const
	{
		return clamp(image, x, y);
	}

	//	tr() is called for a pixel that is on top right of the image
	template<typename _IType>
	typename _IType::ConstPixel tr(const PixMap<_IType> &image, int x, int y) const
	{
		return clamp(image, x, y);
	}

	//	l() is called for a pixel that is on the left of the image
	template<typename _IType>
	typename _IType::ConstPixel l(const PixMap<_IType> &image, int x, int y) const
	{
		return clamp(image, x, y);
	}

	//	r() is called for a pixel that is on the right of the image
	template<typename _IType>
	typename _IType::ConstPixel r(const PixMap<_IType> &image, int x, int y) const
	{
		return clamp(image, x, y);
	}

	//	bl() is called for a pixel that is at the bottom left of the image
	template<typename _IType>
	typename _IType::ConstPixel bl(const PixMap<_IType> &image, int x, int y) const
	{
		return clamp(image, x, y);
	}

	//	b() is called for a pixel that is at the bottom of the image
	template<typename _IType>
	typename _IType::ConstPixel b(const PixMap<_IType> &image, int x, int y) const
	{
		return clamp(image, x, y);
	}

	//	br() is called for a pixel that is at the bottom right of the image
	template<typename _IType>
	typename _IType::ConstPixel br(const PixMap<_IType> &image, int x, int y) const
	{
		return clamp(image, x, y);
	}
};

//==============================================================================
//	CLASS PixMapConvolution
//==============================================================================
template<typename _KType, typename _PType, typename _Scaler=PixMapConvolutionNoScale, typename _Clamper=PixMapConvolutionClampMinMax>
class PixMapConvolution
{
public:
	PixMapConvolution(const PixMap<_KType> &kernel);
	PixMapConvolution(const PixMap<_KType> &kernel, const _Scaler &scaler);
	PixMapConvolution(const PixMap<_KType> &kernel, const _Clamper &clamper);
	PixMapConvolution(const PixMap<_KType> &kernel, const _Scaler &scaler, const _Clamper &clamper);

public:
	template<typename _IType, typename _OType, typename _OOBStrategy>
	void convolveImage(const PixMap<_IType> &imageIn, PixMap<_OType> *imageOut, const _OOBStrategy &strategy, int xInc, int yInc);

	template<typename _IType, typename _OOBStrategy>
	void convolveImageInPlace(PixMap<_IType> *image, const _OOBStrategy &strategy, int xInc, int yInc);
	
private:
	const PixMap<_KType> &mKernel;
	_Scaler mScaler;
	_Clamper mClamper;
};

} // namespace seed

#include "src/PixMapConvolution.inline.h"

#endif // __GENERIC_IMAGING_IMAGEUTILS_CONVOLUTION__
