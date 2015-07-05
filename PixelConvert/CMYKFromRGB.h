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
#ifndef __ITL_PIXELCONVERTER_CMYKFROMRGB_H__
#define __ITL_PIXELCONVERTER_CMYKFROMRGB_H__

#include "../Storage/ColorSpace.h"
#include "../Storage/ComponentModel.h"
#include <Enseed/Generic/Base/Base.h>
#include <Enseed/Generic/Math/Float.h>
#include "../CMY/CMYKPixel.h"
#include "../CMY/CMYPixel.h"

class PixelConvertCMYFromRGB_Float
{
public:
	static CMY32fPixel convert(const RGB32fPixel &rgb)
	{
		return CMY32fPixel(
			1 - rgb.red(),
			1 - rgb.green(),
			1 - rgb.blue()
		);
	}
};

class PixelConvertCMYKFromRGB_Float
{
public:
	static CMYK32fPixel convert(const RGB32fPixel &rgb)
	{
		// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		// first, convert to CMY
		CMY32fPixel cmy = PixelConvertCMYFromRGB_Float::convert(rgb);

		// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		// next, find a K which satisfies CMY
		CMYK32fPixel cmyk;
		cmyk.setBlack( seed::Float::min(cmy.cyan(), cmy.magenta(), cmy.yellow()) );

		// NOTE - one of the component is for sure going to be 0, so we could
		// skip the following for that component..

		// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		// scale the components according to the black
		if (cmyk.black() < 1)
		{
			cmyk.setCyan(    (cmy.cyan() - cmyk.black())     / (1 - cmyk.black()) );
			cmyk.setMagenta( (cmy.magenta() - cmyk.black())  / (1 - cmyk.black()) );
			cmyk.setYellow(  (cmy.yellow() - cmyk.black())   / (1 - cmyk.black()) );
		}
		else
		{
			cmyk.setCyan(    cmy.cyan() - cmyk.black() );
			cmyk.setMagenta( cmy.magenta() - cmyk.black() );
			cmyk.setYellow(  cmy.yellow() - cmyk.black() );
		}
		
		return cmyk;
	}
};

//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================
template<typename SRC_PIXELTYPE, typename DST_PIXELTYPE, typename SRC_COMPONENTMODEL=typename SRC_PIXELTYPE::ComponentModel, typename SRC_COLORSPACE=typename SRC_PIXELTYPE::ColorSpace, typename DST_COMPONENTMODEL=typename DST_PIXELTYPE::ComponentModel, typename DST_COLORSPACE=typename DST_PIXELTYPE::ColorSpace, int HASCYAN=std::tr1::is_base_of<ComponentModel_Cyan, typename DST_PIXELTYPE::ComponentModel>::value, int HASMAGENTA=std::tr1::is_base_of<ComponentModel_Magenta, typename DST_PIXELTYPE::ComponentModel>::value, int HASYELLOW=std::tr1::is_base_of<ComponentModel_Yellow, typename DST_PIXELTYPE::ComponentModel>::value, int HASBLACK=std::tr1::is_base_of<ComponentModel_Black, typename DST_PIXELTYPE::ComponentModel>::value>
struct PixelConvertCMYKFromRGB;

template<typename SRC_PIXELTYPE, typename DST_PIXELTYPE, typename SRC_COMPONENTMODEL, typename DST_COMPONENTMODEL>
struct PixelConvertCMYKFromRGB<SRC_PIXELTYPE, DST_PIXELTYPE, SRC_COMPONENTMODEL, ColorSpace_sRGB, DST_COMPONENTMODEL, ColorSpace_CMYK, true, true, true, true>
{
	typedef typename SRC_PIXELTYPE::RedStorageType RedStorageType;
	typedef typename SRC_PIXELTYPE::GreenStorageType GreenStorageType;
	typedef typename SRC_PIXELTYPE::BlueStorageType BlueStorageType;

	typedef typename DST_PIXELTYPE::CyanStorageType CyanStorageType;
	typedef typename DST_PIXELTYPE::MagentaStorageType MagentaStorageType;
	typedef typename DST_PIXELTYPE::YellowStorageType YellowStorageType;
	typedef typename DST_PIXELTYPE::BlackStorageType BlackStorageType;

	PixelConvertCMYKFromRGB(const SRC_PIXELTYPE &src) : _src(src) {}

	void convert(typename CyanStorageType::ComponentType *c, typename MagentaStorageType::ComponentType *m, typename YellowStorageType::ComponentType *y, typename BlackStorageType::ComponentType *k) const
	{
		RGB32fPixel rgb(
			ConvertComponentRange<RedStorageType, FloatComponent>::eval(_src.red()),
			ConvertComponentRange<GreenStorageType, FloatComponent>::eval(_src.green()),
			ConvertComponentRange<BlueStorageType, FloatComponent>::eval(_src.blue())
		);
		
		CMYK32fPixel cmyk = PixelConvertCMYKFromRGB_Float::convert(rgb);

		if (c)  *c  = ConvertComponentRange<FloatComponent, CyanStorageType>::eval(cmyk.cyan());
		if (m)  *m  = ConvertComponentRange<FloatComponent, MagentaStorageType>::eval(cmyk.magenta());
		if (y)  *y  = ConvertComponentRange<FloatComponent, YellowStorageType>::eval(cmyk.yellow());
		if (k)  *k  = ConvertComponentRange<FloatComponent, BlackStorageType>::eval(cmyk.black());
	}
		
	typename BlackStorageType::ComponentType black() const
	{
		typename BlackStorageType::ComponentType val;	
		convert(NULL, NULL, NULL, &val);
		return val;
	}

	typename CyanStorageType::ComponentType cyan() const
	{
		typename CyanStorageType::ComponentType val;	
		convert(&val, NULL, NULL, NULL);
		return val;
	}

	typename MagentaStorageType::ComponentType magenta() const
	{
		typename MagentaStorageType::ComponentType val;	
		convert(NULL, &val, NULL, NULL);
		return val;
	}

	typename YellowStorageType::ComponentType yellow() const
	{
		typename YellowStorageType::ComponentType val;	
		convert(NULL, NULL, &val, NULL);
		return val;
	}

private:
	const SRC_PIXELTYPE &_src;
};


template<typename SRC_PIXELTYPE, typename DST_PIXELTYPE, typename SRC_COMPONENTMODEL, typename DST_COMPONENTMODEL>
struct PixelConvertCMYKFromRGB<SRC_PIXELTYPE, DST_PIXELTYPE, SRC_COMPONENTMODEL, ColorSpace_sRGB, DST_COMPONENTMODEL, ColorSpace_CMYK, false, false, false, true>
{
	typedef typename SRC_PIXELTYPE::RedStorageType RedStorageType;
	typedef typename SRC_PIXELTYPE::GreenStorageType GreenStorageType;
	typedef typename SRC_PIXELTYPE::BlueStorageType BlueStorageType;

	typedef typename DST_PIXELTYPE::BlackStorageType BlackStorageType;

	PixelConvertCMYKFromRGB(const SRC_PIXELTYPE &src) : _src(src) {}

	void convert(typename BlackStorageType::ComponentType *k) const
	{
		// FIXME - we should use Luminance to make this right...
		RGB32fPixel rgb(
			ConvertComponentRange<RedStorageType, FloatComponent>::eval(_src.red()),
			ConvertComponentRange<GreenStorageType, FloatComponent>::eval(_src.green()),
			ConvertComponentRange<BlueStorageType, FloatComponent>::eval(_src.blue())
		);
		
		float lum = (rgb.red() + rgb.green() + rgb.blue()) / 3;

		if (k)  *k  = ConvertComponentRange<FloatComponent, BlackStorageType>::eval(1 - lum);
	}
		
	typename BlackStorageType::ComponentType black() const
	{
		typename BlackStorageType::ComponentType val;	
		convert(&val);
		return val;
	}


private:
	const SRC_PIXELTYPE &_src;
};


#endif // __ITL_PIXELCONVERTER_CMYKFROMRGB_H__



