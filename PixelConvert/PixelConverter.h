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
#ifndef __ITL_PIXELCONVERTER_H__
#define __ITL_PIXELCONVERTER_H__

//==============================================================================
// FILE PixelConverter.h
//==============================================================================
// Provides the function PixelConvert which can be used to convert
// between different types of pixels. e.g.:
//
// RGB24Pixel p1;
// RGB48Pixel p2;
// PixelConvert(p1, &p2); // converts a 8bit RGB pixel to a 16bit RGB pixel
//
// RGB24PlanarPixel p1;
// RGB24Pixel p2;
// PixelConvert(p1, &p2); // converts a 8bit RGB planer pixel to a 8bit packed RGB pixel
//
// YCbCr24Pixel p1;
// RGB24Pixel p2;
// PixelConvert(p1, &p2); // converts a 8bit YCbCr planer pixel to a 8bit RGB pixel
//
// RGB24Pixel p1;
// RGB24Pixel p2;
// PixelConvert(p1, &p2); // copies the pixel

		// FIXME:
		// If we adjust the pixel to rely on an object for their range, we could
		// generalize a function such that it takes SRC_RANGE, DST_RANGE as it's
		// template parameters to scale the components from one type to another:
		//
		// template<typename SRC_RANGE, typename DST_RANGE> 
		// ScaleComponents(const SRC_RANGE::Type &val)
		// {
		//     float normalized = (val - SRC_RANGE::min()) / (SRC_RANGE::max()-SRC_RANGE::min());
		//     return normalized*(DST_RANGE::max() - DST_RANGE::min()) + DST_RANGE::min();
		// }


//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================
#include "../Storage/ColorSpace.h"
#include "../RGB/RGBPixel.h"
#include "../YCbCr/YCbCrPixel.h"

//==============================================================================
// FORWARD DECLARATIONS
//==============================================================================
template<typename SRC_PIXEL, typename DST_PIXEL>
inline void PixelConvert(const SRC_PIXEL &src, DST_PIXEL *dst);

template<typename SRC_PIXEL0, typename SRC_PIXEL1, typename DST_PIXEL>
inline void PixelConvert(const SRC_PIXEL0 &src0, const SRC_PIXEL1 &src1, DST_PIXEL *dst);

//==============================================================================
// CLASS PixelColorSpaceConverter
//==============================================================================
template<typename SRC_PIXEL, typename DST_PIXEL, typename SRC_COLORSPACE=typename SRC_PIXEL::ColorSpace, typename DST_COLORSPACE=typename DST_PIXEL::ColorSpace>
class PixelColorSpaceConverter
{
public:
	static void convert(const SRC_PIXEL &src, DST_PIXEL *dst)
	{
		dst->convert(src);
	}
};

//==============================================================================
// CLASS PixelColorSpaceConverter2
//==============================================================================
template<typename SRC_PIXEL0, typename SRC_PIXEL1, typename DST_PIXEL, typename SRC_COLORSPACE=typename SRC_PIXEL0::ColorSpace, typename DST_COLORSPACE=typename DST_PIXEL::ColorSpace>
class PixelColorSpaceConverter2
{
public:
	static void convert(const SRC_PIXEL0 &src0, const SRC_PIXEL1 &src1, DST_PIXEL *dst)
	{
		dst->convert(src0, src1);
	}
};

//==============================================================================
// CLASS PixelColorSpaceConverter2
//==============================================================================
template<typename SRC_PIXEL0, typename SRC_PIXEL1, typename SRC_PIXEL2, typename SRC_PIXEL3, typename SRC_PIXEL4, typename SRC_PIXEL5, typename SRC_PIXEL6, typename SRC_PIXEL7, typename DST_PIXEL, typename SRC_COLORSPACE=typename SRC_PIXEL0::ColorSpace, typename DST_COLORSPACE=typename DST_PIXEL::ColorSpace>
class PixelColorSpaceConverter8
{
public:
	static void convert(const SRC_PIXEL0 &src0, const SRC_PIXEL1 &src1, const SRC_PIXEL1 &src2, const SRC_PIXEL3 &src3, const SRC_PIXEL4 &src4, const SRC_PIXEL5 &src5, const SRC_PIXEL6 &src6, const SRC_PIXEL7 &src7, DST_PIXEL *dst)
	{
		dst->convert(src0, src1, src2, src3, src4, src5, src6, src7);
	}
};


//==============================================================================
// CLASS PixelConverter
//==============================================================================
// In general, use the PixelColorSpaceConverter
template<typename SRC_PIXEL, typename DST_PIXEL>
class PixelConverter
{
public:
	static void convert(const SRC_PIXEL &src, DST_PIXEL *dst)
	{ PixelColorSpaceConverter<SRC_PIXEL, DST_PIXEL>::convert(src, dst);	}
};

template<typename SRC_PIXEL0, typename SRC_PIXEL1, typename DST_PIXEL>
class PixelConverter2
{
public:
	static void convert(const SRC_PIXEL0 &src0, const SRC_PIXEL1 &src1, DST_PIXEL *dst)
	{ PixelColorSpaceConverter2<SRC_PIXEL0, SRC_PIXEL1, DST_PIXEL>::convert(src0, src1, dst);	}
};

template<typename SRC_PIXEL0, typename SRC_PIXEL1, typename SRC_PIXEL2, typename SRC_PIXEL3, typename SRC_PIXEL4, typename SRC_PIXEL5, typename SRC_PIXEL6, typename SRC_PIXEL7, typename DST_PIXEL>
class PixelConverter8
{
public:
	static void convert(const SRC_PIXEL0 &src0, const SRC_PIXEL1 &src1, const SRC_PIXEL2 &src2, const SRC_PIXEL3 &src3, const SRC_PIXEL4 &src4, const SRC_PIXEL5 &src5, const SRC_PIXEL6 &src6, const SRC_PIXEL7 &src7, DST_PIXEL *dst)
	{ PixelColorSpaceConverter8<SRC_PIXEL0, SRC_PIXEL1, SRC_PIXEL2, SRC_PIXEL3, SRC_PIXEL4, SRC_PIXEL5, SRC_PIXEL6, SRC_PIXEL7, DST_PIXEL>::convert(src0, src1, src2, src3, src4, src5, src6, src7, dst);	}
};

//==============================================================================
// CLASS PixelConverter<PIXEL,PIXEL>
//		PIXEL_ABC => PIXEL_ABC (copy)
//==============================================================================
// Special case when the two pixels are of the same type
template<typename PIXEL>
class PixelConverter<PIXEL,PIXEL> 
{
public: 
	static void convert(const PIXEL &src, PIXEL *dst)
	{	*dst = src;		}
};

//==============================================================================
// FREE FUNCTION
//==============================================================================
// Makes it easier to use the other classes (template parameters will be found
// by the compiler automatically
template<typename SRC_PIXEL, typename DST_PIXEL>
inline void PixelConvert(const SRC_PIXEL &src, DST_PIXEL *dst)
{
	PixelConverter<SRC_PIXEL, DST_PIXEL>::convert(src, dst);
}

template<typename SRC_PIXEL0, typename SRC_PIXEL1, typename DST_PIXEL>
inline void PixelConvert(const SRC_PIXEL0 &src0, const SRC_PIXEL1 &src1, DST_PIXEL *dst)
{
	PixelConverter2<SRC_PIXEL0, SRC_PIXEL1, DST_PIXEL>::convert(src0, src1, dst);
}


template<typename SRC_PIXEL0, typename SRC_PIXEL1, typename SRC_PIXEL2, typename SRC_PIXEL3, typename SRC_PIXEL4, typename SRC_PIXEL5, typename SRC_PIXEL6, typename SRC_PIXEL7, typename DST_PIXEL>
inline void PixelConvert(const SRC_PIXEL0 &src0, const SRC_PIXEL1 &src1, const SRC_PIXEL2 &src2, const SRC_PIXEL3 &src3, const SRC_PIXEL4 &src4, const SRC_PIXEL5 &src5, const SRC_PIXEL6 &src6, const SRC_PIXEL7 &src7, DST_PIXEL *dst)
{
	PixelConverter8<SRC_PIXEL0, SRC_PIXEL1, SRC_PIXEL2, SRC_PIXEL3, SRC_PIXEL4, SRC_PIXEL5, SRC_PIXEL6, SRC_PIXEL7, DST_PIXEL>::convert(src0, src1, src2, src3, src4, src5, src6, src7, dst);
}


#include "YCbCrFromRGB.h"
#include "RGBFromYCbCr.h"
#include "RGBFromCMYK.h"

#include "../RGB/RGBPixel.h"

#include "Alpha.h"
#include "Black.h"
#include "Blue.h"
#include "ChromaBlue.h"
#include "ChromaRed.h"
#include "Cyan.h"
#include "Green.h"
#include "Luminance.h"
#include "Magenta.h"
#include "Red.h"
#include "Yellow.h"


#endif // __ITL_PIXELCONVERTER_H__


