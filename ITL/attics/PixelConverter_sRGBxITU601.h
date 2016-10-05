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
#ifndef __ITL_PIXELCONVERTER_sRGBxITU601_H__
#define __ITL_PIXELCONVERTER_sRGBxITU601_H__

//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================
#include "PixelConverter.h"

//==============================================================================
// CLASS PixelColorSpaceConverter: 
//		ColorSpace_YCbCr_ITU601::* => ColorSpace_sRGB::*
//==============================================================================
template<typename SRC_PIXEL, typename DST_PIXEL>
class PixelColorSpaceConverter<SRC_PIXEL, DST_PIXEL, ColorSpace_YCbCr_ITU601, ColorSpace_sRGB> 
{
public:
	static void convert(const SRC_PIXEL &src, DST_PIXEL *dst)
	{
		YCbCrf32Pixel floatYCbCr;
		RGBf32Pixel floatRGB;
		PixelConvert(src, &floatYCbCr);
		PixelConvert(floatYCbCr, &floatRGB);
		PixelConvert(floatRGB, dst);
	}
};

template<>
class PixelColorSpaceConverter<YCbCrf32Pixel, RGBf32Pixel, ColorSpace_YCbCr_ITU601, ColorSpace_sRGB>;

template<>
class PixelColorSpaceConverter<RGBf32Pixel, YCbCrf32Pixel, ColorSpace_sRGB, ColorSpace_YCbCr_ITU601>;

//==============================================================================
// CLASS PixelColorSpaceConverter: 
//		ColorSpace_sRGB::* => ColorSpace_YCbCr_ITU601::*
//==============================================================================
template<typename SRC_PIXEL, typename DST_PIXEL>
class PixelColorSpaceConverter<SRC_PIXEL, DST_PIXEL, ColorSpace_sRGB, ColorSpace_YCbCr_ITU601> 
{
public:
	static void convert(const SRC_PIXEL &src, DST_PIXEL *dst)
	{
		RGBf32Pixel floatRGB;
		YCbCrf32Pixel floatYCbCr;
		PixelConvert(src, &floatRGB);
		PixelConvert(floatRGB, &floatYCbCr);
		PixelConvert(floatYCbCr, dst);
	}
};

//==============================================================================
// CLASS PixelColorSpaceConverter: 
//		ColorSpace_YCbCr_ITU601::YCbCrf32Pixel => ColorSpace_sRGB::RGBf32Pixel
//==============================================================================
template<>
class PixelColorSpaceConverter<YCbCrf32Pixel, RGBf32Pixel, ColorSpace_YCbCr_ITU601, ColorSpace_sRGB>
{
public:
	static void convert(const YCbCrf32Pixel &src, RGBf32Pixel *dst)
	{
		dst->setRGB(
			src.luminance() + 1.402f * (src.chromaRed()-0.5f),
			src.luminance() - 0.34414f * (src.chromaBlue()-0.5f) - 0.71414f * (src.chromaRed()-0.5f),
			src.luminance() + 1.772f * (src.chromaBlue()-0.5f)
		);
	}
};

//==============================================================================
// CLASS PixelColorSpaceConverter: 
//		ColorSpace_YCbCr_ITU601::YCbCrf32Pixel => ColorSpace_sRGB::RGBf32Pixel
//==============================================================================
template<>
class PixelColorSpaceConverter<RGBf32Pixel, YCbCrf32Pixel, ColorSpace_sRGB, ColorSpace_YCbCr_ITU601>
{
public:
	static void convert(const RGBf32Pixel &src, YCbCrf32Pixel *dst)
	{
		dst->setYCbCr(
			0.299f * src.red() + 0.587f * src.green() + 0.114f * src.blue(),
			-0.168736f * src.red() + 0.331264f * src.green() + 0.5f * src.blue(),
			0.5f * src.red() - 0.418688f * src.green() - 0.081312f * src.blue()
		);
	}
};


//==============================================================================
// CLASS PixelColorSpaceConverter
//		ColorSpace_sRGB::*[444] => ColorSpace_YCbCr_ITU601::*[422]
//==============================================================================
template<typename SRC_PIXEL0, typename SRC_PIXEL1, typename DST_PIXEL>
class PixelColorSpaceConverter2<SRC_PIXEL0, SRC_PIXEL1, DST_PIXEL, ColorSpace_sRGB, ColorSpace_YCbCr_ITU601>
{
public:
	static void convert(const SRC_PIXEL0 &src0, const SRC_PIXEL0 &src1, DST_PIXEL *dst)
	{
		RGBf32Pixel floatRGB0;
		RGBf32Pixel floatRGB1;
		YCbCrf32Pixel floatYCbCr0;
		YCbCrf32Pixel floatYCbCr1;
		PixelConvert(src0, &floatRGB0);
		PixelConvert(src1, &floatRGB1);
		PixelConvert(floatRGB0, &floatYCbCr0);
		PixelConvert(floatRGB1, &floatYCbCr1);
		PixelConvert(floatYCbCr0, floatYCbCr1, dst);
	}
};

#endif // __ITL_PIXELCONVERTER_sRGBxITU601_H__


#endif // 0
