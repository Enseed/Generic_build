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
#ifndef __ITL_PIXELCONVERTER_ALPHA_H__
#define __ITL_PIXELCONVERTER_ALPHA_H__

//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================
#include "Alpha.declare.h"
#include "Range.h"
#include "../Storage/ComponentModel.h"
#ifndef _WIN32
#include <tr1/type_traits>
#else
#include <type_traits> 
#endif

//==============================================================================
// CASE: The source pixel has an alpha component
//==============================================================================
template<typename SRC_PIXELTYPE, typename DST_PIXELTYPE, typename SRC_COMPONENTMODEL, typename SRC_COLORSPACE, typename DST_COMPONENTMODEL, typename DST_COLORSPACE>
struct PixelConvertExtractAlpha<SRC_PIXELTYPE, DST_PIXELTYPE, SRC_COMPONENTMODEL, SRC_COLORSPACE, DST_COMPONENTMODEL, DST_COLORSPACE, true>
{
	typedef typename DST_PIXELTYPE::AlphaStorageType DstStorage;
	typedef typename SRC_PIXELTYPE::AlphaStorageType SrcStorage;
	static typename DstStorage::ComponentType eval(const SRC_PIXELTYPE &src)
	{	return ConvertComponentRange<SrcStorage, DstStorage>::eval(src.alpha()); }
};

//==============================================================================
// CASE: The source pixel does not have an alpha component (return max())
//==============================================================================
template<typename SRC_PIXELTYPE, typename DST_PIXELTYPE, typename SRC_COMPONENTMODEL, typename SRC_COLORSPACE, typename DST_COMPONENTMODEL, typename DST_COLORSPACE>
struct PixelConvertExtractAlpha<SRC_PIXELTYPE, DST_PIXELTYPE, SRC_COMPONENTMODEL, SRC_COLORSPACE, DST_COMPONENTMODEL, DST_COLORSPACE, false>
{
	typedef typename DST_PIXELTYPE::AlphaStorageType DstStorage;

	static typename DstStorage::ComponentType eval(const SRC_PIXELTYPE &src)
	{	return DstStorage::max(); }
};




#endif // __ITL_PIXELCONVERTER_ALPHA_H__



