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
#ifndef __ITL_PIXELCONVERTER_MAGENTA_DECLARE_H__
#define __ITL_PIXELCONVERTER_MAGENTA_DECLARE_H__

//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================
#include "Range.h"

template<
	typename SRC_PIXELTYPE, 
	typename DST_PIXELTYPE,
	typename SRC_COMPONENTMODEL=typename SRC_PIXELTYPE::ComponentModel, 
	typename SRC_COLORSPACE=typename SRC_PIXELTYPE::ColorSpace, 
	typename DST_COMPONENTMODEL=typename DST_PIXELTYPE::ComponentModel, 
	typename DST_COLORSPACE=typename DST_PIXELTYPE::ColorSpace, 
	int HASCOMPONENT=std::tr1::is_base_of<ComponentModel_Magenta, typename SRC_PIXELTYPE::ComponentModel>::value >
struct PixelConvertExtractMagenta;



#endif // __ITL_PIXELCONVERTER_MAGENTA_DECLARE_H__



