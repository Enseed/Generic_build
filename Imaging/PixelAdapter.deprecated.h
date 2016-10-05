/*******************************************************************************
 Copyright 2007 Enseed inc.
 
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

 Author: Gaspard Petit
*******************************************************************************/
#ifndef __GENERIC_IMAGE_PIXELADAPTER__
#define __GENERIC_IMAGE_PIXELADAPTER__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "Constants.h"
#include "../Base/Types.h"

#ifdef GENERIC_NAMESPACE
namespace GENERIC_NAMESPACE {
#endif

//==============================================================================
// MACRO PIXEL_ADAPTER 
//==============================================================================
#define CONST_PIXEL_ADAPTER_CONSTRUCTOR(_type)\
	_type() : mPixel() {}\
	\
	_type(const Component* pixel): mPixel(const_cast<Component*>(pixel)) {}\
\
	_type(const _type &rhs) : mPixel(rhs.mPixel) {}\
\
	_type& operator=(const _type &rhs)\
	{	mPixel = rhs.mPixel;	return *this;	}

#define PIXEL_ADAPTER_CONSTRUCTOR(_type)\
	_type() : ConstPixel() {}\
	\
	_type(Component* pixel): ConstPixel(pixel) {}\
\
	_type(const _type &rhs) : ConstPixel(rhs) {}\
\
	_type& operator=(const _type &rhs)\
	{	ConstPixel::operator=(rhs);	}


#define PIXEL_ADAPTER_BODY(_type)\
	static int pixelLength()\
	{	return AdaptedPixel::pixelLength();	}\
\
	operator const Component* () const\
	{	return ConstPixel::mPixel;	}\
\
	_type operator + (int i) const\
	{	return _type(ConstPixel::mPixel + i);	}\
\
	_type operator - (int i) const\
	{	return _type(ConstPixel::mPixel - i);	}\
\
	_type& operator += (int i)\
	{	ConstPixel::mPixel += i;	return *this;	}\
\
	_type& operator -= (int i) const\
	{	ConstPixel::mPixel -= i;	return *this;	}\
\
	_type& operator ++ ()\
	{	ConstPixel::mPixel += 1;	return *this;	}\
\
	_type& operator -- ()\
	{	ConstPixel::mPixel -= 1;	return *this;	}\
\
	_type operator ++ (int)\
	{	_type copy = *this; ConstPixel::mPixel += 1;	 return copy;	}\
\
	_type operator -- (int)\
	{	_type copy = *this; ConstPixel::mPixel -= 1;	 return copy;	}\
\
	bool operator < (const _type &rhs) const\
	{	return ConstPixel::mPixel < rhs.mPixel;	}\
\
	bool operator <= (const _type &rhs) const\
	{	return ConstPixel::mPixel <= rhs.mPixel;	}\
\
	bool operator == (const _type &rhs) const\
	{	return ConstPixel::mPixel == rhs.mPixel;	}\
\
	bool operator != (const _type &rhs) const\
	{	return ConstPixel::mPixel != rhs.mPixel;	}\
\
	bool operator >= (const _type &rhs) const\
	{	return ConstPixel::mPixel >= rhs.mPixel;	}\
\
	bool operator > (const _type &rhs) const\
	{	return ConstPixel::mPixel > rhs.mPixel;		}

//------------------------------------------------------------------------------
//
#define CONST_PIXEL_ADAPTER(_type)\
CONST_PIXEL_ADAPTER_CONSTRUCTOR(_type)\
PIXEL_ADAPTER_BODY(_type)

//------------------------------------------------------------------------------
//
#define PIXEL_ADAPTER(_type)\
PIXEL_ADAPTER_CONSTRUCTOR(_type)\
PIXEL_ADAPTER_BODY(_type)


//==============================================================================
// CLASS RGBYCbCrConverterITU709<>
//==============================================================================
template<class T>
class RGBYCbCrConverterITU709
{
public:
	static T rgbToL(T red, T green, T blue)
	{	return rgbToY(red, green, blue);	}

	static T rgbToY(T red, T green, T blue)
	{	return T(red*seed::HDTVColors::y_r + green*seed::HDTVColors::y_g + blue*seed::HDTVColors::y_b);	}

	static T rgbToCb(T red, T green, T blue)
	{	return T(red*seed::HDTVColors::cb_r + green*seed::HDTVColors::cb_g + blue*seed::HDTVColors::cb_b + 0.5);	}

	static T rgbToCr(T red, T green, T blue)
	{	return T(red*seed::HDTVColors::cr_r + green*seed::HDTVColors::cr_g + blue*seed::HDTVColors::cr_b + 0.5);	}

	static T yCbCrToR(T y, T cb, T cr)
	{	return T(y*seed::HDTVColors::r_y + (cb-0.5)*seed::HDTVColors::r_cb + (cr-0.5)*seed::HDTVColors::r_cr);	}

	static T yCbCrToG(T y, T cb, T cr)
	{	return T(y*seed::HDTVColors::g_y + (cb-0.5)*seed::HDTVColors::g_cb + (cr-0.5)*seed::HDTVColors::g_cr);	}

	static T yCbCrToB(T y, T cb, T cr)
	{	return T(y*seed::HDTVColors::b_y + (cb-0.5)*seed::HDTVColors::b_cb + (cr-0.5)*seed::HDTVColors::b_cr);	}
};

//------------------------------------------------------------------------------
//
template<>
class RGBYCbCrConverterITU709<uint8>
{
public:
	static uint8 rgbToL(uint8 red, uint8 green, uint8 blue)
	{	return rgbToY(red, green, blue);	}

	static uint8 rgbToY(uint8 red, uint8 green, uint8 blue)
	{	return (red*seed::HDTVColors16::y_r + green*seed::HDTVColors16::y_g + blue*seed::HDTVColors16::y_b + 32767)>>16;	}

	static uint8 rgbToCb(uint8 red, uint8 green, uint8 blue)
	{	return ((red*seed::HDTVColors16::cb_r + green*seed::HDTVColors16::cb_g + blue*seed::HDTVColors16::cb_b + 32767)>>16) + 128;	}

	static uint8 rgbToCr(uint8 red, uint8 green, uint8 blue)
	{	return ((red*seed::HDTVColors16::cr_r + green*seed::HDTVColors16::cr_g + blue*seed::HDTVColors16::cr_b + 32767)>>16) + 128;	}

	static uint8 yCbCrToR(uint8 y, uint8 cb, uint8 cr)
	{	return (y*seed::HDTVColors16::r_y + (cb-128)*seed::HDTVColors16::r_cb + (cr-128)*seed::HDTVColors16::r_cr)>>16;	}

	static uint8 yCbCrToG(uint8 y, uint8 cb, uint8 cr)
	{	return (y*seed::HDTVColors16::g_y + (cb-128)*seed::HDTVColors16::g_cb + (cr-128)*seed::HDTVColors16::g_cr)>>16;	}

	static uint8 yCbCrToB(uint8 y, uint8 cb, uint8 cr)
	{	return (y*seed::HDTVColors16::b_y + (cb-128)*seed::HDTVColors16::b_cb + (cr-128)*seed::HDTVColors16::b_cr)>>16;	}
};

//==============================================================================
// CLASS RGBToRYCbCrConverterCCIR601<>
//==============================================================================
template<class T>
class RGBYCbCrConverterCCIR601
{
public:
	static T rgbToL(T red, T green, T blue)
	{	return rgbToY(red, green, blue);	}

	static T rgbToY(T red, T green, T blue)
	{	return T(red*seed::NTSCColors::y_r() + green*seed::NTSCColors::y_g() + blue*seed::NTSCColors::y_b());	}

	static T rgbToCb(T red, T green, T blue)
	{	return T(red*seed::NTSCColors::cb_r() + green*seed::NTSCColors::cb_g() + blue*seed::NTSCColors::cb_b() + 0.5);	}

	static T rgbToCr(T red, T green, T blue)
	{	return T(red*seed::NTSCColors::cr_r() + green*seed::NTSCColors::cr_g() + blue*seed::NTSCColors::cr_b() + 0.5);	}

	static T yCbCrToR(T y, T cb, T cr)
	{	return T(y*seed::NTSCColors::r_y() + (cb-0.5)*seed::NTSCColors::r_cb() + (cr-0.5)*seed::NTSCColors::r_cr());	}

	static T yCbCrToG(T y, T cb, T cr)
	{	return T(y*seed::NTSCColors::g_y() + (cb-0.5)*seed::NTSCColors::g_cb() + (cr-0.5)*seed::NTSCColors::g_cr());	}

	static T yCbCrToB(T y, T cb, T cr)
	{	return T(y*seed::NTSCColors::b_y() + (cb-0.5)*seed::NTSCColors::b_cb() + (cr-0.5)*seed::NTSCColors::b_cr());	}
};

//------------------------------------------------------------------------------
//
template<>
class RGBYCbCrConverterCCIR601<uint8>
{
public:
	static uint8 rgbToL(uint8 red, uint8 green, uint8 blue)
	{	return rgbToY(red, green, blue);	}

	static uint8 rgbToY(uint8 red, uint8 green, uint8 blue)
	{
		float fy, fcb, fcr;
		int y;
//		int cb, cr;
		fy  = red*seed::NTSCColors::y_r() + green*seed::NTSCColors::y_g() + blue*seed::NTSCColors::y_b();
		fcb = red*seed::NTSCColors::cb_r() + green*seed::NTSCColors::cb_g() + blue*seed::NTSCColors::cb_b();
		fcr = red*seed::NTSCColors::cr_r() + green*seed::NTSCColors::cr_g() + blue*seed::NTSCColors::cr_b();

		y = (red*seed::NTSCColors16::y_r() + green*seed::NTSCColors16::y_g() + blue*seed::NTSCColors16::y_b() + 32767);
		if (y <= 0x00000000)	y = 0;
		else if (y >= 0x00FFFFFF)	y = 255;
		else y >>= 16;

//		cb = rgbToCb(red, green, blue);
//		cr = rgbToCr(red, green, blue);
//		uint8 r2 = yCbCrToR(y, cb, cr);
//		uint8 g2 = yCbCrToG(y, cb, cr);
//		uint8 b2 = yCbCrToB(y, cb, cr);

//		ASSERT(r2 >= red - 1 && r2 <= red + 1);
//		ASSERT(g2 >= green - 1 && g2 <= green + 1);
//		ASSERT(b2 >= blue - 1 && b2 <= blue + 1);
		return y;
	}

	static uint8 rgbToCb(uint8 red, uint8 green, uint8 blue)
	{
		int cb = (red*seed::NTSCColors16::cb_r() + green*seed::NTSCColors16::cb_g() + blue*seed::NTSCColors16::cb_b() + 32767 + 0x00800000);
		if (cb <= 0x00000000)	return 0;
		if (cb >= 0x00FFFFFF)	return 255;
		return cb >> 16;
	}

	static uint8 rgbToCr(uint8 red, uint8 green, uint8 blue)
	{	
		int cr = (red*seed::NTSCColors16::cr_r() + green*seed::NTSCColors16::cr_g() + blue*seed::NTSCColors16::cr_b() + 32767 + 0x00800000);
		if (cr <= 0x00000000)	return 0;
		if (cr >= 0x00FFFFFF)	return 255;
		return cr >> 16;
	}

	static uint8 yCbCrToR(uint8 y, uint8 cb, uint8 cr)
	{
		int r = (y*seed::NTSCColors16::r_y() + (cb-128)*seed::NTSCColors16::r_cb() + (cr-128)*seed::NTSCColors16::r_cr() + 32767);
		if (r <= 0x00000000)	return 0;
		if (r >= 0x00FFFFFF)	return 255;
		return r >> 16;
	}

	static uint8 yCbCrToG(uint8 y, uint8 cb, uint8 cr)
	{
		int g = (y*seed::NTSCColors16::g_y() + (cb-128)*seed::NTSCColors16::g_cb() + (cr-128)*seed::NTSCColors16::g_cr() + 32767);
		if (g <= 0x00000000)	return 0;
		if (g >= 0x00FFFFFF)	return 255;
		return g >> 16;
	}

	static uint8 yCbCrToB(uint8 y, uint8 cb, uint8 cr)
	{
		int b = (y*seed::NTSCColors16::b_y() + (cb-128)*seed::NTSCColors16::b_cb() + (cr-128)*seed::NTSCColors16::b_cr() + 32767);
		if (b <= 0x00000000)	return 0;
		if (b >= 0x00FFFFFF)	return 255;
		return b >> 16;
	}
};

//==============================================================================
//	CLASS ConstRGBAsLPixel
//==============================================================================
template <class _RGBPixel, typename LConverter=RGBYCbCrConverterCCIR601<typename _RGBPixel::Component> >
class ConstRGBAsLPixel
{
public:
	typedef LConverter 						Converter;
	typedef typename _RGBPixel::Component 	Component;
	typedef ConstRGBAsLPixel				ConstPixel;
	typedef _RGBPixel						AdaptedPixel;

	CONST_PIXEL_ADAPTER(ConstRGBAsLPixel);

public:
	Component luminance() const
	{	return ConstPixel::luminance(mPixel);	}
	
	static Component luminance(const _RGBPixel &pixel)
	{	return Converter::rgbToL(pixel.red(), pixel.green(), pixel.blue());	}

protected:	
	//	not const because we want to derive a non-const version
	/*const*/	_RGBPixel mPixel;
};


//==============================================================================
//	CLASS RGBAsLPixel
//==============================================================================
template <class _RGBPixel>
class RGBAsLPixel: public ConstRGBAsLPixel<_RGBPixel>
{
public:
	typedef RGBAsLPixel						Pixel;
	typedef ConstRGBAsLPixel<_RGBPixel>		ConstPixel;
	typedef typename ConstPixel::Component	Component;
	typedef _RGBPixel						AdaptedPixel;

	PIXEL_ADAPTER(RGBAsLPixel);

public:
	void setLuminance(int val)
	{	Pixel::setLuminance(ConstPixel::mPixel, val);	}
	
	static void setLuminance(_RGBPixel &pixel, int val)
	{	pixel.setRed(val); pixel.setGreen(val); pixel.setBlue(val);	}
};


//==============================================================================
//	CLASS DefaultAlphaValue
//==============================================================================
template<class Pixel, class Component>
class DefaultAlphaValue
{};

//------------------------------------------------------------------------------
//
template<class Pixel>
class DefaultAlphaValue<Pixel, uint8>
{
public:
	static uint8 alpha(const Pixel &pixel)	{	return 255;	}
};

//------------------------------------------------------------------------------
//
template<class Pixel>
class DefaultAlphaValue<Pixel, float>
{
public:
	static float alpha(const Pixel &pixel)	{	return 1.0f;	}
};

//------------------------------------------------------------------------------
//
template<class Pixel>
class DefaultAlphaValue<Pixel, double>
{
public:
	static double alpha(const Pixel &pixel)	{	return 1.0;	}
};

//------------------------------------------------------------------------------
//
template<class Pixel>
class DefaultAlphaValue<Pixel, uint16>
{
public:
	static uint16 alpha(const Pixel &pixel)	{	return 65535;	}
};

//==============================================================================
//	CLASS ConstRGBAsRGBAPixel
//==============================================================================
template <class _RGBPixel, class Alpha=DefaultAlphaValue<_RGBPixel, typename _RGBPixel::Component> >
class ConstRGBAsRGBAPixel
{
public:
	typedef typename _RGBPixel::Component 		Component;
	typedef ConstRGBAsRGBAPixel					ConstPixel;
	typedef _RGBPixel							AdaptedPixel;

	CONST_PIXEL_ADAPTER(ConstRGBAsRGBAPixel);

public:
	Component red() const
	{	return ConstPixel::red(mPixel);	}

	Component green() const
	{	return ConstPixel::green(mPixel);	}

	Component blue() const
	{	return ConstPixel::blue(mPixel);	}

	Component alpha() const
	{	return ConstPixel::alpha(mPixel);	}
	

	static Component red(const _RGBPixel &pixel)
	{	return pixel.red();	}

	static Component green(const _RGBPixel &pixel)
	{	return pixel.green();	}

	static Component blue(const _RGBPixel &pixel)
	{	return pixel.blue();	}

	static Component alpha(const _RGBPixel &pixel)
	{	return Alpha::alpha(pixel);	}

protected:	
	//	not const because we want to derive a non-const version
	/*const*/	_RGBPixel mPixel;
};

//==============================================================================
//	CLASS RGBAsRGBAPixel
//==============================================================================
template <class _RGBPixel, class Alpha=DefaultAlphaValue<_RGBPixel, typename _RGBPixel::Component> >
class RGBAsRGBAPixel: public ConstRGBAsRGBAPixel<_RGBPixel, Alpha>
{
public:
	typedef RGBAsRGBAPixel								Pixel;
	typedef ConstRGBAsRGBAPixel<_RGBPixel, Alpha>		ConstPixel;
	typedef typename ConstPixel::Component				Component;
	typedef _RGBPixel									AdaptedPixel;

	PIXEL_ADAPTER(RGBAsRGBAPixel);

public:
	void setRed(int val)
	{	Pixel::setRed(ConstPixel::mPixel, val);	}

	void setGreen(int val)
	{	Pixel::setGreen(ConstPixel::mPixel, val);	}

	void setBlue(int val)
	{	Pixel::setBlue(ConstPixel::mPixel, val);	}

	void setAlpha(int val)
	{	Pixel::setAlpha(ConstPixel::mPixel, val);	}
	
	static void setRed(_RGBPixel &pixel, int val)
	{	pixel.setRed(val); }

	static void setGreen(_RGBPixel &pixel, int val)
	{	pixel.setGreen(val); }

	static void setBlue(_RGBPixel &pixel, int val)
	{	pixel.setBlue(val); }

	static void setAlpha(_RGBPixel &pixel, int val)
	{}
};

//==============================================================================
//	CLASS ConstLAsRGBPixel
//==============================================================================
template <class Pixel>
class ConstLAsRGBPixel
{
public:
	typedef typename Pixel::Component 			Component;
	typedef ConstLAsRGBPixel					ConstPixel;
	typedef Pixel								AdaptedPixel;

	CONST_PIXEL_ADAPTER(ConstLAsRGBPixel);

	Component red() const
	{	return ConstPixel::red(mPixel);	}

	Component green() const
	{	return ConstPixel::green(mPixel);	}

	Component blue() const
	{	return ConstPixel::blue(mPixel);	}

	static Component red(const Pixel &pixel)
	{	return pixel.luminance();	}

	static Component green(const Pixel &pixel)
	{	return pixel.luminance();	}

	static Component blue(const Pixel &pixel)
	{	return pixel.luminance();	}

protected:	
	//	not const because we want to derive a non-const version
	/*const*/	Pixel mPixel;

};



//==============================================================================
//	CLASS ConstLAAsRGBAPixel
//==============================================================================
template <class Pixel>
class ConstLAAsRGBAPixel
{
public:
	typedef typename Pixel::Component 			Component;
	typedef ConstLAAsRGBAPixel					ConstPixel;
	typedef Pixel								AdaptedPixel;

	CONST_PIXEL_ADAPTER(ConstLAAsRGBAPixel);

	Component red() const
	{	return ConstPixel::red(mPixel);	}

	Component green() const
	{	return ConstPixel::green(mPixel);	}

	Component blue() const
	{	return ConstPixel::blue(mPixel);	}

	Component alpha() const
	{	return ConstPixel::alpha(mPixel);	}

	static Component red(const Pixel &pixel)
	{	return pixel.luminance();	}

	static Component green(const Pixel &pixel)
	{	return pixel.luminance();	}

	static Component blue(const Pixel &pixel)
	{	return pixel.luminance();	}

	static Component alpha(const Pixel &pixel)
	{	return pixel.alpha();	}

protected:	
	//	not const because we want to derive a non-const version
	/*const*/	Pixel mPixel;

};

//==============================================================================
//	CLASS ConstRGBAsRGBAPixel
//==============================================================================
template <class _RGBPixel, class Alpha=DefaultAlphaValue<_RGBPixel, typename _RGBPixel::Component> >
class ConstLAsLAPixel
{
public:
	typedef typename _RGBPixel::Component 		Component;
	typedef ConstLAsLAPixel						ConstPixel;
	typedef _RGBPixel							AdaptedPixel;

	CONST_PIXEL_ADAPTER(ConstLAsLAPixel);

public:
	Component luminance() const
	{	return ConstPixel::luminance(mPixel);	}

	Component alpha() const
	{	return Alpha::alpha(mPixel);	}
	
	static Component luminance(const _RGBPixel &pixel)
	{	return pixel.luminance();	}

	static Component alpha(const _RGBPixel &pixel)
	{	return Alpha::alpha(pixel);	}

protected:	
	//	not const because we want to derive a non-const version
	/*const*/	_RGBPixel mPixel;
};

//==============================================================================
//	CLASS LAsLAPixel
//==============================================================================
template <class _RGBPixel, class Alpha=DefaultAlphaValue<_RGBPixel, typename _RGBPixel::Component> >
class LAsLAPixel: public ConstLAsLAPixel<_RGBPixel, Alpha>
{
public:
	typedef LAsLAPixel								Pixel;
	typedef ConstLAsLAPixel<_RGBPixel, Alpha>		ConstPixel;
	typedef typename ConstPixel::Component				Component;
	typedef _RGBPixel									AdaptedPixel;

	PIXEL_ADAPTER(LAsLAPixel);

public:
	void setLuminance(int val)
	{	Pixel::setLuminance(ConstPixel::mPixel, val);	}

	void setAlpha(int val)
	{	Pixel::setAlpha(ConstPixel::mPixel, val);	}
	
	static void setLuminance(_RGBPixel &pixel, int val)
	{	pixel.setLuminance(val); }

	static void setAlpha(_RGBPixel &pixel, int val)
	{}
};

//==============================================================================
//	CLASS ConstRGBAsYCbCrPixel
//==============================================================================
template <class _RGBPixel, typename LConverter=RGBYCbCrConverterCCIR601<typename _RGBPixel::Component> >
class ConstRGBAsYCbCrPixel
{
public:
	typedef LConverter 						Converter;
	typedef typename _RGBPixel::Component 	Component;
	typedef ConstRGBAsYCbCrPixel			ConstPixel;
	typedef _RGBPixel						AdaptedPixel;

	CONST_PIXEL_ADAPTER(ConstRGBAsYCbCrPixel);

public:
	Component luminance() const
	{	return ConstPixel::luminance(mPixel);	}

	Component cb() const
	{	return ConstPixel::cb(mPixel);	}

	Component cr() const
	{	return ConstPixel::cr(mPixel);	}
	
	static Component luminance(const _RGBPixel &pixel)
	{	return Converter::rgbToY(pixel.red(), pixel.green(), pixel.blue());		}

	static Component cb(const _RGBPixel &pixel)
	{	return Converter::rgbToCb(pixel.red(), pixel.green(), pixel.blue());	}

	static Component cr(const _RGBPixel &pixel)
	{	return Converter::rgbToCr(pixel.red(), pixel.green(), pixel.blue());	}

protected:	
	//	not const because we want to derive a non-const version
	/*const*/	_RGBPixel mPixel;
};

//==============================================================================
//	CLASS ConstYCbCrAsRGBPixel
//==============================================================================
template <class YCbCrPixel, typename LConverter=RGBYCbCrConverterCCIR601<typename YCbCrPixel::Component> >
class ConstYCbCrAsRGBPixel
{
public:
	typedef LConverter 						Converter;
	typedef typename YCbCrPixel::Component 	Component;
	typedef ConstYCbCrAsRGBPixel			ConstPixel;
	typedef YCbCrPixel						AdaptedPixel;

	CONST_PIXEL_ADAPTER(ConstYCbCrAsRGBPixel);

public:
	Component red() const
	{	return ConstPixel::red(mPixel);	}

	Component green() const
	{	return ConstPixel::green(mPixel);	}

	Component blue() const
	{	return ConstPixel::blue(mPixel);	}
	
	static Component red(const YCbCrPixel &pixel)
	{	return Converter::yCbCrToR(pixel.luminance(), pixel.cb(), pixel.cr());		}

	static Component green(const YCbCrPixel &pixel)
	{	return Converter::yCbCrToG(pixel.luminance(), pixel.cb(), pixel.cr());		}

	static Component blue(const YCbCrPixel &pixel)
	{	return Converter::yCbCrToB(pixel.luminance(), pixel.cb(), pixel.cr());		}

protected:	
	//	not const because we want to derive a non-const version
	/*const*/	YCbCrPixel mPixel;
};

//==============================================================================
//	CLASS DefaultAlphaValue
//==============================================================================
template<class Pixel, class Component>
class ChromaZeroValue
{};

//------------------------------------------------------------------------------
//
template<class Pixel>
class ChromaZeroValue<Pixel, uint8>
{
public:
	static uint8 chroma(const Pixel &pixel)	{	return 128;	}
};

//------------------------------------------------------------------------------
//
template<class Pixel>
class ChromaZeroValue<Pixel, float>
{
public:
	static float chroma(const Pixel &pixel)	{	return 0.5f;	}
};

//------------------------------------------------------------------------------
//
template<class Pixel>
class ChromaZeroValue<Pixel, double>
{
public:
	static double chroma(const Pixel &pixel)	{	return 0.5;	}
};

//------------------------------------------------------------------------------
//
template<class Pixel>
class ChromaZeroValue<Pixel, uint16>
{
public:
	static uint16 chroma(const Pixel &pixel)	{	return 32768;	}
};


//==============================================================================
//	CLASS ConstLAsYCbCrPixel
//==============================================================================
template <class _LPixel, typename Chroma=ChromaZeroValue<_LPixel, typename _LPixel::Component> >
class ConstLAsYCbCrPixel
{
public:
	typedef typename _LPixel::Component 	Component;
	typedef ConstLAsYCbCrPixel				ConstPixel;
	typedef _LPixel							AdaptedPixel;

	CONST_PIXEL_ADAPTER(ConstLAsYCbCrPixel);

public:
	Component luminance() const
	{	return ConstPixel::luminance(mPixel);	}

	Component cb() const
	{	return ConstPixel::cb(mPixel);	}

	Component cr() const
	{	return ConstPixel::cr(mPixel);	}
	
	static Component luminance(const _LPixel &pixel)
	{	return pixel.luminance();		}

	static Component cb(const _LPixel &pixel)
	{	return Chroma::chroma(pixel);	}

	static Component cr(const _LPixel &pixel)
	{	return Chroma::chroma(pixel);	}

protected:	
	//	not const because we want to derive a non-const version
	/*const*/	_LPixel mPixel;
};

#ifdef GENERIC_NAMESPACE
}
#endif

#endif // __GENERIC_IMAGE_PIXELADAPTER__
