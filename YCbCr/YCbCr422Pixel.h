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
#ifndef __ITL_YCBCR422PIXEL_H__
#define __ITL_YCBCR422PIXEL_H__

//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================
#include "YCbCr422PixelDefinition.h"
#include "YCbCr422PixelRefDefinition.h"
#include "../Storage/ComponentArray.h"
#include "../Storage/PixelManipulation.h"
#include "../Storage/ColorSpace.h"
#include "../Storage/ComponentRange.h"
#include "YCbCrOrdering.h"



#define DECLARE_YCBCR422_PIXEL(_type, _ordering, _name)\
typedef ComponentArray<_type, _ordering, ComponentModel_YCbCr, ColorSpace_YCbCr_ITU601, DefaultRange<_type> > _ComponentArray_##_name;\
typedef ConstYCbCr422PixelFamily<_ComponentArray_##_name, PixelManipulation, YCbCr422LuminanceEven<_ComponentArray_##_name, PixelManipulation> > _ComponentArray_##_name##_Even;\
typedef ConstYCbCr422PixelFamily<_ComponentArray_##_name, PixelManipulation, YCbCr422LuminanceOdd<_ComponentArray_##_name, PixelManipulation> > _ComponentArray_##_name##_Odd;\
typedef YCbCr422PixelPacket<_ComponentArray_##_name##_Even, _ComponentArray_##_name##_Odd> _name;


/*
DECLARE_YCBCR422_PIXEL(unsigned char, ComponentOrderingY0CbY1Cr, YCbYCr32Pixel);
DECLARE_YCBCR422_PIXEL(unsigned char, ComponentOrderingCrY1CbY0, YCbYCrRev32Pixel);

DECLARE_YCBCR422_PIXEL(unsigned char, ComponentOrderingY0CrY1Cb, YCrYCb32Pixel);
DECLARE_YCBCR422_PIXEL(unsigned char, ComponentOrderingCbY1CrY0, YCrYCbRev32Pixel);

DECLARE_YCBCR422_PIXEL(unsigned char, ComponentOrderingCrY0CbY1, CrYCbY32Pixel);
DECLARE_YCBCR422_PIXEL(unsigned char, ComponentOrderingY1CbY0Cr, CrYCbYRev32Pixel);

DECLARE_YCBCR422_PIXEL(unsigned char, ComponentOrderingCbY0CrY1, CbYCrY32Pixel);
DECLARE_YCBCR422_PIXEL(unsigned char, ComponentOrderingY1CrY0Cb, CbYCrYRev32Pixel);
*/
#undef DECLARE_YCBCR422_PIXEL

/*

//==============================================================================
// PLANAR
//==============================================================================



#define DECLARE_YCBCR422_PLANARPIXEL(_type, _name)\
typedef ComponentArrayRef<_type, ComponentOrderingYY, ComponentModel_YCbCr, ColorSpace_YCbCr_ITU601, DefaultRange<_type> > _ComponentArray_YY_##_name;\
typedef ComponentArrayRef<_type, ComponentOrderingCb, ComponentModel_YCbCr, ColorSpace_YCbCr_ITU601, DefaultRange<_type> > _ComponentArray_Cb_##_name;\
typedef ComponentArrayRef<_type, ComponentOrderingCr, ComponentModel_YCbCr, ColorSpace_YCbCr_ITU601, DefaultRange<_type> > _ComponentArray_Cr_##_name;\
typedef ConstYCbCr422PixelPlanarFamily<_ComponentArray_YY_##_name, _ComponentArray_Cb_##_name, _ComponentArray_Cr_##_name, PixelManipulation, YCbCr422LuminanceEven<_ComponentArray_YY_##_name, PixelManipulation> > _ComponentPacket_##_name##_Even;\
typedef ConstYCbCr422PixelPlanarFamily<_ComponentArray_YY_##_name, _ComponentArray_Cb_##_name, _ComponentArray_Cr_##_name, PixelManipulation, YCbCr422LuminanceOdd<_ComponentArray_YY_##_name, PixelManipulation> > _ComponentPacket_##_name##_Odd;\
typedef YCbCr422PixelPlanarPacket<_ComponentPacket_##_name##_Even, _ComponentPacket_##_name##_Odd> _name;\
typedef ConstComponentArrayRef<_type, ComponentOrderingYY, ComponentModel_YCbCr, ColorSpace_YCbCr_ITU601, DefaultRange<_type> > _ConstComponentArray_YY_##_name;\
typedef ConstComponentArrayRef<_type, ComponentOrderingCb, ComponentModel_YCbCr, ColorSpace_YCbCr_ITU601, DefaultRange<_type> > _ConstComponentArray_Cb_##_name;\
typedef ConstComponentArrayRef<_type, ComponentOrderingCr, ComponentModel_YCbCr, ColorSpace_YCbCr_ITU601, DefaultRange<_type> > _ConstComponentArray_Cr_##_name;\
typedef ConstYCbCr422PixelPlanarFamily<_ConstComponentArray_YY_##_name, _ConstComponentArray_Cb_##_name, _ConstComponentArray_Cr_##_name, PixelManipulation, YCbCr422LuminanceEven<_ConstComponentArray_YY_##_name, PixelManipulation> > _ConstComponentPacket_##_name##_Even;\
typedef ConstYCbCr422PixelPlanarFamily<_ConstComponentArray_YY_##_name, _ConstComponentArray_Cb_##_name, _ConstComponentArray_Cr_##_name, PixelManipulation, YCbCr422LuminanceOdd<_ConstComponentArray_YY_##_name, PixelManipulation> > _ConstComponentPacket_##_name##_Odd;\
typedef ConstYCbCr422PixelPlanarPacket<_ConstComponentPacket_##_name##_Even, _ConstComponentPacket_##_name##_Odd> Const##_name;\

DECLARE_YCBCR422_PLANARPIXEL(unsigned char, YCbYCr32PixelPlanar);

#undef DECLARE_YCBCR422_PLANARPIXEL
*/


//==============================================================================
// YCbCr Pixel declarations
//==============================================================================
#define DECLARE_YCBCR422_PIXEL(_type, _ordering, _name)\
typedef YCbCr422PixelPacketFamily<ComponentArray<_type, _ordering, ComponentModel_YCbCr, ColorSpace_YCbCr_ITU601, DefaultRange<_type> > > _name; \
typedef ConstYCbCr422PixelPacketFamily<ComponentArray<_type, _ordering, ComponentModel_YCbCr, ColorSpace_YCbCr_ITU601, DefaultRange<_type> > > Const##_name;

#define DECLARE_YCBCR422HD_PIXEL(_type, _ordering, _name)\
typedef YCbCr422PixelPacketFamily<ComponentArray<_type, _ordering, ComponentModel_YCbCr, ColorSpace_YCbCr_ITU709, DefaultRange<_type> > > _name; \
typedef ConstYCbCr422PixelPacketFamily<ComponentArray<_type, _ordering, ComponentModel_YCbCr, ColorSpace_YCbCr_ITU709, DefaultRange<_type> > > Const##_name;

DECLARE_YCBCR422_PIXEL(unsigned char, ComponentOrderingY0CbY1Cr, YCbYCr32Pixel);
DECLARE_YCBCR422_PIXEL(unsigned char, ComponentOrderingCrY1CbY0, YCbYCrRev32Pixel);

DECLARE_YCBCR422_PIXEL(unsigned char, ComponentOrderingY0CrY1Cb, YCrYCb32Pixel);
DECLARE_YCBCR422_PIXEL(unsigned char, ComponentOrderingCbY1CrY0, YCrYCbRev32Pixel);

DECLARE_YCBCR422_PIXEL(unsigned char, ComponentOrderingCrY0CbY1, CrYCbY32Pixel);
DECLARE_YCBCR422_PIXEL(unsigned char, ComponentOrderingY1CbY0Cr, CrYCbYRev32Pixel);

DECLARE_YCBCR422_PIXEL(unsigned char, ComponentOrderingCbY0CrY1, CbYCrY32Pixel);
DECLARE_YCBCR422_PIXEL(unsigned char, ComponentOrderingY1CrY0Cb, CbYCrYRev32Pixel);

//DECLARE_YCBCR422HD_PIXEL(unsigned char, ComponentOrderingCbY0CrY1, CbYCrYHD32Pixel);
//DECLARE_YCBCR422HD_PIXEL(unsigned char, ComponentOrderingY1CrY0Cb, CbYCrYHDRev32Pixel);

DECLARE_YCBCR422_PIXEL(double, ComponentOrderingY0CbY1Cr, YCbYCr64fPixel);
DECLARE_YCBCR422_PIXEL(double, ComponentOrderingCrY1CbY0, YCbYCrRev64fPixel);

DECLARE_YCBCR422_PIXEL(double, ComponentOrderingY0CrY1Cb, YCrYCb64fPixel);
DECLARE_YCBCR422_PIXEL(double, ComponentOrderingCbY1CrY0, YCrYCbRev64fPixel);

DECLARE_YCBCR422_PIXEL(double, ComponentOrderingCrY0CbY1, CrYCbY64fPixel);
DECLARE_YCBCR422_PIXEL(double, ComponentOrderingY1CbY0Cr, CrYCbYRev64fPixel);

DECLARE_YCBCR422_PIXEL(double, ComponentOrderingCbY0CrY1, CbYCrY64fPixel);
DECLARE_YCBCR422_PIXEL(double, ComponentOrderingY1CrY0Cb, CbYCrYRev64fPixel);

DECLARE_YCBCR422_PIXEL(unsigned char, ComponentOrderingY0Y1CbCr, YYCbCr32Pixel);
DECLARE_YCBCR422_PIXEL(double, ComponentOrderingY0Y1CbCr, YYCbCr64fPixel);

#undef DECLARE_YCBCR422_PIXEL




#endif // __ITL_YCBCR422PIXEL_H__

