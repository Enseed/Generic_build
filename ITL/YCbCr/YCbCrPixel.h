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
#ifndef __ITL_YCBCRPIXEL_H__
#define __ITL_YCBCRPIXEL_H__

//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================
#include "YCbCrPixelDefinition.h"
#include "../Storage/PixelManipulation.h"
#include "../Storage/ComponentArray.h"
#include "../Storage/ColorSpace.h"
#include "../Storage/ComponentRange.h"
#include "YCbCrOrdering.h"
#include "../Storage/ComponentSpecification.h"


//==============================================================================
// YCbCr Pixel declarations
//==============================================================================
#define DECLARE_YUVA_PIXEL(_type, _ordering, _name)\
typedef YCbCrAPixelFamily<ComponentArray<_type, _ordering, ComponentModel_YCbCrA, ColorSpace_YCbCr_ITU601, DefaultRange<_type> >, ComponentSpecification<_type,DefaultRange<_type> >, ComponentSpecification<_type,DefaultRange<_type> >, ComponentSpecification<_type,DefaultRange<_type> >, ComponentSpecification<_type,DefaultRange<_type> >  > _name; \
typedef ConstYCbCrAPixelFamily<ComponentArray<_type, _ordering, ComponentModel_YCbCrA, ColorSpace_YCbCr_ITU601, DefaultRange<_type> >, ComponentSpecification<_type,DefaultRange<_type> >, ComponentSpecification<_type,DefaultRange<_type> >, ComponentSpecification<_type,DefaultRange<_type> >, ComponentSpecification<_type,DefaultRange<_type> > > Const##_name;

DECLARE_YUVA_PIXEL(unsigned char, ComponentOrderingYCbCrA,	YCbCrA32Pixel);
DECLARE_YUVA_PIXEL(unsigned char, ComponentOrderingCrCbYA,	CrCbYA32Pixel);
DECLARE_YUVA_PIXEL(unsigned char, ComponentOrderingCbYCrA,	CbYCrA32Pixel);
DECLARE_YUVA_PIXEL(unsigned char, ComponentOrderingACbYCr,	ACbYCr32Pixel);

DECLARE_YUVA_PIXEL(unsigned short, ComponentOrderingYCbCrA, YCbCrA64Pixel);
DECLARE_YUVA_PIXEL(unsigned short, ComponentOrderingCrCbYA, CrCbYA64Pixel);

DECLARE_YUVA_PIXEL(float, ComponentOrderingYCbCrA,			YCbCrA32fPixel);
DECLARE_YUVA_PIXEL(float, ComponentOrderingCrCbYA,			CrCbYA32fPixel);

DECLARE_YUVA_PIXEL(double, ComponentOrderingYCbCrA,			YCbCrA64fPixel);
DECLARE_YUVA_PIXEL(double, ComponentOrderingCrCbYA,			CrCbYA64fPixel);

DECLARE_YUVA_PIXEL(unsigned char, ComponentOrderingAYCbCr,	AYCbCr32Pixel);
DECLARE_YUVA_PIXEL(unsigned char, ComponentOrderingACrCbY,	ACrCbY32Pixel);

DECLARE_YUVA_PIXEL(unsigned short, ComponentOrderingAYCbCr, AYCbCr64Pixel);
DECLARE_YUVA_PIXEL(unsigned short, ComponentOrderingACrCbY, ACrCbY64Pixel);

DECLARE_YUVA_PIXEL(float, ComponentOrderingAYCbCr,			AYCbCr32fPixel);
DECLARE_YUVA_PIXEL(float, ComponentOrderingACrCbY,			ACrCbY32fPixel);

DECLARE_YUVA_PIXEL(double, ComponentOrderingAYCbCr,			AYCbCr64fPixel);
DECLARE_YUVA_PIXEL(double, ComponentOrderingACrCbY,			ACrCbY64fPixel);

#undef DECLARE_YUVA_PIXEL



#define DECLARE_YUVA_VIDEO_PIXEL(_type, _ordering, _name)\
typedef YCbCrAPixelFamily<ComponentArray<_type, _ordering, ComponentModel_YCbCrA, ColorSpace_YCbCr_ITU601, DefaultRange<_type> >, ComponentSpecification<_type, DefaultRange<_type> >, ComponentSpecification<_type, DefaultRange<_type> >, ComponentSpecification<_type, DefaultRange<_type> >, ComponentSpecification<_type, DefaultRange<_type> > > _name; \
typedef ConstYCbCrAPixelFamily<ComponentArray<_type, _ordering, ComponentModel_YCbCrA, ColorSpace_YCbCr_ITU601, DefaultRange<_type> >, ComponentSpecification<_type, DefaultRange<_type> >, ComponentSpecification<_type, DefaultRange<_type> >, ComponentSpecification<_type, DefaultRange<_type> >, ComponentSpecification<_type, DefaultRange<_type> > > Const##_name;

DECLARE_YUVA_VIDEO_PIXEL(unsigned char, ComponentOrderingYCbCrA,	YCbCrAVideo32Pixel);
DECLARE_YUVA_VIDEO_PIXEL(unsigned char, ComponentOrderingCrCbYA,	CrCbYAVideo32Pixel);
DECLARE_YUVA_VIDEO_PIXEL(unsigned char, ComponentOrderingCbYCrA,	CbYCrAVideo32Pixel);
DECLARE_YUVA_VIDEO_PIXEL(unsigned char, ComponentOrderingACbYCr,	ACbYCrVideo32Pixel);

DECLARE_YUVA_VIDEO_PIXEL(unsigned short, ComponentOrderingYCbCrA, YCbCrAVideo64Pixel);
DECLARE_YUVA_VIDEO_PIXEL(unsigned short, ComponentOrderingCrCbYA, CrCbYAVideo64Pixel);

DECLARE_YUVA_VIDEO_PIXEL(float, ComponentOrderingYCbCrA,			YCbCrAVideo32fPixel);
DECLARE_YUVA_VIDEO_PIXEL(float, ComponentOrderingCrCbYA,			CrCbYAVideo32fPixel);

DECLARE_YUVA_VIDEO_PIXEL(double, ComponentOrderingYCbCrA,			YCbCrAVideo64fPixel);
DECLARE_YUVA_VIDEO_PIXEL(double, ComponentOrderingCrCbYA,			CrCbYAVideo64fPixel);

DECLARE_YUVA_VIDEO_PIXEL(unsigned char, ComponentOrderingAYCbCr,	AYCbCrVideo32Pixel);
DECLARE_YUVA_VIDEO_PIXEL(unsigned char, ComponentOrderingACrCbY,	ACrCbYVideo32Pixel);

DECLARE_YUVA_VIDEO_PIXEL(unsigned short, ComponentOrderingAYCbCr, AYCbCrVideo64Pixel);
DECLARE_YUVA_VIDEO_PIXEL(unsigned short, ComponentOrderingACrCbY, ACrCbYVideo64Pixel);

DECLARE_YUVA_VIDEO_PIXEL(float, ComponentOrderingAYCbCr,			AYCbCrVideo32fPixel);
DECLARE_YUVA_VIDEO_PIXEL(float, ComponentOrderingACrCbY,			ACrCbYVideo32fPixel);

DECLARE_YUVA_VIDEO_PIXEL(double, ComponentOrderingAYCbCr,			AYCbCrVideo64fPixel);
DECLARE_YUVA_VIDEO_PIXEL(double, ComponentOrderingACrCbY,			ACrCbYVideo64fPixel);

#undef DECLARE_YUVA_PIXEL



//==============================================================================
// YCbCr Pixel declarations
//==============================================================================
#define DECLARE_YUV_PIXEL(_type, _ordering, _name)\
typedef YCbCrPixelFamily<ComponentArray<_type, _ordering, ComponentModel_YCbCr, ColorSpace_YCbCr_ITU601, DefaultRange<_type> > > _name; \
typedef ConstYCbCrPixelFamily<ComponentArray<_type, _ordering, ComponentModel_YCbCr, ColorSpace_YCbCr_ITU601, DefaultRange<_type> > > Const##_name;

DECLARE_YUV_PIXEL(unsigned char, ComponentOrderingYCbCr,	YCbCr24Pixel);
DECLARE_YUV_PIXEL(unsigned char, ComponentOrderingCrCbY,	CrCbY24Pixel);

DECLARE_YUV_PIXEL(unsigned short, ComponentOrderingYCbCr, YCbCr48Pixel);
DECLARE_YUV_PIXEL(unsigned short, ComponentOrderingCrCbY, CrCbY48Pixel);

DECLARE_YUV_PIXEL(float, ComponentOrderingYCbCr,			YCbCr32fPixel);
DECLARE_YUV_PIXEL(float, ComponentOrderingCrCbY,			CrCbY32fPixel);

DECLARE_YUV_PIXEL(double, ComponentOrderingYCbCr,			YCbCr64fPixel);
DECLARE_YUV_PIXEL(double, ComponentOrderingCrCbY,			CrCbY64fPixel);

#undef DECLARE_YUV_PIXEL


//==============================================================================
//	PLANAR TYPES
//==============================================================================
#define DECLARE_YUV_PLANAR_PIXEL(_type, _name)\
typedef YCbCrPlanarPixel<\
	LuminancePixelFamily<ComponentArray<_type, ComponentOrderingY, ComponentModel_YCbCr, ColorSpace_YCbCr_ITU601, DefaultRange<_type> > >,\
	ChromaBluePixelFamily<ComponentArray<_type, ComponentOrderingCb, ComponentModel_YCbCr, ColorSpace_YCbCr_ITU601, DefaultRange<_type> > >,\
	ChromaRedPixelFamily<ComponentArray<_type, ComponentOrderingCr, ComponentModel_YCbCr, ColorSpace_YCbCr_ITU601, DefaultRange<_type> > >, ComponentModel_YCbCr, ColorSpace_YCbCr_ITU601 > _name;
DECLARE_YUV_PLANAR_PIXEL(unsigned char,		YCbCr24PlanarPixel);
DECLARE_YUV_PLANAR_PIXEL(unsigned short,	YCbCr48PlanarPixel);
DECLARE_YUV_PLANAR_PIXEL(float,				YCbCr32fPlanarPixel);
DECLARE_YUV_PLANAR_PIXEL(double,			YCbCr64fPlanarPixel);
#undef DECLARE_YUV_PLANAR_PIXEL


//==============================================================================
//	Luminance only
//==============================================================================
#define DECLARE_Y_PIXEL(_type, _name)\
typedef LuminancePixelFamily<ComponentArray<_type, ComponentOrderingY, ComponentModel_Luminance, ColorSpace_YCbCr_ITU601, DefaultRange<_type> > > _name; \
typedef ConstLuminancePixelFamily<ComponentArray<_type, ComponentOrderingY, ComponentModel_Luminance, ColorSpace_YCbCr_ITU601, DefaultRange<_type> > > Const##_name;

DECLARE_Y_PIXEL(unsigned char,		Lum8Pixel);
DECLARE_Y_PIXEL(unsigned short,		Lum16Pixel);
DECLARE_Y_PIXEL(float,		Lum32fPixel);
DECLARE_Y_PIXEL(double,		Lum64fPixel);

#define DECLARE_YA_PIXEL(_type, _name)\
typedef YAPixelFamily<ComponentArray<_type, ComponentOrderingYA, ComponentModel_YA, ColorSpace_YCbCr_ITU601, DefaultRange<_type> >, ComponentSpecification<_type, DefaultRange<_type> >, ComponentSpecification<_type, DefaultRange<_type> > > _name; \
typedef ConstYAPixelFamily<ComponentArray<_type, ComponentOrderingYA, ComponentModel_YA, ColorSpace_YCbCr_ITU601, DefaultRange<_type> >, ComponentSpecification<_type, DefaultRange<_type> >, ComponentSpecification<_type, DefaultRange<_type> > > Const##_name;
DECLARE_YA_PIXEL(unsigned char,		LA8Pixel);
DECLARE_YA_PIXEL(unsigned short,	LA16Pixel);
DECLARE_YA_PIXEL(float,				LA32fPixel);
DECLARE_YA_PIXEL(double,			LA64fPixel);
#undef DECLARE_Y_PIXEL




#endif // __ITL_YCBCRPIXEL_H__


