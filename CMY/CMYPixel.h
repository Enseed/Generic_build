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
#ifndef __ITL_CMYPIXEL_H__
#define __ITL_CMYPIXEL_H__

//==============================================================================
//	FILE CMYPixel.h
//==============================================================================
// Various definitions for the family of CMY pixels
//------------------------------------------------------------------------------

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "CMYPixelDefinition.h"
#include "../Storage/ComponentArray.h"
#include "../Storage/ColorSpace.h"
#include "../Storage/ComponentRange.h"

/*******
*	We defines the following Pixel formats:

	CMY24Pixel		CMY48Pixel		CMY32fPixel		CMY64fPixel
	YMC24Pixel		YMC48Pixel		YMC32fPixel		YMC64fPixel
	CMYA32Pixel		ACMY32Pixel		AYMC32Pixel
	CMYA64Pixel		YMCA64Pixel		ACMY64Pixel		AYMC64Pixel	
	CMYA32fPixel	YMCA32fPixel	ACMY32fPixel	AYMC32fPixel	
	CMYA64fPixel	YMCA64fPixel	ACMY64fPixel	AYMC64fPixel

	CMY24PlanarPixel				CMY48PlanarPixel
	CMY32fPlanarPixel				CMY64fPlanarPixel
	CMYA32PlanarPixel				CMYA64PlanarPixel
	CMYA32fPlanarPixel				CMYA64fPlanarPixel

	CMY565Pixel		YMC565Pixel		CMY5551Pixel	YMC5551Pixel
	CMY1555Pixel	YMC1555Pixel	CMYA5551Pixel	YMCA5551Pixel
	ACMY1555Pixel	AYMC1555Pixel	CMY332Pixel		YMC332Pixel
*
********/

//==============================================================================
//	PACKED TYPES
//==============================================================================
struct ComponentOrderingCMY { enum { CYAN, MAGENTA, YELLOW, COMPONENT_COUNT }; };
struct ComponentOrderingYMC { enum { YELLOW, MAGENTA, CYAN, COMPONENT_COUNT }; };

struct ComponentOrderingCMYA { enum { CYAN, MAGENTA, YELLOW, ALPHA, COMPONENT_COUNT }; };
struct ComponentOrderingYMCA { enum { YELLOW, MAGENTA, CYAN, ALPHA, COMPONENT_COUNT }; };

struct ComponentOrderingACMY { enum { ALPHA, CYAN, MAGENTA, YELLOW, COMPONENT_COUNT }; };
struct ComponentOrderingAYMC { enum { ALPHA, YELLOW, MAGENTA, CYAN, COMPONENT_COUNT }; };


#define DECLARE_CMY_PIXEL(_type, _ordering, _name)\
typedef CMYPixelFamily<ComponentArray<_type, _ordering, ComponentModel_CMY, ColorSpace_CMY, DefaultRange<_type> > > _name;

DECLARE_CMY_PIXEL(unsigned char, ComponentOrderingCMY,	CMY24Pixel);
DECLARE_CMY_PIXEL(unsigned char, ComponentOrderingYMC,	YMC24Pixel);

DECLARE_CMY_PIXEL(unsigned short, ComponentOrderingCMY, CMY48Pixel);
DECLARE_CMY_PIXEL(unsigned short, ComponentOrderingYMC, YMC48Pixel);

DECLARE_CMY_PIXEL(float, ComponentOrderingCMY,			CMY32fPixel);
DECLARE_CMY_PIXEL(float, ComponentOrderingYMC,			YMC32fPixel);

DECLARE_CMY_PIXEL(double, ComponentOrderingCMY,			CMY64fPixel);
DECLARE_CMY_PIXEL(double, ComponentOrderingYMC,			YMC64fPixel);

#undef DECLARE_CMY_PIXEL


#define DECLARE_CMYA_PIXEL(_type, _ordering, _name)\
typedef CMYAPixelFamily<ComponentArray<_type, _ordering, ComponentModel_CMYA, ColorSpace_CMY, DefaultRange<_type> > > _name; \
typedef ConstCMYAPixelFamily<ComponentArray<_type, _ordering, ComponentModel_CMYA, ColorSpace_CMY, DefaultRange<_type> > > Const##_name;

DECLARE_CMYA_PIXEL(unsigned char, ComponentOrderingCMYA,	CMYA32Pixel);
DECLARE_CMYA_PIXEL(unsigned char, ComponentOrderingYMCA,	YMCA32Pixel);
DECLARE_CMYA_PIXEL(unsigned char, ComponentOrderingACMY,	ACMY32Pixel);
DECLARE_CMYA_PIXEL(unsigned char, ComponentOrderingAYMC,	AYMC32Pixel);

DECLARE_CMYA_PIXEL(unsigned short, ComponentOrderingCMYA,	CMYA64Pixel);
DECLARE_CMYA_PIXEL(unsigned short, ComponentOrderingYMCA,	YMCA64Pixel);
DECLARE_CMYA_PIXEL(unsigned short, ComponentOrderingACMY,	ACMY64Pixel);
DECLARE_CMYA_PIXEL(unsigned short, ComponentOrderingAYMC,	AYMC64Pixel);

DECLARE_CMYA_PIXEL(float, ComponentOrderingCMYA,			CMYA32fPixel);
DECLARE_CMYA_PIXEL(float, ComponentOrderingYMCA,			YMCA32fPixel);
DECLARE_CMYA_PIXEL(float, ComponentOrderingACMY,			ACMY32fPixel);
DECLARE_CMYA_PIXEL(float, ComponentOrderingAYMC,			AYMC32fPixel);

DECLARE_CMYA_PIXEL(double, ComponentOrderingCMYA,			CMYA64fPixel);
DECLARE_CMYA_PIXEL(double, ComponentOrderingYMCA,			YMCA64fPixel);
DECLARE_CMYA_PIXEL(double, ComponentOrderingACMY,			ACMY64fPixel);
DECLARE_CMYA_PIXEL(double, ComponentOrderingAYMC,			AYMC64fPixel);

#undef DECLARE_CMYA_PIXEL

/*#include "CMYPixelRefDefinition.h"
//==============================================================================
//	PLANAR TYPES
//==============================================================================
struct ComponentOrderingCyan		{ enum { CYAN, COMPONENT_COUNT }; };
struct ComponentOrderingMagenta	{ enum { MAGENTA, COMPONENT_COUNT }; };
struct ComponentOrderingYellow	{ enum { YELLOW, COMPONENT_COUNT }; };


#define DECLARE_CMY_PLANAR_PIXEL(_type, _name)\
typedef CMYPixelPlanarFamily<ComponentArrayRef<_type, ComponentOrderingCyan, ComponentModel_CMY, ColorSpace_CMY, DefaultRange<_type> >, ComponentArrayRef<_type, ComponentOrderingMagenta, ComponentModel_CMY, ColorSpace_CMY, DefaultRange<_type> >, ComponentArrayRef<_type, ComponentOrderingYellow, ComponentModel_CMY, ColorSpace_CMY, DefaultRange<_type> > > _name;\
typedef CMYPixelPlanarFamily<ConstComponentArrayRef<_type, ComponentOrderingCyan, ComponentModel_CMY, ColorSpace_CMY, DefaultRange<_type> >, ConstComponentArrayRef<_type, ComponentOrderingMagenta, ComponentModel_CMY, ColorSpace_CMY, DefaultRange<_type> >, ConstComponentArrayRef<_type, ComponentOrderingYellow, ComponentModel_CMY, ColorSpace_CMY, DefaultRange<_type> > > Const##_name;

DECLARE_CMY_PLANAR_PIXEL(unsigned char,		CMY24PlanarPixel);
DECLARE_CMY_PLANAR_PIXEL(unsigned short,	CMY48PlanarPixel);
DECLARE_CMY_PLANAR_PIXEL(float,				CMY32fPlanarPixel);
DECLARE_CMY_PLANAR_PIXEL(double,			CMY64fPlanarPixel);
#undef DECLARE_CMY_PLANAR_PIXEL


struct ComponentOrderingAlpha { enum { ALPHA, COMPONENT_COUNT }; };


#define DECLARE_CMYA_PLANAR_PIXEL(_type, _name)\
typedef CMYAPixelPlanarFamily<ComponentArrayRef<_type, ComponentOrderingCyan, ComponentModel_CMYA, ColorSpace_CMY, DefaultRange<_type> >, ComponentArrayRef<_type, ComponentOrderingMagenta, ComponentModel_CMYA, ColorSpace_CMY, DefaultRange<_type> >,	ComponentArrayRef<_type, ComponentOrderingYellow, ComponentModel_CMYA, ColorSpace_CMY, DefaultRange<_type> >,	ComponentArrayRef<_type, ComponentOrderingAlpha, ComponentModel_CMYA, ColorSpace_CMY, DefaultRange<_type> > > _name;\
typedef CMYAPixelPlanarFamily<ConstComponentArrayRef<_type, ComponentOrderingCyan, ComponentModel_CMYA, ColorSpace_CMY, DefaultRange<_type> >, ConstComponentArrayRef<_type, ComponentOrderingMagenta, ComponentModel_CMYA, ColorSpace_CMY, DefaultRange<_type> >, ConstComponentArrayRef<_type, ComponentOrderingYellow, ComponentModel_CMYA, ColorSpace_CMY, DefaultRange<_type> >, ConstComponentArrayRef<_type, ComponentOrderingAlpha, ComponentModel_CMYA, ColorSpace_CMY, DefaultRange<_type> > > Const##_name;


DECLARE_CMYA_PLANAR_PIXEL(unsigned char,	CMYA32PlanarPixel);
DECLARE_CMYA_PLANAR_PIXEL(unsigned short,	CMYA64PlanarPixel);
DECLARE_CMYA_PLANAR_PIXEL(float,			CMYA32fPlanarPixel);
DECLARE_CMYA_PLANAR_PIXEL(double,			CMYA64fPlanarPixel);
#undef DECLARE_CMYA_PLANAR_PIXEL
*/

//==============================================================================
//	16 BIT SUPPORT
//==============================================================================
/*#include "ComponentCMYPacked.h"
#include "BitIO.h"

typedef CMYPixelFamily<ComponentCMYPacked<unsigned short, unsigned char, 0, 5, 0, 6, 0, 5, BitIO, ComponentOrderingCMY, ColorSpace_CMY> > CMY565Pixel;
typedef CMYPixelFamily<ComponentCMYPacked<unsigned short, unsigned char, 0, 5, 0, 6, 0, 5, BitIO, ComponentOrderingYMC, ColorSpace_CMY> > YMC565Pixel;

typedef CMYPixelFamily<ComponentCMYPacked<unsigned short, unsigned char, 0, 5, 0, 5, 0, 5, BitIO, ComponentOrderingCMY, ColorSpace_CMY> > CMY5551Pixel;
typedef CMYPixelFamily<ComponentCMYPacked<unsigned short, unsigned char, 0, 5, 0, 5, 0, 5, BitIO, ComponentOrderingYMC, ColorSpace_CMY> > YMC5551Pixel;

typedef CMYPixelFamily<ComponentCMYPacked<unsigned short, unsigned char, 1, 5, 0, 5, 0, 5, BitIO, ComponentOrderingCMY, ColorSpace_CMY> > CMY1555Pixel;
typedef CMYPixelFamily<ComponentCMYPacked<unsigned short, unsigned char, 1, 5, 0, 5, 0, 5, BitIO, ComponentOrderingYMC, ColorSpace_CMY> > YMC1555Pixel;

typedef CMYAPixelFamily<ComponentCMYAPacked<unsigned short, unsigned char, 0, 5, 0, 5, 0, 5, 0, 1, BitIO, ComponentOrderingCMYA, ColorSpace_CMY> > CMYA5551Pixel;
typedef CMYAPixelFamily<ComponentCMYAPacked<unsigned short, unsigned char, 0, 5, 0, 5, 0, 5, 0, 1, BitIO, ComponentOrderingYMCA, ColorSpace_CMY> > YMCA5551Pixel;

typedef CMYAPixelFamily<ComponentCMYAPacked<unsigned short, unsigned char, 0, 1, 0, 5, 0, 5, 0, 5, BitIO, ComponentOrderingACMY, ColorSpace_CMY> > ACMY1555Pixel;
typedef CMYAPixelFamily<ComponentCMYAPacked<unsigned short, unsigned char, 0, 1, 0, 5, 0, 5, 0, 5, BitIO, ComponentOrderingAYMC, ColorSpace_CMY> > AYMC1555Pixel;

//==============================================================================
//	8 BIT SUPPORT (why not...)
//==============================================================================
typedef CMYPixelFamily<ComponentCMYPacked<unsigned char, unsigned char, 0, 3, 0, 3, 0, 2, BitIO, ComponentOrderingCMY, ColorSpace_CMY> > CMY332Pixel;
typedef CMYPixelFamily<ComponentCMYPacked<unsigned char, unsigned char, 0, 3, 0, 3, 0, 2, BitIO, ComponentOrderingYMC, ColorSpace_CMY> > YMC332Pixel;
*/

#endif // __ITL_CMYPIXEL_H__


