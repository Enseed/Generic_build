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
#ifndef __ITL_PIXELCONVERTER_RGBFROMYCBCR_H__
#define __ITL_PIXELCONVERTER_RGBFROMYCBCR_H__

//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================
#include "../Storage/ComponentModel.h"
#include "../Storage/ComponentArray.h"
#ifndef _WIN32
#include <tr1/type_traits>
#else
#include <type_traits> 
#endif

#include "../RGB/RGBPixel.h"
#include "../YCbCr/YCbCrPixel.h"
#include <Enseed/Generic/Geometry/Matrix.h>


class PixelConvertRGBFromYCbCr_Float
{
public:
	static RGB32fPixel convert(const YCbCr32fPixel &yuv)
	{
		return RGB32fPixel(
			yuv.luminance() + 1.403f   * yuv.chromaRed(),
			yuv.luminance() - 0.34414f * yuv.chromaBlue() - 0.71414f * yuv.chromaRed(),
			yuv.luminance() + 1.772f  * yuv.chromaBlue()
		);
	}
};


template<typename SRC_PIXELTYPE, typename DST_PIXELTYPE, typename SRC_COMPONENTMODEL=typename SRC_PIXELTYPE::ComponentModel, typename SRC_COLORSPACE=typename SRC_PIXELTYPE::ColorSpace, typename DST_COMPONENTMODEL=typename DST_PIXELTYPE::ComponentModel, typename DST_COLORSPACE=typename DST_PIXELTYPE::ColorSpace, int HASLUMINANCE=std::tr1::is_base_of<ComponentModel_Luminance, typename SRC_PIXELTYPE::ComponentModel>::value, int HASCHROMABLUE=std::tr1::is_base_of<ComponentModel_ChromaBlue, typename SRC_PIXELTYPE::ComponentModel>::value, int HASCHROMARED=std::tr1::is_base_of<ComponentModel_ChromaRed, typename SRC_PIXELTYPE::ComponentModel>::value>
class PixelConvertRGBFromYCbCr;

//==============================================================================
// CASE: ITU601 to sRGB with full YCbCr
//==============================================================================
template<typename SRC_PIXELTYPE, typename DST_PIXELTYPE, typename SRC_COMPONENTMODEL, typename DST_COMPONENTMODEL>
struct PixelConvertRGBFromYCbCr<SRC_PIXELTYPE, DST_PIXELTYPE, SRC_COMPONENTMODEL, ColorSpace_YCbCr_ITU601, DST_COMPONENTMODEL, ColorSpace_sRGB, true, true, true>
{
	typedef typename DST_PIXELTYPE::RedStorageType RedStorageType;
	typedef typename DST_PIXELTYPE::GreenStorageType GreenStorageType;
	typedef typename DST_PIXELTYPE::BlueStorageType BlueStorageType;

	typedef typename SRC_PIXELTYPE::LuminanceStorageType LuminanceStorageType;
	typedef typename SRC_PIXELTYPE::ChromaBlueStorageType ChromaBlueStorageType;
	typedef typename SRC_PIXELTYPE::ChromaRedStorageType ChromaRedStorageType;

	PixelConvertRGBFromYCbCr(const SRC_PIXELTYPE &src) : _src(src) {}

	void convert(typename RedStorageType::ComponentType *red, typename GreenStorageType::ComponentType *green, typename BlueStorageType::ComponentType *blue) const
	{
		YCbCr32fPixel yuv(
			ConvertComponentRange<LuminanceStorageType, FloatComponent>::eval(_src.luminance()),
			ConvertComponentRange<ChromaBlueStorageType, SignedFloatComponent>::eval(_src.chromaBlue()),
			ConvertComponentRange<ChromaRedStorageType, SignedFloatComponent>::eval(_src.chromaRed())
		);
		
		RGB32fPixel rgb = PixelConvertRGBFromYCbCr_Float::convert(yuv);
		
		if (red)   *red   = ConvertComponentRange<FloatComponent, RedStorageType>::eval(rgb.red());
		if (green) *green = ConvertComponentRange<FloatComponent, GreenStorageType>::eval(rgb.green());
		if (blue)  *blue  = ConvertComponentRange<FloatComponent, BlueStorageType>::eval(rgb.blue());
	}

	typename RedStorageType::ComponentType red() const
	{
		typename RedStorageType::ComponentType val;	
		convert(&val, NULL, NULL);
		return val;
	}

	typename GreenStorageType::ComponentType green() const
	{
		typename GreenStorageType::ComponentType val;	
		convert(NULL, &val, NULL);
		return val;
	}

	typename BlueStorageType::ComponentType blue() const
	{
		typename BlueStorageType::ComponentType val;	
		convert(NULL, NULL, &val);
		return val;
	}

private:
	const SRC_PIXELTYPE &_src;
};


//==============================================================================
// CASE: ITU601 to sRGB with only Y
//==============================================================================
template<typename SRC_PIXELTYPE, typename DST_PIXELTYPE, typename SRC_COMPONENTMODEL, typename DST_COMPONENTMODEL>
struct PixelConvertRGBFromYCbCr<SRC_PIXELTYPE, DST_PIXELTYPE, SRC_COMPONENTMODEL, ColorSpace_YCbCr_ITU601, DST_COMPONENTMODEL, ColorSpace_sRGB, true, false, false>
{
	typedef typename DST_PIXELTYPE::RedStorageType RedStorageType;
	typedef typename DST_PIXELTYPE::GreenStorageType GreenStorageType;
	typedef typename DST_PIXELTYPE::BlueStorageType BlueStorageType;

	typedef typename SRC_PIXELTYPE::LuminanceStorageType LuminanceStorageType;

	PixelConvertRGBFromYCbCr(const SRC_PIXELTYPE &src) : _src(src) {}

	void convert(typename RedStorageType::ComponentType *red, typename GreenStorageType::ComponentType *green, typename BlueStorageType::ComponentType *blue) const
	{
		float y = ConvertComponentRange<LuminanceStorageType, FloatComponent>::eval(_src.luminance());
		if (red)   *red   = ConvertComponentRange<FloatComponent, RedStorageType>::eval(y);
		if (green) *green = ConvertComponentRange<FloatComponent, GreenStorageType>::eval(y);
		if (blue)  *blue  = ConvertComponentRange<FloatComponent, BlueStorageType>::eval(y);
	}

	typename RedStorageType::ComponentType red() const
	{
		typename RedStorageType::ComponentType val;	
		convert(&val, NULL, NULL);
		return val;
	}

	typename GreenStorageType::ComponentType green() const
	{
		typename GreenStorageType::ComponentType val;	
		convert(NULL, &val, NULL);
		return val;
	}

	typename BlueStorageType::ComponentType blue() const
	{
		typename BlueStorageType::ComponentType val;	
		convert(NULL, NULL, &val);
		return val;
	}

private:
	const SRC_PIXELTYPE &_src;
};

#endif // __ITL_PIXELCONVERTER_RGBFROMYCBCR_H__



