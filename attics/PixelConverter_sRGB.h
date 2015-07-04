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
#ifndef __ITL_PIXELCONVERTER_sRGB_H__
#define __ITL_PIXELCONVERTER_sRGB_H__

//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================
#include "PixelConverter.h"
#include "PixelConverter_sRGB_opt.h"

//==============================================================================
// GENERIC RGB<=>RGB CONVERSION
//==============================================================================

//==============================================================================
// CLASS PixelColorSpaceConverter:
//		ColorSpace_sRGB::* => ColorSpace_sRGB::*
//==============================================================================
// Generic RGB to RGB.  Use a RGBf32Pixel as an intermediary.
template<typename SRC_PIXEL, typename DST_PIXEL>
class PixelColorSpaceConverter<SRC_PIXEL, DST_PIXEL, ColorSpace_sRGB, ColorSpace_sRGB> 
{
public:
	static void convert(const SRC_PIXEL &src, DST_PIXEL *dst)
	{
		RGBf32Pixel temp;
		PixelConvert(src, &temp);
		PixelConvert(temp, dst);
	}
};

//==============================================================================
// CLASS PixelColorSpaceConverter:
//		ColorSpace_sRGB::* => ColorSpace_sRGB::RGBf32Pixel
//==============================================================================
// From any RGB to RGBf32Pixel
template<typename SRC_PIXEL>
class PixelColorSpaceConverter<SRC_PIXEL, RGBf32Pixel, ColorSpace_sRGB, ColorSpace_sRGB> 
{
public:
	static void convert(const SRC_PIXEL &src, RGBf32Pixel *dst)
	{
		dst->setRGB(
			(src.red() - SRC_PIXEL::minRed()) / float(SRC_PIXEL::maxRed()-SRC_PIXEL::minRed()), 
			(src.green() - SRC_PIXEL::minGreen()) / float(SRC_PIXEL::maxGreen()-SRC_PIXEL::minGreen()), 
			(src.blue() - SRC_PIXEL::minBlue()) / float(SRC_PIXEL::maxBlue()-SRC_PIXEL::minBlue())
		);
	}
};

//==============================================================================
// CLASS PixelColorSpaceConverter:
//		ColorSpace_sRGB::RGBf32Pixel => ColorSpace_sRGB::*
//==============================================================================
// From RGBf32Pixel to any RGB
template<typename DST_PIXEL>
class PixelColorSpaceConverter<RGBf32Pixel, DST_PIXEL, ColorSpace_sRGB, ColorSpace_sRGB>
{
public: 
	static void convert(const RGBf32Pixel &src, DST_PIXEL *dst)
	{
		dst->setRGB(
			typename DST_PIXEL::RedComponentType((src.red() * (DST_PIXEL::maxRed()-DST_PIXEL::minRed()) + DST_PIXEL::minRed())), 
			typename DST_PIXEL::GreenComponentType((src.green() * (DST_PIXEL::maxGreen()-DST_PIXEL::minGreen()) + DST_PIXEL::minGreen())), 
			typename DST_PIXEL::BlueComponentType((src.blue() * (DST_PIXEL::maxBlue()-DST_PIXEL::minBlue()) + DST_PIXEL::minBlue()))
		);
	}
};

#endif // __ITL_PIXELCONVERTER_sRGB_H__


#endif // 0