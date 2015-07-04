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
#ifndef __ITL_PIXELCONVERTER_BLUE_H__
#define __ITL_PIXELCONVERTER_BLUE_H__

//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================
#include "Blue.declare.h"
#include "Range.h"
#include "../Storage/ComponentModel.h"
#include "../Storage/ColorSpace.h"

#ifndef _WIN32
#include <tr1/type_traits>
#else
#include <type_traits> 
#endif


//==============================================================================
// CASE: Same color space and source has the component
//==============================================================================
template<typename SRC_PIXELTYPE, typename DST_PIXELTYPE, typename SRC_COMPONENTMODEL, typename DST_COMPONENTMODEL, typename SAME_COLORSPACE>
struct PixelConvertExtractBlue<SRC_PIXELTYPE, DST_PIXELTYPE, SRC_COMPONENTMODEL, SAME_COLORSPACE, DST_COMPONENTMODEL, SAME_COLORSPACE, true>
{
	typedef typename SRC_PIXELTYPE::BlueStorageType SrcStorage;
	typedef typename DST_PIXELTYPE::BlueStorageType DstStorage;
	
	static typename DstStorage::ComponentType eval(const SRC_PIXELTYPE &src)
	{	return ConvertComponentRange<SrcStorage, DstStorage>::eval(src.blue()); }
};

#include "RGBFromYCbCr.h"
//==============================================================================
// CASE: from ColorSpace_YCbCr_ITU601
//==============================================================================
template<typename SRC_PIXELTYPE, typename DST_PIXELTYPE, typename SRC_COMPONENTMODEL, typename DST_COMPONENTMODEL, typename DST_COLORSPACE>
struct PixelConvertExtractBlue<SRC_PIXELTYPE, DST_PIXELTYPE, SRC_COMPONENTMODEL, ColorSpace_YCbCr_ITU601, DST_COMPONENTMODEL, DST_COLORSPACE, false>
{
	typedef typename DST_PIXELTYPE::BlueStorageType DstStorage;
	
	static typename DstStorage::ComponentType eval(const SRC_PIXELTYPE &src)
	{	return PixelConvertRGBFromYCbCr<SRC_PIXELTYPE, DST_PIXELTYPE>(src).blue(); }
};


#include "RGBFromCMYK.h"
//==============================================================================
// CASE: from ColorSpace_CMYK
//==============================================================================
template<typename SRC_PIXELTYPE, typename DST_PIXELTYPE, typename SRC_COMPONENTMODEL, typename DST_COMPONENTMODEL, typename DST_COLORSPACE>
struct PixelConvertExtractBlue<SRC_PIXELTYPE, DST_PIXELTYPE, SRC_COMPONENTMODEL, ColorSpace_CMYK, DST_COMPONENTMODEL, DST_COLORSPACE, false>
{
	typedef typename DST_PIXELTYPE::BlueStorageType DstStorage;
	
	static typename DstStorage::ComponentType eval(const SRC_PIXELTYPE &src)
	{	return PixelConvertRGBFromCMYK<SRC_PIXELTYPE, DST_PIXELTYPE>(src).blue(); }
};


#endif // __ITL_PIXELCONVERTER_BLUE_H__



