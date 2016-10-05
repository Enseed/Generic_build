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
#ifndef __ITL_CMYKPIXEL_H__
#define __ITL_CMYKPIXEL_H__

//==============================================================================
//	FILE CMYKPixel.h
//==============================================================================
// Various definitions for the family of CMYK pixels
//------------------------------------------------------------------------------

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "CMYKPixelDefinition.h"
#include "../Storage/ComponentArray.h"
#include "../Storage/ColorSpace.h"
#include "../Storage/ComponentRange.h"

/*******
*	We defines the following Pixel formats:

	CMYK24Pixel		CMYK48Pixel		CMYK32fPixel		CMYK64fPixel
	KYMC24Pixel		KYMC48Pixel		KYMC32fPixel		KYMC64fPixel
	CMYKA32Pixel		ACMYK32Pixel		AKYMC32Pixel
	CMYKA64Pixel		KYMCA64Pixel		ACMYK64Pixel		AKYMC64Pixel	
	CMYKA32fPixel	KYMCA32fPixel	ACMYK32fPixel	AKYMC32fPixel	
	CMYKA64fPixel	KYMCA64fPixel	ACMYK64fPixel	AKYMC64fPixel

	CMYK24PlanarPixel				CMYK48PlanarPixel
	CMYK32fPlanarPixel				CMYK64fPlanarPixel
	CMYKA32PlanarPixel				CMYKA64PlanarPixel
	CMYKA32fPlanarPixel				CMYKA64fPlanarPixel

	CMYK565Pixel		KYMC565Pixel		CMYK5551Pixel	KYMC5551Pixel
	CMYK1555Pixel	KYMC1555Pixel	CMYKA5551Pixel	KYMCA5551Pixel
	ACMYK1555Pixel	AKYMC1555Pixel	CMYK332Pixel		KYMC332Pixel
*
********/

struct ComponentOrderingCyan { enum { CYAN, COMPONENT_COUNT }; };
struct ComponentOrderingMagenta { enum { MAGENTA, COMPONENT_COUNT }; };
struct ComponentOrderingYellow { enum { YELLOW, COMPONENT_COUNT }; };
struct ComponentOrderingBlack { enum { BLACK, COMPONENT_COUNT }; };

#define DECLARE_CYAN_PIXEL(_type, _name)\
typedef CyanPixelFamily<ComponentArray<_type, ComponentOrderingCyan, ComponentModel_Cyan, ColorSpace_CMYK, DefaultRange<_type> > > _name;
DECLARE_CYAN_PIXEL(unsigned char,	Cyan8Pixel);
DECLARE_CYAN_PIXEL(unsigned short, 	Cyan16Pixel);
DECLARE_CYAN_PIXEL(float,			Cyan32fPixel);
DECLARE_CYAN_PIXEL(double,			Cyan64fPixel);
#undef DECLARE_CYAN_PIXEL


#define DECLARE_MAGENTA_PIXEL(_type, _name)\
typedef MagentaPixelFamily<ComponentArray<_type, ComponentOrderingMagenta, ComponentModel_Magenta, ColorSpace_CMYK, DefaultRange<_type> > > _name;
DECLARE_MAGENTA_PIXEL(unsigned char,	Magenta8Pixel);
DECLARE_MAGENTA_PIXEL(unsigned short, 	Magenta16Pixel);
DECLARE_MAGENTA_PIXEL(float,			Magenta32fPixel);
DECLARE_MAGENTA_PIXEL(double,			Magenta64fPixel);
#undef DECLARE_MAGENTA_PIXEL

#define DECLARE_YELLOW_PIXEL(_type, _name)\
typedef YellowPixelFamily<ComponentArray<_type, ComponentOrderingYellow, ComponentModel_Yellow, ColorSpace_CMYK, DefaultRange<_type> > > _name;
DECLARE_YELLOW_PIXEL(unsigned char,		Yellow8Pixel);
DECLARE_YELLOW_PIXEL(unsigned short, 	Yellow16Pixel);
DECLARE_YELLOW_PIXEL(float,				Yellow32fPixel);
DECLARE_YELLOW_PIXEL(double,			Yellow64fPixel);
#undef DECLARE_YELLOW_PIXEL

#define DECLARE_BLACK_PIXEL(_type, _name)\
typedef BlackPixelFamily<ComponentArray<_type, ComponentOrderingBlack, ComponentModel_Black, ColorSpace_CMYK, DefaultRange<_type> > > _name;
DECLARE_BLACK_PIXEL(unsigned char,		Black8Pixel);
DECLARE_BLACK_PIXEL(unsigned short, 	Black16Pixel);
DECLARE_BLACK_PIXEL(float,				Black32fPixel);
DECLARE_BLACK_PIXEL(double,				Black64fPixel);
#undef DECLARE_BLACK_PIXEL


typedef BitStorage<1, ComponentOrderingBlack, ComponentModel_Black, ColorSpace_CMYK, BitRange<1> > BlackBitStorage1;
typedef BlackPixelBitPacketFamily<BlackBitStorage1> Black1Pixel;

//typedef BitStorage<1, ComponentOrderingBlack, ComponentModel_Black, ColorSpace_CMYK, BitRange<1> > BlackBitStorage2;
//typedef BlackPixelBitPacketFamily<BlackBitStorage2> Black2Pixel;

typedef BitStorage<4, ComponentOrderingBlack, ComponentModel_Black, ColorSpace_CMYK, BitRange<4> > BlackBitStorage4;
typedef BlackPixelBitPacketFamily<BlackBitStorage4> Black4Pixel;



//==============================================================================
//	PACKED TYPES
//==============================================================================
struct ComponentOrderingCMYK { enum { CYAN, MAGENTA, YELLOW, BLACK, COMPONENT_COUNT }; };
struct ComponentOrderingKYMC { enum { BLACK, YELLOW, MAGENTA, CYAN, COMPONENT_COUNT }; };

struct ComponentOrderingCMYKA { enum { CYAN, MAGENTA, YELLOW, BLACK, ALPHA, COMPONENT_COUNT }; };
struct ComponentOrderingKYMCA { enum { BLACK, YELLOW, MAGENTA, CYAN, ALPHA, COMPONENT_COUNT }; };

struct ComponentOrderingACMYK { enum { ALPHA, CYAN, MAGENTA, YELLOW, BLACK, COMPONENT_COUNT }; };
struct ComponentOrderingAKYMC { enum { BLACK, ALPHA, YELLOW, MAGENTA, CYAN, COMPONENT_COUNT }; };


#define DECLARE_CMYK_PIXEL(_type, _ordering, _name)\
typedef CMYKPixelFamily<ComponentArray<_type, _ordering, ComponentModel_CMYK, ColorSpace_CMYK, DefaultRange<_type> > > _name;

DECLARE_CMYK_PIXEL(unsigned char, ComponentOrderingCMYK,	CMYK32Pixel);
DECLARE_CMYK_PIXEL(unsigned char, ComponentOrderingKYMC,	KYMC32Pixel);

DECLARE_CMYK_PIXEL(unsigned short, ComponentOrderingCMYK, CMYK64Pixel);
DECLARE_CMYK_PIXEL(unsigned short, ComponentOrderingKYMC, KYMC64Pixel);

DECLARE_CMYK_PIXEL(float, ComponentOrderingCMYK,			CMYK32fPixel);
DECLARE_CMYK_PIXEL(float, ComponentOrderingKYMC,			KYMC32fPixel);

DECLARE_CMYK_PIXEL(double, ComponentOrderingCMYK,			CMYK64fPixel);
DECLARE_CMYK_PIXEL(double, ComponentOrderingKYMC,			KYMC64fPixel);

#undef DECLARE_CMYK_PIXEL
/*

#define DECLARE_CMYKA_PIXEL(_type, _ordering, _name)\
typedef CMYKAPixelFamily<ComponentArray<_type, _ordering, ComponentModel_CMYKA, ColorSpace_CMYK, DefaultRange<_type> > > _name; \
typedef ConstCMYKAPixelFamily<ComponentArray<_type, _ordering, ComponentModel_CMYKA, ColorSpace_CMYK, DefaultRange<_type> > > Const##_name;

DECLARE_CMYKA_PIXEL(unsigned char, ComponentOrderingCMYKA,	CMYKA32Pixel);
DECLARE_CMYKA_PIXEL(unsigned char, ComponentOrderingKYMCA,	KYMCA32Pixel);
DECLARE_CMYKA_PIXEL(unsigned char, ComponentOrderingACMYK,	ACMYK32Pixel);
DECLARE_CMYKA_PIXEL(unsigned char, ComponentOrderingAKYMC,	AKYMC32Pixel);

DECLARE_CMYKA_PIXEL(unsigned short, ComponentOrderingCMYKA,	CMYKA64Pixel);
DECLARE_CMYKA_PIXEL(unsigned short, ComponentOrderingKYMCA,	KYMCA64Pixel);
DECLARE_CMYKA_PIXEL(unsigned short, ComponentOrderingACMYK,	ACMYK64Pixel);
DECLARE_CMYKA_PIXEL(unsigned short, ComponentOrderingAKYMC,	AKYMC64Pixel);

DECLARE_CMYKA_PIXEL(float, ComponentOrderingCMYKA,			CMYKA32fPixel);
DECLARE_CMYKA_PIXEL(float, ComponentOrderingKYMCA,			KYMCA32fPixel);
DECLARE_CMYKA_PIXEL(float, ComponentOrderingACMYK,			ACMYK32fPixel);
DECLARE_CMYKA_PIXEL(float, ComponentOrderingAKYMC,			AKYMC32fPixel);

DECLARE_CMYKA_PIXEL(double, ComponentOrderingCMYKA,			CMYKA64fPixel);
DECLARE_CMYKA_PIXEL(double, ComponentOrderingKYMCA,			KYMCA64fPixel);
DECLARE_CMYKA_PIXEL(double, ComponentOrderingACMYK,			ACMYK64fPixel);
DECLARE_CMYKA_PIXEL(double, ComponentOrderingAKYMC,			AKYMC64fPixel);

#undef DECLARE_CMYKA_PIXEL
*/
/*#include "CMYKPixelRefDefinition.h"
//==============================================================================
//	PLANAR TYPES
//==============================================================================
struct ComponentOrderingCyan		{ enum { CYAN, COMPONENT_COUNT }; };
struct ComponentOrderingMagenta	{ enum { MAGENTA, COMPONENT_COUNT }; };
struct ComponentOrderingYellow	{ enum { YELLOW, COMPONENT_COUNT }; };


#define DECLARE_CMYK_PLANAR_PIXEL(_type, _name)\
typedef CMYKPixelPlanarFamily<ComponentArrayRef<_type, ComponentOrderingCyan, ComponentModel_CMYK, ColorSpace_CMYK, DefaultRange<_type> >, ComponentArrayRef<_type, ComponentOrderingMagenta, ComponentModel_CMYK, ColorSpace_CMYK, DefaultRange<_type> >, ComponentArrayRef<_type, ComponentOrderingYellow, ComponentModel_CMYK, ColorSpace_CMYK, DefaultRange<_type> > > _name;\
typedef CMYKPixelPlanarFamily<ConstComponentArrayRef<_type, ComponentOrderingCyan, ComponentModel_CMYK, ColorSpace_CMYK, DefaultRange<_type> >, ConstComponentArrayRef<_type, ComponentOrderingMagenta, ComponentModel_CMYK, ColorSpace_CMYK, DefaultRange<_type> >, ConstComponentArrayRef<_type, ComponentOrderingYellow, ComponentModel_CMYK, ColorSpace_CMYK, DefaultRange<_type> > > Const##_name;

DECLARE_CMYK_PLANAR_PIXEL(unsigned char,		CMYK24PlanarPixel);
DECLARE_CMYK_PLANAR_PIXEL(unsigned short,	CMYK48PlanarPixel);
DECLARE_CMYK_PLANAR_PIXEL(float,				CMYK32fPlanarPixel);
DECLARE_CMYK_PLANAR_PIXEL(double,			CMYK64fPlanarPixel);
#undef DECLARE_CMYK_PLANAR_PIXEL


struct ComponentOrderingAlpha { enum { ALPHA, COMPONENT_COUNT }; };


#define DECLARE_CMYKA_PLANAR_PIXEL(_type, _name)\
typedef CMYKAPixelPlanarFamily<ComponentArrayRef<_type, ComponentOrderingCyan, ComponentModel_CMYKA, ColorSpace_CMYK, DefaultRange<_type> >, ComponentArrayRef<_type, ComponentOrderingMagenta, ComponentModel_CMYKA, ColorSpace_CMYK, DefaultRange<_type> >,	ComponentArrayRef<_type, ComponentOrderingYellow, ComponentModel_CMYKA, ColorSpace_CMYK, DefaultRange<_type> >,	ComponentArrayRef<_type, ComponentOrderingAlpha, ComponentModel_CMYKA, ColorSpace_CMYK, DefaultRange<_type> > > _name;\
typedef CMYKAPixelPlanarFamily<ConstComponentArrayRef<_type, ComponentOrderingCyan, ComponentModel_CMYKA, ColorSpace_CMYK, DefaultRange<_type> >, ConstComponentArrayRef<_type, ComponentOrderingMagenta, ComponentModel_CMYKA, ColorSpace_CMYK, DefaultRange<_type> >, ConstComponentArrayRef<_type, ComponentOrderingYellow, ComponentModel_CMYKA, ColorSpace_CMYK, DefaultRange<_type> >, ConstComponentArrayRef<_type, ComponentOrderingAlpha, ComponentModel_CMYKA, ColorSpace_CMYK, DefaultRange<_type> > > Const##_name;


DECLARE_CMYKA_PLANAR_PIXEL(unsigned char,	CMYKA32PlanarPixel);
DECLARE_CMYKA_PLANAR_PIXEL(unsigned short,	CMYKA64PlanarPixel);
DECLARE_CMYKA_PLANAR_PIXEL(float,			CMYKA32fPlanarPixel);
DECLARE_CMYKA_PLANAR_PIXEL(double,			CMYKA64fPlanarPixel);
#undef DECLARE_CMYKA_PLANAR_PIXEL
*/

//==============================================================================
//	16 BIT SUPPORT
//==============================================================================
/*#include "ComponentCMYKPacked.h"
#include "BitIO.h"

typedef CMYKPixelFamily<ComponentCMYKPacked<unsigned short, unsigned char, 0, 5, 0, 6, 0, 5, BitIO, ComponentOrderingCMYK, ColorSpace_CMYK> > CMYK565Pixel;
typedef CMYKPixelFamily<ComponentCMYKPacked<unsigned short, unsigned char, 0, 5, 0, 6, 0, 5, BitIO, ComponentOrderingKYMC, ColorSpace_CMYK> > KYMC565Pixel;

typedef CMYKPixelFamily<ComponentCMYKPacked<unsigned short, unsigned char, 0, 5, 0, 5, 0, 5, BitIO, ComponentOrderingCMYK, ColorSpace_CMYK> > CMYK5551Pixel;
typedef CMYKPixelFamily<ComponentCMYKPacked<unsigned short, unsigned char, 0, 5, 0, 5, 0, 5, BitIO, ComponentOrderingKYMC, ColorSpace_CMYK> > KYMC5551Pixel;

typedef CMYKPixelFamily<ComponentCMYKPacked<unsigned short, unsigned char, 1, 5, 0, 5, 0, 5, BitIO, ComponentOrderingCMYK, ColorSpace_CMYK> > CMYK1555Pixel;
typedef CMYKPixelFamily<ComponentCMYKPacked<unsigned short, unsigned char, 1, 5, 0, 5, 0, 5, BitIO, ComponentOrderingKYMC, ColorSpace_CMYK> > KYMC1555Pixel;

typedef CMYKAPixelFamily<ComponentCMYKAPacked<unsigned short, unsigned char, 0, 5, 0, 5, 0, 5, 0, 1, BitIO, ComponentOrderingCMYKA, ColorSpace_CMYK> > CMYKA5551Pixel;
typedef CMYKAPixelFamily<ComponentCMYKAPacked<unsigned short, unsigned char, 0, 5, 0, 5, 0, 5, 0, 1, BitIO, ComponentOrderingKYMCA, ColorSpace_CMYK> > KYMCA5551Pixel;

typedef CMYKAPixelFamily<ComponentCMYKAPacked<unsigned short, unsigned char, 0, 1, 0, 5, 0, 5, 0, 5, BitIO, ComponentOrderingACMYK, ColorSpace_CMYK> > ACMYK1555Pixel;
typedef CMYKAPixelFamily<ComponentCMYKAPacked<unsigned short, unsigned char, 0, 1, 0, 5, 0, 5, 0, 5, BitIO, ComponentOrderingAKYMC, ColorSpace_CMYK> > AKYMC1555Pixel;

//==============================================================================
//	8 BIT SUPPORT (why not...)
//==============================================================================
typedef CMYKPixelFamily<ComponentCMYKPacked<unsigned char, unsigned char, 0, 3, 0, 3, 0, 2, BitIO, ComponentOrderingCMYK, ColorSpace_CMYK> > CMYK332Pixel;
typedef CMYKPixelFamily<ComponentCMYKPacked<unsigned char, unsigned char, 0, 3, 0, 3, 0, 2, BitIO, ComponentOrderingKYMC, ColorSpace_CMYK> > KYMC332Pixel;
*/

#endif // __ITL_CMYKPIXEL_H__


