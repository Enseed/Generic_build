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
#ifndef __ITL_RGBPIXEL_H__
#define __ITL_RGBPIXEL_H__

//==============================================================================
//	FILE RGBPixel.h
//==============================================================================
// Various definitions for the family of RGB pixels
//------------------------------------------------------------------------------

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "RGBPixelDefinition.h"
#include "../Storage/ComponentArray.h"
#include "../Storage/ColorSpace.h"
#include "../Storage/ComponentRange.h"

/*******
*	We defines the following Pixel formats:

	RGB24Pixel		RGB48Pixel		RGB32fPixel		RGB64fPixel
	BGR24Pixel		BGR48Pixel		BGR32fPixel		BGR64fPixel
	RGBA32Pixel		ARGB32Pixel		ABGR32Pixel
	RGBA64Pixel		BGRA64Pixel		ARGB64Pixel		ABGR64Pixel	
	RGBA32fPixel	BGRA32fPixel	ARGB32fPixel	ABGR32fPixel	
	RGBA64fPixel	BGRA64fPixel	ARGB64fPixel	ABGR64fPixel

	RGB24PlanarPixel				RGB48PlanarPixel
	RGB32fPlanarPixel				RGB64fPlanarPixel
	RGBA32PlanarPixel				RGBA64PlanarPixel
	RGBA32fPlanarPixel				RGBA64fPlanarPixel

	RGB565Pixel		BGR565Pixel		RGB5551Pixel	BGR5551Pixel
	RGB1555Pixel	BGR1555Pixel	RGBA5551Pixel	BGRA5551Pixel
	ARGB1555Pixel	ABGR1555Pixel	RGB332Pixel		BGR332Pixel
*
********/

//==============================================================================
//	PACKED TYPES
//==============================================================================
struct ComponentOrderingRed		{ enum { RED, COMPONENT_COUNT }; };
struct ComponentOrderingGreen	{ enum { GREEN, COMPONENT_COUNT }; };
struct ComponentOrderingBlue	{ enum { BLUE, COMPONENT_COUNT }; };

struct ComponentOrderingRGB { enum { RED, GREEN, BLUE, COMPONENT_COUNT }; };
struct ComponentOrderingBGR { enum { BLUE, GREEN, RED, COMPONENT_COUNT }; };

struct ComponentOrderingRGBA { enum { RED, GREEN, BLUE, ALPHA, COMPONENT_COUNT }; };
struct ComponentOrderingBGRA { enum { BLUE, GREEN, RED, ALPHA, COMPONENT_COUNT }; };
struct ComponentOrderingBGRX { enum { BLUE, GREEN, RED, PADDING, COMPONENT_COUNT }; };

struct ComponentOrderingARGB { enum { ALPHA, RED, GREEN, BLUE, COMPONENT_COUNT }; };
struct ComponentOrderingABGR { enum { ALPHA, BLUE, GREEN, RED, COMPONENT_COUNT }; };


#define DECLARE_RED_PIXEL(_type, _name)\
typedef RedPixelFamily<ComponentArray<_type, ComponentOrderingRed, ComponentModel_Red, ColorSpace_sRGB, DefaultRange<_type> > > _name;
DECLARE_RED_PIXEL(unsigned char,	Red24Pixel);
DECLARE_RED_PIXEL(unsigned short,	Red48Pixel);
DECLARE_RED_PIXEL(float,			Red32fPixel);
DECLARE_RED_PIXEL(double,			Red64fPixel);
#undef DECLARE_RED_PIXEL

#define DECLARE_GREEN_PIXEL(_type, _name)\
typedef GreenPixelFamily<ComponentArray<_type, ComponentOrderingGreen, ComponentModel_Green, ColorSpace_sRGB, DefaultRange<_type> > > _name;
DECLARE_GREEN_PIXEL(unsigned char,	Green24Pixel);
DECLARE_GREEN_PIXEL(unsigned short,	Green48Pixel);
DECLARE_GREEN_PIXEL(float,			Green32fPixel);
DECLARE_GREEN_PIXEL(double,			Green64fPixel);
#undef DECLARE_GREEN_PIXEL

#define DECLARE_BLUE_PIXEL(_type, _name)\
typedef BluePixelFamily<ComponentArray<_type, ComponentOrderingBlue, ComponentModel_Blue, ColorSpace_sRGB, DefaultRange<_type> > > _name;
DECLARE_BLUE_PIXEL(unsigned char,	Blue24Pixel);
DECLARE_BLUE_PIXEL(unsigned short,	Blue48Pixel);
DECLARE_BLUE_PIXEL(float,			Blue32fPixel);
DECLARE_BLUE_PIXEL(double,			Blue64fPixel);
#undef DECLARE_BLUE_PIXEL


#define DECLARE_RGB_PIXEL(_type, _ordering, _name)\
typedef RGBPixelFamily<ComponentArray<_type, _ordering, ComponentModel_RGB, ColorSpace_sRGB, DefaultRange<_type> > > _name; \
typedef ConstRGBPixelFamily<ComponentArray<_type, _ordering, ComponentModel_RGB, ColorSpace_sRGB, DefaultRange<_type> > > Const##_name;

DECLARE_RGB_PIXEL(unsigned char, ComponentOrderingRGB,	RGB24Pixel);
DECLARE_RGB_PIXEL(unsigned char, ComponentOrderingBGR,	BGR24Pixel);

DECLARE_RGB_PIXEL(unsigned short, ComponentOrderingRGB, RGB48Pixel);
DECLARE_RGB_PIXEL(unsigned short, ComponentOrderingBGR, BGR48Pixel);

DECLARE_RGB_PIXEL(unsigned long, ComponentOrderingRGB, RGB96Pixel);
DECLARE_RGB_PIXEL(unsigned long, ComponentOrderingBGR, BGR96Pixel);

DECLARE_RGB_PIXEL(float, ComponentOrderingRGB,			RGB32fPixel);
DECLARE_RGB_PIXEL(float, ComponentOrderingBGR,			BGR32fPixel);

DECLARE_RGB_PIXEL(double, ComponentOrderingRGB,			RGB64fPixel);
DECLARE_RGB_PIXEL(double, ComponentOrderingBGR,			BGR64fPixel);

DECLARE_RGB_PIXEL(unsigned char, ComponentOrderingBGRX,	BGRX32Pixel);

#undef DECLARE_RGB_PIXEL


#define DECLARE_RGBA_PIXEL(_type, _ordering, _name)\
typedef RGBAPixelFamily<ComponentArray<_type, _ordering, ComponentModel_RGBA, ColorSpace_sRGB, DefaultRange<_type> > > _name; \
typedef ConstRGBAPixelFamily<ComponentArray<_type, _ordering, ComponentModel_RGBA, ColorSpace_sRGB, DefaultRange<_type> > > Const##_name;

DECLARE_RGBA_PIXEL(unsigned char, ComponentOrderingRGBA,	RGBA32Pixel);
DECLARE_RGBA_PIXEL(unsigned char, ComponentOrderingBGRA,	BGRA32Pixel);
DECLARE_RGBA_PIXEL(unsigned char, ComponentOrderingARGB,	ARGB32Pixel);
DECLARE_RGBA_PIXEL(unsigned char, ComponentOrderingABGR,	ABGR32Pixel);

DECLARE_RGBA_PIXEL(unsigned short, ComponentOrderingRGBA,	RGBA64Pixel);
DECLARE_RGBA_PIXEL(unsigned short, ComponentOrderingBGRA,	BGRA64Pixel);
DECLARE_RGBA_PIXEL(unsigned short, ComponentOrderingARGB,	ARGB64Pixel);
DECLARE_RGBA_PIXEL(unsigned short, ComponentOrderingABGR,	ABGR64Pixel);

DECLARE_RGBA_PIXEL(unsigned long, ComponentOrderingRGBA,	RGBA128Pixel);
DECLARE_RGBA_PIXEL(unsigned long, ComponentOrderingBGRA,	BGRA128Pixel);
DECLARE_RGBA_PIXEL(unsigned long, ComponentOrderingARGB,	ARGB128Pixel);
DECLARE_RGBA_PIXEL(unsigned long, ComponentOrderingABGR,	ABGR128Pixel);

DECLARE_RGBA_PIXEL(float, ComponentOrderingRGBA,			RGBA32fPixel);
DECLARE_RGBA_PIXEL(float, ComponentOrderingBGRA,			BGRA32fPixel);
DECLARE_RGBA_PIXEL(float, ComponentOrderingARGB,			ARGB32fPixel);
DECLARE_RGBA_PIXEL(float, ComponentOrderingABGR,			ABGR32fPixel);

DECLARE_RGBA_PIXEL(double, ComponentOrderingRGBA,			RGBA64fPixel);
DECLARE_RGBA_PIXEL(double, ComponentOrderingBGRA,			BGRA64fPixel);
DECLARE_RGBA_PIXEL(double, ComponentOrderingARGB,			ARGB64fPixel);
DECLARE_RGBA_PIXEL(double, ComponentOrderingABGR,			ABGR64fPixel);

#undef DECLARE_RGBA_PIXEL


#define DECLARE_RGB_PLANAR_PIXEL(_type, _name)\
typedef RGBPlanarPixel<\
	RedPixelFamily<ComponentArray<_type, ComponentOrderingRed, ComponentModel_RGB, ColorSpace_sRGB, DefaultRange<_type> > >,\
	GreenPixelFamily<ComponentArray<_type, ComponentOrderingGreen, ComponentModel_RGB, ColorSpace_sRGB, DefaultRange<_type> > >,\
	BluePixelFamily<ComponentArray<_type, ComponentOrderingBlue, ComponentModel_RGB, ColorSpace_sRGB, DefaultRange<_type> > >, ComponentModel_RGB, ColorSpace_sRGB > _name;
DECLARE_RGB_PLANAR_PIXEL(unsigned char,		RGB24PlanarPixel);
DECLARE_RGB_PLANAR_PIXEL(unsigned short,	RGB48PlanarPixel);
DECLARE_RGB_PLANAR_PIXEL(float,				RGB32fPlanarPixel);
DECLARE_RGB_PLANAR_PIXEL(double,			RGB64fPlanarPixel);
#undef DECLARE_RGB_PLANAR_PIXEL


#define DECLARE_RGBA_PLANAR_PIXEL(_type, _name)\
typedef RGBAPlanarPixel<\
	RedPixelFamily<ComponentArray<_type, ComponentOrderingRed, ComponentModel_RGB, ColorSpace_sRGB, DefaultRange<_type> > >,\
	GreenPixelFamily<ComponentArray<_type, ComponentOrderingGreen, ComponentModel_RGB, ColorSpace_sRGB, DefaultRange<_type> > >,\
	BluePixelFamily<ComponentArray<_type, ComponentOrderingBlue, ComponentModel_RGB, ColorSpace_sRGB, DefaultRange<_type> > >,\
	AlphaPixelFamily<ComponentArray<_type, ComponentOrderingBlue, ComponentModel_RGB, ColorSpace_sRGB, DefaultRange<_type> > >,\
	ComponentModel_RGB, ColorSpace_sRGB > _name;
//DECLARE_RGBA_PLANAR_PIXEL(unsigned char,	RGBA24PlanarPixel);
//DECLARE_RGBA_PLANAR_PIXEL(unsigned short,	RGBA48PlanarPixel);
//DECLARE_RGBA_PLANAR_PIXEL(float,			RGBA32fPlanarPixel);
//DECLARE_RGBA_PLANAR_PIXEL(double,			RGBA64fPlanarPixel);
#undef DECLARE_RGBA_PLANAR_PIXEL


//==============================================================================
//	16 BIT SUPPORT
//==============================================================================
#include "ComponentRGBPacked.h"
#include "../Utils/BitIO.h"

typedef RGBPixelFamily<ComponentRGBPacked<unsigned short, unsigned char, 0, 5, 0, 6, 0, 5, BitIO, ComponentOrderingRGB, ColorSpace_sRGB> > RGB565Pixel;
typedef RGBPixelFamily<ComponentRGBPacked<unsigned short, unsigned char, 0, 5, 0, 6, 0, 5, BitIO, ComponentOrderingBGR, ColorSpace_sRGB> > BGR565Pixel;

typedef RGBPixelFamily<ComponentRGBPacked<unsigned short, unsigned char, 0, 5, 0, 5, 0, 5, BitIO, ComponentOrderingRGB, ColorSpace_sRGB> > RGB5551Pixel;
typedef RGBPixelFamily<ComponentRGBPacked<unsigned short, unsigned char, 0, 5, 0, 5, 0, 5, BitIO, ComponentOrderingBGR, ColorSpace_sRGB> > BGR5551Pixel;

typedef RGBPixelFamily<ComponentRGBPacked<unsigned short, unsigned char, 1, 5, 0, 5, 0, 5, BitIO, ComponentOrderingRGB, ColorSpace_sRGB> > RGB1555Pixel;
typedef RGBPixelFamily<ComponentRGBPacked<unsigned short, unsigned char, 1, 5, 0, 5, 0, 5, BitIO, ComponentOrderingBGR, ColorSpace_sRGB> > BGR1555Pixel;

typedef RGBAPixelFamily<ComponentRGBAPacked<unsigned short, unsigned char, 0, 5, 0, 5, 0, 5, 0, 1, BitIO, ComponentOrderingRGBA, ColorSpace_sRGB> > RGBA5551Pixel;
typedef RGBAPixelFamily<ComponentRGBAPacked<unsigned short, unsigned char, 0, 5, 0, 5, 0, 5, 0, 1, BitIO, ComponentOrderingBGRA, ColorSpace_sRGB> > BGRA5551Pixel;

typedef RGBAPixelFamily<ComponentRGBAPacked<unsigned short, unsigned char, 0, 1, 0, 5, 0, 5, 0, 5, BitIO, ComponentOrderingARGB, ColorSpace_sRGB> > ARGB1555Pixel;
typedef RGBAPixelFamily<ComponentRGBAPacked<unsigned short, unsigned char, 0, 1, 0, 5, 0, 5, 0, 5, BitIO, ComponentOrderingABGR, ColorSpace_sRGB> > ABGR1555Pixel;

//==============================================================================
//	8 BIT SUPPORT (why not...)
//==============================================================================
typedef RGBPixelFamily<ComponentRGBPacked<unsigned char, unsigned char, 0, 3, 0, 3, 0, 2, BitIO, ComponentOrderingRGB, ColorSpace_sRGB> > RGB332Pixel;
typedef RGBPixelFamily<ComponentRGBPacked<unsigned char, unsigned char, 0, 3, 0, 3, 0, 2, BitIO, ComponentOrderingBGR, ColorSpace_sRGB> > BGR332Pixel;


#endif // __ITL_RGBPIXEL_H__


