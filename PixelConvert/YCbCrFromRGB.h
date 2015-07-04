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
#ifndef __ITL_PIXELCONVERTER_YCBCRFROMRGB_H__
#define __ITL_PIXELCONVERTER_YCBCRFROMRGB_H__

//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================

class PixelConvertYCbCrFromRGB_Float
{
public:
	static YCbCr32fPixel convert(const RGB32fPixel &rgb)
	{
		return YCbCr32fPixel(
			0.299f     * rgb.red() + 0.587f    * rgb.green() + 0.114f    * rgb.blue(),
			-0.168736f * rgb.red() - 0.331264f * rgb.green() + 0.5f      * rgb.blue(),
			0.5f       * rgb.red() - 0.418688f * rgb.green() - 0.081312f * rgb.blue()
		);
	}
};

template<
	typename SRC_PIXELTYPE, typename DST_PIXELTYPE, 
	typename SRC_COLORSPACE=typename SRC_PIXELTYPE::ColorSpace, 
	int HASRED=std::tr1::is_base_of<ComponentModel_Red, typename SRC_PIXELTYPE::ComponentModel>::value, int HASGREEN=std::tr1::is_base_of<ComponentModel_Green, typename SRC_PIXELTYPE::ComponentModel>::value, int HASBLUE=std::tr1::is_base_of<ComponentModel_Blue, typename SRC_PIXELTYPE::ComponentModel>::value, 
	typename DST_COLORSPACE=typename DST_PIXELTYPE::ColorSpace,
	int HASLUMINANCE=std::tr1::is_base_of<ComponentModel_Luminance, typename DST_PIXELTYPE::ComponentModel>::value, int HASCHROMABLUE=std::tr1::is_base_of<ComponentModel_ChromaBlue, typename DST_PIXELTYPE::ComponentModel>::value, int HASCHROMARED=std::tr1::is_base_of<ComponentModel_ChromaRed, typename DST_PIXELTYPE::ComponentModel>::value>
class PixelConvertYCbCrFromRGB;


//==============================================================================
// CASE: FULL sRGB to FULL ITU601
//==============================================================================
template<typename SRC_PIXELTYPE, typename DST_PIXELTYPE>
class PixelConvertYCbCrFromRGB<SRC_PIXELTYPE, DST_PIXELTYPE, ColorSpace_sRGB, true, true, true, ColorSpace_YCbCr_ITU601, true, true, true>
{
	typedef typename SRC_PIXELTYPE::RedStorageType RedStorageType;
	typedef typename RedStorageType::ComponentType RedComponentType;

	typedef typename SRC_PIXELTYPE::GreenStorageType GreenStorageType;
	typedef typename GreenStorageType::ComponentType GreenComponentType;

	typedef typename SRC_PIXELTYPE::BlueStorageType BlueStorageType;
	typedef typename BlueStorageType::ComponentType BlueComponentType;

	typedef typename DST_PIXELTYPE::LuminanceStorageType LuminanceStorageType;
	typedef typename LuminanceStorageType::ComponentType LuminanceComponentType;

	typedef typename DST_PIXELTYPE::ChromaBlueStorageType ChromaBlueStorageType;
	typedef typename ChromaBlueStorageType::ComponentType ChromaBlueComponentType;

	typedef typename DST_PIXELTYPE::ChromaRedStorageType ChromaRedStorageType;
	typedef typename ChromaRedStorageType::ComponentType ChromaRedComponentType;

public:
	PixelConvertYCbCrFromRGB(const SRC_PIXELTYPE &src) : _src(src) {}

	void convert(LuminanceComponentType *y, ChromaBlueComponentType *cb, ChromaRedComponentType *cr)
	{
		RGB32fPixel rgb(
			ConvertComponentRange<RedStorageType, FloatComponent>::eval(_src.red()),
			ConvertComponentRange<GreenStorageType, FloatComponent>::eval(_src.green()),
			ConvertComponentRange<BlueStorageType, FloatComponent>::eval(_src.blue())
		);
		
		YCbCr32fPixel yuv = PixelConvertYCbCrFromRGB_Float::convert(rgb);

		if (y)   *y   = ConvertComponentRange<FloatComponent, LuminanceStorageType>::eval(yuv.luminance());
		if (cb)  *cb  = ConvertComponentRange<SignedFloatComponent, ChromaBlueStorageType>::eval(yuv.chromaBlue());
		if (cr)  *cr  = ConvertComponentRange<SignedFloatComponent, ChromaRedStorageType>::eval(yuv.chromaRed());
	}
	
	LuminanceComponentType luminance()
	{
		LuminanceComponentType y;
		convert(&y, NULL, NULL);
		return y;
	}

	ChromaBlueComponentType chromaBlue()
	{
		ChromaBlueComponentType cb;
		convert(NULL, &cb, NULL);
		return cb;
	}

	ChromaRedComponentType chromaRed()
	{
		ChromaRedComponentType cr;
		convert(NULL, NULL, &cr);
		return cr;
	}
	
private:
	const SRC_PIXELTYPE &_src;
};


//==============================================================================
// CASE: FULL sRGB to Luminance ITU601
//==============================================================================
template<typename SRC_PIXELTYPE, typename DST_PIXELTYPE>
class PixelConvertYCbCrFromRGB<SRC_PIXELTYPE, DST_PIXELTYPE, ColorSpace_sRGB, 1, 1, 1, ColorSpace_YCbCr_ITU601, 1, 0, 0>
{
	typedef typename SRC_PIXELTYPE::RedStorageType RedStorageType;
	typedef typename RedStorageType::ComponentType RedComponentType;

	typedef typename SRC_PIXELTYPE::GreenStorageType GreenStorageType;
	typedef typename GreenStorageType::ComponentType GreenComponentType;

	typedef typename SRC_PIXELTYPE::BlueStorageType BlueStorageType;
	typedef typename BlueStorageType::ComponentType BlueComponentType;

	typedef typename DST_PIXELTYPE::LuminanceStorageType LuminanceStorageType;
	typedef typename LuminanceStorageType::ComponentType LuminanceComponentType;

public:
	PixelConvertYCbCrFromRGB(const SRC_PIXELTYPE &src) : _src(src) {}

	void convert(LuminanceComponentType *y)
	{
		RGB32fPixel rgb(
			ConvertComponentRange<RedStorageType, FloatComponent>::eval(_src.red()),
			ConvertComponentRange<GreenStorageType, FloatComponent>::eval(_src.green()),
			ConvertComponentRange<BlueStorageType, FloatComponent>::eval(_src.blue())
		);
		
		YCbCr32fPixel yuv = PixelConvertYCbCrFromRGB_Float::convert(rgb);

		if (y)   *y   = ConvertComponentRange<FloatComponent, LuminanceStorageType>::eval(yuv.luminance());
	}
	
	LuminanceComponentType luminance()
	{
		LuminanceComponentType y;
		convert(&y);
		return y;
	}
	
private:
	const SRC_PIXELTYPE &_src;
};




#endif // __ITL_PIXELCONVERTER_YCBCRFROMRGB_H__



