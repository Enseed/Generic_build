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
#ifndef __GENERIC_IMAGING_IMAGEUTILS_CONVOLUTION_INLINE__
#define __GENERIC_IMAGING_IMAGEUTILS_CONVOLUTION_INLINE__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "../PixMapConvolution.h"
#include "../../PixMap.deprecated.h"
#include "../../Pixel.deprecated.h"

namespace seed {

//==============================================================================
//	CLASS PixMapConvolution
//==============================================================================

//------------------------------------------------------------------------------
//
template<typename _KType, typename _PType, typename _Scaler, typename _Clamper>
PixMapConvolution<_KType, _PType, _Scaler, _Clamper>::PixMapConvolution(const PixMap<_KType> &kernel)
:	
	mKernel(kernel),
	mScaler(),
	mClamper()
{}

//------------------------------------------------------------------------------
//
template<typename _KType, typename _PType, typename _Scaler, typename _Clamper>
PixMapConvolution<_KType, _PType, _Scaler, _Clamper>::PixMapConvolution(const PixMap<_KType> &kernel, const _Scaler &scaler)
:	
	mKernel(kernel),
	mScaler(scaler),
	mClamper()
{}

//------------------------------------------------------------------------------
//
template<typename _KType, typename _PType, typename _Scaler, typename _Clamper>
PixMapConvolution<_KType, _PType, _Scaler, _Clamper>::PixMapConvolution(const PixMap<_KType> &kernel, const _Clamper &clamper)
:	
	mKernel(kernel),
	mScaler(),
	mClamper(clamper)
{}
	
//------------------------------------------------------------------------------
//
template<typename _KType, typename _PType, typename _Scaler, typename _Clamper>
PixMapConvolution<_KType, _PType, _Scaler, _Clamper>::PixMapConvolution(const PixMap<_KType> &kernel, const _Scaler &scaler, const _Clamper &clamper)
:	
	mKernel(kernel),
	mScaler(scaler),
	mClamper(clamper)
{}
	
//------------------------------------------------------------------------------
//
template<typename _KType, typename _PType, typename _Scaler, typename _Clamper> template<typename _IType, typename _OType, typename _OOBStrategy>
void PixMapConvolution<_KType, _PType, _Scaler, _Clamper>::convolveImage(const PixMap<_IType> &imageIn, PixMap<_OType> *imageOut, const _OOBStrategy &oobStrategy, int xInc, int yInc)
{
	ASSERT(_IType::COMPONENT_COUNT == _OType::COMPONENT_COUNT);
	ASSERT(imageIn.width() == imageOut->width());
	ASSERT(imageIn.height() == imageOut->height());

	if (imageIn.width() < mKernel.width())		return;
	if (imageIn.height() < mKernel.height())	return;

	ASSERT(imageIn.width() >= mKernel.width());
	ASSERT(imageIn.height() >= mKernel.height());
	
	//	kernel center is as (width+1)/2
	//	For example:
	//
	//  A B C      A B C D
	//	D * F      E F G H
	//	G H I      I H * L
	//             M N O P
	
	//	We will read mKernel backward...
	
	const int32 kernelWidth = mKernel.width();
	const int32 kernelLeft = (kernelWidth-1)/2;
	const int32 kernelRight = kernelWidth - kernelLeft;

	const int32 kernelHeight = mKernel.height();
	const int32 kernelTop = (kernelHeight-1)/2;
	const int32 kernelBottom = kernelHeight - kernelTop;

	const int32 imageWidth = imageIn.width();
	const int32 imageHeight = imageIn.height();

	int y;
	for (y = 0; y < kernelTop; y+=yInc)
	{
		int x;
		for (x = 0; x < kernelLeft; x+=xInc)
		{
			_PType accum[_OType::COMPONENT_COUNT] = {0};
			int j;
			for (j = 0; j-kernelTop+y < 0; ++j)
			{
				int jImage = j - kernelTop;
				int i;
				for (i = 0; i+x-kernelLeft < 0; ++i)
				{
					int iImage = i - kernelLeft;
					for (int s = 0; s < _OType::COMPONENT_COUNT; ++s)
					{
						const typename _IType::Component *p = oobStrategy.tl(imageIn, x+iImage, y+jImage);
						const typename _KType::Component *k = mKernel[j][i];
						accum[s] += static_cast<_PType>(p[s] * k[0]);
					}
				}

				for (; i < kernelWidth; ++i)
				{
					int iImage = i - kernelLeft;
					for (int s = 0; s < _OType::COMPONENT_COUNT; ++s)
					{
						const typename _IType::Component *p = oobStrategy.t(imageIn, x+iImage, y+jImage);
						const typename _KType::Component *k = ((mKernel.begin() + j).begin() + i);
						accum[s] += static_cast<_PType>(p[s] * k[0]);
					}
				}
			}
			for (; j < kernelHeight; ++j)
			{
				int jImage = j - kernelTop;
				int i;
				for (i = 0; i+x-kernelLeft < 0; ++i)
				{
					int iImage = i - kernelLeft;
					for (int s = 0; s < _OType::COMPONENT_COUNT; ++s)
					{
						const typename _IType::Component *p = oobStrategy.l(imageIn, x+iImage, y+jImage);
						const typename _KType::Component *k = ((mKernel.begin() + j).begin() + i);
						accum[s] += static_cast<_PType>(p[s] * k[0]);
					}
				}

				for (; i < kernelWidth; ++i)
				{
					int iImage = i - kernelLeft;
					for (int s = 0; s < _OType::COMPONENT_COUNT; ++s)
					{
						const typename _IType::Component *p = imageIn[y+jImage][x+iImage];
						const typename _KType::Component *k = ((mKernel.begin() + j).begin() + i);
						accum[s] += static_cast<_PType>(p[s] * k[0]);
					}
				}
			}

			for (int s = 0; s < _OType::COMPONENT_COUNT; ++s)
			{
				_PType scaled;
				mScaler(accum[s], &scaled);
				typename _OType::Component *destPixel = (*imageOut)[y][x];
				mClamper(scaled, destPixel+s);
			}
		}

		for (; x < imageWidth - kernelRight; x+=xInc)
		{
			_PType accum[_OType::COMPONENT_COUNT] = {0};
			int j;
			for (j = 0; j-kernelTop+y < 0; ++j)
			{
				int jImage = j - kernelTop;
				for (int i = 0; i < kernelWidth; ++i)
				{
					int iImage = i - kernelLeft;
					for (int s = 0; s < _OType::COMPONENT_COUNT; ++s)
					{
						const typename _IType::ConstPixel pel = oobStrategy.t(imageIn, x+iImage, y+jImage);
						const typename _KType::Component *k = ((mKernel.begin() + j).begin() + i);
						const typename _IType::Component *p = pel;
						accum[s] += static_cast<_PType>(p[s] * k[0]);
					}
				}
			}

			for (; j < kernelHeight; ++j)
			{
				int jImage = j - kernelTop;
				for (int i = 0; i < kernelWidth; ++i)
				{
					int iImage = i - kernelLeft;
					for (int s = 0; s < _OType::COMPONENT_COUNT; ++s)
					{
						const typename _IType::ConstPixel pel = imageIn[y+jImage][x+iImage];
						const typename _KType::Component *k = ((mKernel.begin() + j).begin() + i);
						const typename _IType::Component *p = pel;
						accum[s] += static_cast<_PType>(p[s] * k[0]);
					}
				}
			}
			for (int s = 0; s < _OType::COMPONENT_COUNT; ++s)
			{
				_PType scaled;
				mScaler(accum[s], &scaled);
				typename _OType::Component *destPixel = (*imageOut)[y][x];
				mClamper(scaled, destPixel+s);
			}
		}


		for (; x < imageWidth; x+=xInc)
		{
			_PType accum[_OType::COMPONENT_COUNT] = {0};
			int j;
			for (j = 0; j-kernelTop+y < 0; ++j)
			{
				int jImage = j - kernelTop;
				int i;
				for (i = 0; i-kernelLeft+x < imageWidth; ++i)
				{
					int iImage = i - kernelLeft;
					for (int s = 0; s < _OType::COMPONENT_COUNT; ++s)
					{
						const typename _IType::Component *p = oobStrategy.t(imageIn, x+iImage, y+jImage);
						const typename _KType::Component *k = ((mKernel.begin() + j).begin() + i);
						accum[s] += static_cast<_PType>(p[s] * k[0]);
					}
				}

				for (; i < kernelWidth; ++i)
				{
					int iImage = i - kernelLeft;
					for (int s = 0; s < _OType::COMPONENT_COUNT; ++s)
					{
						const typename _IType::Component *p = oobStrategy.tr(imageIn, x+iImage, y+jImage);
						const typename _KType::Component *k = ((mKernel.begin() + j).begin() + i);
						accum[s] += static_cast<_PType>(p[s] * k[0]);
					}
				}
			}

			for (; j < kernelHeight; ++j)
			{
				int jImage = j - kernelTop;
				int i;
				for (i = 0; i-kernelLeft+x < imageWidth; ++i)
				{
					int iImage = i - kernelLeft;
					for (int s = 0; s < _OType::COMPONENT_COUNT; ++s)
					{
						const typename _IType::Component *p = imageIn[y+jImage][x+iImage];
						const typename _KType::Component *k = ((mKernel.begin() + j).begin() + i);
						accum[s] += static_cast<_PType>(p[s] * k[0]);
					}
				}

				for (; i < kernelWidth; ++i)
				{
					int iImage = i - kernelLeft;
					for (int s = 0; s < _OType::COMPONENT_COUNT; ++s)
					{
						const typename _IType::Component *p = oobStrategy.r(imageIn, x+iImage, y+jImage);
						const typename _KType::Component *k = ((mKernel.begin() + j).begin() + i);
						accum[s] += static_cast<_PType>(p[s] * k[0]);
					}
				}
			}

			for (int s = 0; s < _OType::COMPONENT_COUNT; ++s)
			{
				_PType scaled;
				mScaler(accum[s], &scaled);
				typename _OType::Component *destPixel = (*imageOut)[y][x];
				mClamper(scaled, destPixel+s);
			}
		}
	}

	for (y = kernelTop; y < imageHeight - kernelBottom; y+=yInc)
	{
		int x;
		for (x = 0; x < kernelLeft; x+=xInc)
		{
			_PType accum[_OType::COMPONENT_COUNT] = {0};
			for (int j = 0; j < kernelHeight; ++j)
			{
				int jImage = j - kernelTop;
				int i;
				for (i = 0; i+x-kernelLeft < 0; ++i)
				{
					int iImage = i - kernelLeft;
					for (int s = 0; s < _OType::COMPONENT_COUNT; ++s)
					{
						const typename _IType::Component *p = oobStrategy.l(imageIn, x+iImage, y+jImage);
						const typename _KType::Component *k = ((mKernel.begin() + j).begin() + i);
						accum[s] += static_cast<_PType>(p[s] * k[0]);
					}
				}

				for (; i < kernelWidth; ++i)
				{
					int iImage = i - kernelLeft;
					for (int s = 0; s < _OType::COMPONENT_COUNT; ++s)
					{
						const typename _IType::Component *p = imageIn[y+jImage][x+iImage];
						const typename _KType::Component *k = ((mKernel.begin() + j).begin() + i);
						accum[s] += static_cast<_PType>(p[s] * k[0]);
					}
				}
			}

			for (int s = 0; s < _OType::COMPONENT_COUNT; ++s)
			{
				_PType scaled;
				mScaler(accum[s], &scaled);
				typename _OType::Component *destPixel = (*imageOut)[y][x];
				mClamper(scaled, destPixel+s);
			}
		}

		// MAIN LOOP
		for (; x < imageWidth - kernelRight; x+=xInc)
		{
			_PType accum[_OType::COMPONENT_COUNT] = {0};
			for (int j = 0; j < kernelHeight; ++j)
			{
				int jImage = j - kernelTop;
				for (int i = 0; i < kernelWidth; ++i)
				{
					int iImage = i - kernelLeft;
					for (int s = 0; s < _OType::COMPONENT_COUNT; ++s)
					{
						const typename _IType::Component *p = imageIn[y+jImage][x+iImage];
						const typename _KType::Component *k = ((mKernel.begin() + j).begin() + i);
						accum[s] += static_cast<_PType>(p[s] * k[0]);
					}
				}
				

			}

			for (int s = 0; s < _OType::COMPONENT_COUNT; ++s)
			{
				_PType scaled;
				mScaler(accum[s], &scaled);
				typename _OType::Component *destPixel = (*imageOut)[y][x];
				mClamper(scaled, destPixel+s);
			}
		}

		for (; x < imageWidth; x+=xInc)
		{
			_PType accum[_OType::COMPONENT_COUNT] = {0};
			for (int j = 0; j < kernelHeight; ++j)
			{
				int jImage = j - kernelTop;
				int i;
				for (i = 0; i-kernelLeft+x < imageWidth; ++i)
				{
					int iImage = i - kernelLeft;
					for (int s = 0; s < _OType::COMPONENT_COUNT; ++s)
					{
						const typename _IType::Component *p = imageIn[y+jImage][x+iImage];
						const typename _KType::Component *k = ((mKernel.begin() + j).begin() + i);
						accum[s] += static_cast<_PType>(p[s] * k[0]);
					}
				}

				for (; i < kernelWidth; ++i)
				{
					int iImage = i - kernelLeft;
					for (int s = 0; s < _OType::COMPONENT_COUNT; ++s)
					{
						const typename _IType::Component *p = oobStrategy.r(imageIn, x+iImage, y+jImage);
						const typename _KType::Component *k = ((mKernel.begin() + j).begin() + i);
						accum[s] += static_cast<_PType>(p[s] * k[0]);
					}
				}
				

			}

			for (int s = 0; s < _OType::COMPONENT_COUNT; ++s)
			{
				_PType scaled;
				mScaler(accum[s], &scaled);
				typename _OType::Component *destPixel = (*imageOut)[y][x];
				mClamper(scaled, destPixel+s);
			}
		}
	}

	for (y = imageHeight - kernelBottom; y < imageHeight; y+=yInc)
	{
		int x;
		for (x = 0; x < kernelLeft; x+=xInc)
		{
			_PType accum[_OType::COMPONENT_COUNT] = {0};
			int j;
			for (j = 0; j-kernelTop+y < imageHeight; ++j)
			{
				int jImage = j - kernelTop;
				int i;
				for (i = 0; i+x-kernelLeft < 0; ++i)
				{
					int iImage = i - kernelLeft;
					for (int s = 0; s < _OType::COMPONENT_COUNT; ++s)
					{
						const typename _IType::Component *p = oobStrategy.l(imageIn, x+iImage, y+jImage);
						const typename _KType::Component *k = ((mKernel.begin() + j).begin() + i);
						accum[s] += static_cast<_PType>(p[s] * k[0]);
					}
				}

				for (; i < kernelWidth; ++i)
				{
					int iImage = i - kernelLeft;
					for (int s = 0; s < _OType::COMPONENT_COUNT; ++s)
					{
						const typename _IType::Component *p = imageIn[y+jImage][x+iImage];
						const typename _KType::Component *k = ((mKernel.begin() + j).begin() + i);
						accum[s] += static_cast<_PType>(p[s] * k[0]);
					}
				}
			}
			for (; j < kernelHeight; ++j)
			{
				int jImage = j - kernelTop;
				int i;
				for (i = 0; i+x-kernelLeft < 0; ++i)
				{
					int iImage = i - kernelLeft;
					for (int s = 0; s < _OType::COMPONENT_COUNT; ++s)
					{
						const typename _IType::Component *p = oobStrategy.bl(imageIn, x+iImage, y+jImage);
						const typename _KType::Component *k = ((mKernel.begin() + j).begin() + i);
						accum[s] += static_cast<_PType>(p[s] * k[0]);
					}
				}

				for (; i < kernelWidth; ++i)
				{
					int iImage = i - kernelLeft;
					for (int s = 0; s < _OType::COMPONENT_COUNT; ++s)
					{
						const typename _IType::Component *p = oobStrategy.b(imageIn, x+iImage, y+jImage);
						const typename _KType::Component *k = ((mKernel.begin() + j).begin() + i);
						accum[s] += static_cast<_PType>(p[s] * k[0]);
					}
				}
			}

			for (int s = 0; s < _OType::COMPONENT_COUNT; ++s)
			{
				_PType scaled;
				mScaler(accum[s], &scaled);
				typename _OType::Component *destPixel = (*imageOut)[y][x];
				mClamper(scaled, destPixel+s);
			}
		}

		for (; x < imageWidth - kernelRight; x+=xInc)
		{
			_PType accum[_OType::COMPONENT_COUNT] = {0};
			int j;
			for (j = 0; j-kernelTop+y < imageHeight; ++j)
			{
				int jImage = j - kernelTop;
				for (int i = 0; i < kernelWidth; ++i)
				{
					int iImage = i - kernelLeft;
					for (int s = 0; s < _OType::COMPONENT_COUNT; ++s)
					{
						const typename _IType::ConstPixel pel = imageIn[y+jImage][x+iImage];
						const typename _KType::Component *k = ((mKernel.begin() + j).begin() + i);
						const typename _IType::Component *p = pel;
						accum[s] += static_cast<_PType>(p[s] * k[0]);
					}
				}
			}

			for (; j < kernelHeight; ++j)
			{
				int jImage = j - kernelTop;
				for (int i = 0; i < kernelWidth; ++i)
				{
					int iImage = i - kernelLeft;
					for (int s = 0; s < _OType::COMPONENT_COUNT; ++s)
					{
						const typename _IType::ConstPixel pel = oobStrategy.b(imageIn, x+iImage, y+jImage);
						const typename _KType::Component *k = ((mKernel.begin() + j).begin() + i);
						const typename _IType::Component *p = pel;
						accum[s] += static_cast<_PType>(p[s] * k[0]);
					}
				}
			}
			for (int s = 0; s < _OType::COMPONENT_COUNT; ++s)
			{
				_PType scaled;
				mScaler(accum[s], &scaled);
				typename _OType::Component *destPixel = (*imageOut)[y][x];
				mClamper(scaled, destPixel+s);
			}
		}


		for (; x < imageWidth; x+=xInc)
		{
			_PType accum[_OType::COMPONENT_COUNT] = {0};
			int j;
			for (j = 0; j-kernelTop+y < imageHeight; ++j)
			{
				int jImage = j - kernelTop;
				int i;
				for (i = 0; i-kernelLeft+x < imageWidth; ++i)
				{
					int iImage = i - kernelLeft;
					for (int s = 0; s < _OType::COMPONENT_COUNT; ++s)
					{
						const typename _IType::Component *p = imageIn[y+jImage][x+iImage];
						const typename _KType::Component *k = ((mKernel.begin() + j).begin() + i);
						accum[s] += static_cast<_PType>(p[s] * k[0]);
					}
				}

				for (; i < kernelWidth; ++i)
				{
					int iImage = i - kernelLeft;
					for (int s = 0; s < _OType::COMPONENT_COUNT; ++s)
					{
						const typename _IType::Component *p = oobStrategy.r(imageIn, x+iImage, y+jImage);
						const typename _KType::Component *k = ((mKernel.begin() + j).begin() + i);
						accum[s] += static_cast<_PType>(p[s] * k[0]);
					}
				}
			}

			for (; j < kernelHeight; ++j)
			{
				int jImage = j - kernelTop;
				int i;
				for (i = 0; i-kernelLeft+x < imageWidth; ++i)
				{
					int iImage = i - kernelLeft;
					for (int s = 0; s < _OType::COMPONENT_COUNT; ++s)
					{
						const typename _IType::Component *p = oobStrategy.b(imageIn, x+iImage, y+jImage);
						const typename _KType::Component *k = ((mKernel.begin() + j).begin() + i);
						accum[s] += static_cast<_PType>(p[s] * k[0]);
					}
				}

				for (; i < kernelWidth; ++i)
				{
					int iImage = i - kernelLeft;
					for (int s = 0; s < _OType::COMPONENT_COUNT; ++s)
					{
						const typename _IType::Component *p = oobStrategy.br(imageIn, x+iImage, y+jImage);
						const typename _KType::Component *k = ((mKernel.begin() + j).begin() + i);
						accum[s] += static_cast<_PType>(p[s] * k[0]);
					}
				}
			}

			for (int s = 0; s < _OType::COMPONENT_COUNT; ++s)
			{
				_PType scaled;
				mScaler(accum[s], &scaled);
				typename _OType::Component *destPixel = (*imageOut)[y][x];
				mClamper(scaled, destPixel+s);
			}
		}
	}
}

//------------------------------------------------------------------------------
//
template<typename _KType, typename _PType, typename _Scaler, typename _Clamper> template<typename _IType, typename _OOBStrategy>
void PixMapConvolution<_KType, _PType, _Scaler, _Clamper>::convolveImageInPlace(PixMap<_IType> *image, const _OOBStrategy &strategy, int xInc, int yInc)
{
	PixMap<_IType> temp;
	temp.copy(*image);
	convolveImage(temp, image, strategy, xInc, yInc);
}
	
} // namespace seed


#endif // __GENERIC_IMAGING_IMAGEUTILS_CONVOLUTION_INLINE__
