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
#ifndef __ITL_PIXELCONVERTER_RGBFROMCMYK_H__
#define __ITL_PIXELCONVERTER_RGBFROMCMYK_H__

//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================
#include "../Storage/ComponentModel.h"
#include "../Storage/ComponentArray.h"
#include "../CMY/CMYPixel.h"
#include "../RGB/RGBPixel.h"
#include "../CMY/CMYPixel.h"
#include "../CMY/CMYKPixel.h"

struct PixelConvertCMYFromCMYK_Float
{
	static CMY32fPixel convert(const CMYK32fPixel &cmyk)
	{
		return CMY32fPixel(
			cmyk.cyan()    * (1 - cmyk.black()) + cmyk.black(),
			cmyk.magenta() * (1 - cmyk.black()) + cmyk.black(),
			cmyk.yellow()  * (1 - cmyk.black()) + cmyk.black()
		);
	}
};

struct PixelConvertRGBFromCMYK_Float
{
	static RGB32fPixel convert(const CMYK32fPixel &cmyk)
	{
		CMY32fPixel cmy = PixelConvertCMYFromCMYK_Float::convert(cmyk);
		return RGB32fPixel(
			1.0f - cmy.cyan(),
			1.0f - cmy.magenta(),
			1.0f - cmy.yellow()
		);
	}

	static RGB32fPixel convert(const Black32fPixel &k)
	{
		return RGB32fPixel(
			1.0f - k.black(),
			1.0f - k.black(),
			1.0f - k.black()
		);
	}

};

template<typename SRC_PIXELTYPE, typename DST_PIXELTYPE, typename SRC_COMPONENTMODEL=typename SRC_PIXELTYPE::ComponentModel, typename SRC_COLORSPACE=typename SRC_PIXELTYPE::ColorSpace, typename DST_COMPONENTMODEL=typename DST_PIXELTYPE::ComponentModel, typename DST_COLORSPACE=typename DST_PIXELTYPE::ColorSpace, int HASCYAN=std::tr1::is_base_of<ComponentModel_Cyan, typename SRC_PIXELTYPE::ComponentModel>::value, int HASMAGENTA=std::tr1::is_base_of<ComponentModel_Magenta, typename SRC_PIXELTYPE::ComponentModel>::value, int HASYELLOW=std::tr1::is_base_of<ComponentModel_Yellow, typename SRC_PIXELTYPE::ComponentModel>::value, int HASBLACK=std::tr1::is_base_of<ComponentModel_Black, typename SRC_PIXELTYPE::ComponentModel>::value>
struct PixelConvertRGBFromCMYK;

template<typename SRC_PIXELTYPE, typename DST_PIXELTYPE, typename SRC_COMPONENTMODEL, typename DST_COMPONENTMODEL>
struct PixelConvertRGBFromCMYK<SRC_PIXELTYPE, DST_PIXELTYPE, SRC_COMPONENTMODEL, ColorSpace_CMYK, DST_COMPONENTMODEL, ColorSpace_sRGB, true, true, true, true>
{
	typedef typename DST_PIXELTYPE::RedStorageType RedStorageType;
	typedef typename DST_PIXELTYPE::GreenStorageType GreenStorageType;
	typedef typename DST_PIXELTYPE::BlueStorageType BlueStorageType;

	typedef typename SRC_PIXELTYPE::CyanStorageType CyanStorageType;
	typedef typename SRC_PIXELTYPE::MagentaStorageType MagentaStorageType;
	typedef typename SRC_PIXELTYPE::YellowStorageType YellowStorageType;
	typedef typename SRC_PIXELTYPE::BlackStorageType BlackStorageType;

	PixelConvertRGBFromCMYK(const SRC_PIXELTYPE &src) : _src(src) {}

	void convert(typename RedStorageType::ComponentType *red, typename GreenStorageType::ComponentType *green, typename BlueStorageType::ComponentType *blue) const
	{
		CMYK32fPixel cmyk(
			ConvertComponentRange<CyanStorageType, FloatComponent>::eval(_src.cyan()),
			ConvertComponentRange<MagentaStorageType, FloatComponent>::eval(_src.magenta()),
			ConvertComponentRange<YellowStorageType, FloatComponent>::eval(_src.yellow()),
			ConvertComponentRange<BlackStorageType, FloatComponent>::eval(_src.black())
		);
		
		RGB32fPixel rgb = PixelConvertRGBFromCMYK_Float::convert(cmyk);
		
		if (red)   *red   = ConvertComponentRange<FloatComponent, RedStorageType>::eval(rgb.red());
		if (green) *green = ConvertComponentRange<FloatComponent, RedStorageType>::eval(rgb.green());
		if (blue)  *blue  = ConvertComponentRange<FloatComponent, RedStorageType>::eval(rgb.blue());
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



template<typename SRC_PIXELTYPE, typename DST_PIXELTYPE, typename SRC_COMPONENTMODEL, typename DST_COMPONENTMODEL>
struct PixelConvertRGBFromCMYK<SRC_PIXELTYPE, DST_PIXELTYPE, SRC_COMPONENTMODEL, ColorSpace_CMYK, DST_COMPONENTMODEL, ColorSpace_sRGB, false, false, false, true>
{
	typedef typename DST_PIXELTYPE::RedStorageType RedStorageType;
	typedef typename DST_PIXELTYPE::GreenStorageType GreenStorageType;
	typedef typename DST_PIXELTYPE::BlueStorageType BlueStorageType;

	typedef typename SRC_PIXELTYPE::BlackStorageType BlackStorageType;

	PixelConvertRGBFromCMYK(const SRC_PIXELTYPE &src) : _src(src) {}

	void convert(typename RedStorageType::ComponentType *red, typename GreenStorageType::ComponentType *green, typename BlueStorageType::ComponentType *blue) const
	{
		Black32fPixel k(
			ConvertComponentRange<BlackStorageType, FloatComponent>::eval(_src.black())
		);
		
		RGB32fPixel rgb = PixelConvertRGBFromCMYK_Float::convert(k);
		
		if (red)   *red   = ConvertComponentRange<FloatComponent, RedStorageType>::eval(rgb.red());
		if (green) *green = ConvertComponentRange<FloatComponent, RedStorageType>::eval(rgb.green());
		if (blue)  *blue  = ConvertComponentRange<FloatComponent, RedStorageType>::eval(rgb.blue());
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



#endif // __ITL_PIXELCONVERTER_RGBFROMCMYK_H__



