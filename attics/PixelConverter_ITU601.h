#if 0
/*******************************************************************************
 Copyright 2009 Enseed Inc. & Gaspard Petit <gaspardpetit@enseed.com>
 
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
*******************************************************************************/
#ifndef __ITL_PIXELCONVERTER_ITU601_H__
#define __ITL_PIXELCONVERTER_ITU601_H__

//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================
#include "PixelConverter.h"

//==============================================================================
// CLASS PixelColorSpaceConverter:
//		ColorSpace_YCbCr_ITU601::* => ColorSpace_YCbCr_ITU601::*
//==============================================================================
// Generic YCbCr_ITU601 to YCbCr_ITU601.  Use a YCbCrf32Pixel as an intermediary.
template<typename SRC_PIXEL, typename DST_PIXEL>
class PixelColorSpaceConverter<SRC_PIXEL, DST_PIXEL, ColorSpace_YCbCr_ITU601, ColorSpace_YCbCr_ITU601> 
{
public:
	static void convert(const SRC_PIXEL &src, DST_PIXEL *dst)
	{
		YCbCrf32Pixel temp;
		PixelConvert(src, &temp);
		PixelConvert(temp, dst);
	}
};

//==============================================================================
// CLASS PixelColorSpaceConverter2
//		ColorSpace_YCbCr_ITU601::*[444] => ColorSpace_YCbCr_ITU601::*[422]
//==============================================================================
template<typename SRC_PIXEL0, typename SRC_PIXEL1, typename DST_PIXEL>
class PixelColorSpaceConverter2<SRC_PIXEL0, SRC_PIXEL1, DST_PIXEL, ColorSpace_YCbCr_ITU601, ColorSpace_YCbCr_ITU601> 
{
public:
	static void convert(const SRC_PIXEL0 &src0, const SRC_PIXEL1 &src1, DST_PIXEL *dst)
	{
		YCbCrf32Pixel floatYCbCr0;
		YCbCrf32Pixel floatYCbCr1;
		PixelConvert(src0, &floatYCbCr0);
		PixelConvert(src1, &floatYCbCr1);
		PixelConvert(floatYCbCr0, floatYCbCr1, dst);
	}
};


//==============================================================================
// CLASS PixelColorSpaceConverter2
//		ColorSpace_YCbCr_ITU601::*[444] => ColorSpace_YCbCr_ITU601::*[422]
//==============================================================================
// Generic YCbCr_ITU601 to YCbCr_ITU601.  Use a YCbCrf32Pixel as an intermediary.
template<typename DST_PIXEL>
class PixelColorSpaceConverter2<YCbCrf32Pixel, YCbCrf32Pixel, DST_PIXEL, ColorSpace_YCbCr_ITU601, ColorSpace_YCbCr_ITU601> 
{
public:
	static void convert(const YCbCrf32Pixel &src0, const YCbCrf32Pixel &src1, DST_PIXEL *dst)
	{
				// FIXME:
				// We probably want to interpolate the chroma values here...

		dst->setYCbYCr(
			DST_PIXEL::Y0ComponentType(src0.luminance()*(DST_PIXEL::maxLuminance0()-DST_PIXEL::minLuminance0())+DST_PIXEL::minLuminance0()),
			DST_PIXEL::CbComponentType(src0.chromaBlue()*(DST_PIXEL::maxChromaBlue()-DST_PIXEL::minChromaBlue())+DST_PIXEL::minChromaBlue()),
			DST_PIXEL::Y1ComponentType(src1.luminance()*(DST_PIXEL::maxLuminance1()-DST_PIXEL::minLuminance1())+DST_PIXEL::minLuminance1()),
			DST_PIXEL::CrComponentType(src1.chromaRed()*(DST_PIXEL::maxChromaRed()-DST_PIXEL::minChromaRed())+DST_PIXEL::minChromaRed())
		);
	}
};

//==============================================================================
// CLASS PixelColorSpaceConverter:
//		ColorSpace_YCbCr_ITU601::* => ColorSpace_YCbCr_ITU601::YCbCrf32Pixel
//==============================================================================
// From any YCbCr_601 to YCbCrf32Pixel
template<typename SRC_PIXEL>
class PixelColorSpaceConverter<SRC_PIXEL, YCbCrf32Pixel, ColorSpace_YCbCr_ITU601, ColorSpace_YCbCr_ITU601> 
{
public:
	static void convert(const SRC_PIXEL &src, YCbCrf32Pixel *dst)
	{
		dst->setYCbCr(
			(src.luminance() - SRC_PIXEL::minLuminance()) / float(SRC_PIXEL::maxLuminance()-SRC_PIXEL::minLuminance()), 
			(src.chromaBlue() - SRC_PIXEL::minChromaBlue()) / float(SRC_PIXEL::maxChromaBlue()-SRC_PIXEL::minChromaBlue()), 
			(src.chromaRed() - SRC_PIXEL::minChromaRed()) / float(SRC_PIXEL::maxChromaRed()-SRC_PIXEL::minChromaRed())
		);
	}
};


//==============================================================================
// CLASS PixelColorSpaceConverter:
//		ColorSpace_YCbCr_ITU601::YCbCrf32Pixel => ColorSpace_YCbCr_ITU601::*
//==============================================================================
// From YCbCrf32Pixel to any YCbCr_601
template<typename DST_PIXEL>
class PixelColorSpaceConverter<YCbCrf32Pixel, DST_PIXEL, ColorSpace_YCbCr_ITU601, ColorSpace_YCbCr_ITU601>
{
public: 
	static void convert(const YCbCrf32Pixel &src, DST_PIXEL *dst)
	{
		dst->setYCbCr(
			typename DST_PIXEL::YComponentType(src.luminance() * (DST_PIXEL::maxLuminance()-DST_PIXEL::minLuminance()) + DST_PIXEL::minLuminance()), 
			typename DST_PIXEL::CbComponentType(src.chromaBlue() * (DST_PIXEL::maxChromaBlue()-DST_PIXEL::minChromaBlue()) + DST_PIXEL::minChromaBlue()), 
			typename DST_PIXEL::CrComponentType(src.chromaRed() * (DST_PIXEL::maxChromaRed()-DST_PIXEL::minChromaRed()) + DST_PIXEL::minChromaRed())
		);
	}
};

#endif // __ITL_PIXELCONVERTER_ITU601_H__



#endif 0
