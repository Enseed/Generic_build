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
#ifndef __GENERIC_IMAGE_PIXEL__
#define __GENERIC_IMAGE_PIXEL__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "Pixel.declare.deprecated.h"
#include "PixMap.declare.deprecated.h"
#include "ColorProfiles.h"
#include <stddef.h>

namespace seed {


//==============================================================================
//	MACRO Pixel
//==============================================================================
#define DECLARE_CONST_PIXEL(_pixel)\
	_pixel() : mPixel(NULL) {}\
\
	_pixel(const Component *pixel): mPixel(const_cast<Component*>(pixel)) {}\
\
	_pixel(const ConstPixel &rhs) : mPixel(const_cast<Component*>(rhs.mPixel)) {}\
\
	virtual ~_pixel() {}\
\
	typedef int ComponentCount;\
	static ComponentCount pixelLength()\
	{	return COMPONENT_COUNT;	}\
\
	static ColorProfile defaultColorProfile()\
	{	return ColorProfile(DEFAULT_COLOR_PROFILE);	}\
\
	operator const Component*() const\
	{	return ConstPixel::mPixel;	}\
\
	operator const void*() const\
	{	return ConstPixel::mPixel;	}\
\
	_pixel& operator=(const _pixel &rhs)\
	{	ConstPixel::mPixel = rhs.mPixel;	return *this;	}\
\
	_pixel operator + (int i) const\
	{	return _pixel(ConstPixel::mPixel + i * _pixel::pixelLength());	}\
\
	_pixel operator - (int i) const\
	{	return _pixel(ConstPixel::mPixel - i * _pixel::pixelLength());	}\
\
	_pixel& operator += (int i)\
	{	ConstPixel::mPixel += i * _pixel::pixelLength();	return *this;	}\
\
	_pixel& operator -= (int i) const\
	{	ConstPixel::mPixel -= i * _pixel::pixelLength();	return *this;	}\
\
	_pixel& operator ++ ()\
	{	ConstPixel::mPixel += _pixel::pixelLength();	return *this;	}\
\
	_pixel& operator -- ()\
	{	ConstPixel::mPixel -= _pixel::pixelLength();	return *this;	}\
\
	_pixel operator ++ (int)\
	{	_pixel copy = *this; ConstPixel::mPixel += _pixel::pixelLength();	 return copy;	}\
\
	_pixel operator -- (int)\
	{	_pixel copy = *this; ConstPixel::mPixel -= _pixel::pixelLength();	 return copy;	}\
\
	const Component& operator [] (int i) const\
	{	return ConstPixel::mPixel[i];	}\
\
	bool operator < (const _pixel &rhs) const\
	{	return ConstPixel::mPixel < rhs.mPixel;	}\
\
	bool operator <= (const _pixel &rhs) const\
	{	return ConstPixel::mPixel <= rhs.mPixel;	}\
\
	bool operator == (const _pixel &rhs) const\
	{	return ConstPixel::mPixel == rhs.mPixel;	}\
\
	bool operator != (const _pixel &rhs) const\
	{	return ConstPixel::mPixel != rhs.mPixel;	}\
\
	bool operator >= (const _pixel &rhs) const\
	{	return ConstPixel::mPixel >= rhs.mPixel;	}\
\
	bool operator > (const _pixel &rhs) const\
	{	return ConstPixel::mPixel > rhs.mPixel;		}

#define DECLARE_PIXEL(_pixel)\
	_pixel() : ConstPixel() {}\
\
	_pixel(Component *pixel): ConstPixel(pixel) {}\
\
	_pixel(const Pixel &rhs) : ConstPixel(rhs) {}\
\
	~_pixel() {}\
\
	operator Component*() const\
	{	return ConstPixel::mPixel;	}\
\
	operator void*() const\
	{	return ConstPixel::mPixel;	}\
\
	_pixel operator + (int i) const\
	{	return _pixel(ConstPixel::mPixel + i * _pixel::pixelLength());	}\
\
	_pixel operator - (int i) const\
	{	return _pixel(ConstPixel::mPixel - i * _pixel::pixelLength());	}\
\
	Component& operator [] (int i)\
	{	return ConstPixel::mPixel[i];	}\

#define RGBAPixelFamily(_C1, _C2, _C3, _C4)\
template <class C>\
	class Const ## _C1 ## _C2 ## _C3 ## _C4 ## Pixel\
{\
private:\
	class ComponentOrdering { public: enum {_C1, _C2, _C3, _C4, COMPONENT_COUNT}; };\
\
public:\
	typedef Const ## _C1 ## _C2 ## _C3 ## _C4 ## Pixel ConstPixel;\
	typedef C Component;\
\
	typedef enum\
	{\
		RED = ComponentOrdering::R,\
		GREEN = ComponentOrdering::G,\
		BLUE = ComponentOrdering::B,\
		ALPHA = ComponentOrdering::A,\
		COMPONENT_COUNT = ComponentOrdering::COMPONENT_COUNT\
	} Index;\
\
	enum {	DEFAULT_COLOR_PROFILE = MK_COLORPROFILE_UNCALIBRATED_RGBA	};\
\
public:\
	DECLARE_CONST_PIXEL(Const ## _C1 ## _C2 ## _C3 ## _C4 ## Pixel);\
	\
	Component alpha() const\
	{	return alpha(mPixel);	}\
	\
	Component red() const\
	{	return red(mPixel);		}\
	\
	Component green() const\
	{	return green(mPixel);		}\
	\
	Component blue() const\
	{	return blue(mPixel);		}\
\
public:\
	static const Component alpha(const Component* pixel)\
	{	return pixel[ALPHA];	}\
	\
	static const Component red(const Component* pixel)\
	{	return pixel[RED];		}\
	\
	static const Component green(const Component* pixel)\
	{	return pixel[GREEN];	}\
	\
	static const Component blue(const Component* pixel)\
	{	return pixel[BLUE];		}\
\
protected:	\
	/*	not const because we want to derive a non-const version*/\
	/*const*/	Component* mPixel;\
};\
\
template <class C>\
class _C1 ## _C2 ## _C3 ## _C4 ## Pixel: public Const ## _C1 ## _C2 ## _C3 ## _C4 ## Pixel<C>\
{\
public:\
	typedef C								Component;\
	typedef _C1 ## _C2 ## _C3 ## _C4 ## Pixel						Pixel;\
	typedef Const ## _C1 ## _C2 ## _C3 ## _C4 ## Pixel<Component>		ConstPixel;\
\
public:\
	DECLARE_PIXEL(_C1 ## _C2 ## _C3 ## _C4 ## Pixel);\
\
public:\
	template<class RHS>\
	Pixel& copy(const RHS &rhs)\
	{\
		setRGBA(static_cast<C>(rhs.red()), static_cast<C>(rhs.green()), static_cast<C>(rhs.blue()), static_cast<C>(rhs.alpha()));\
		return *this;\
	}\
	\
	void setAlpha(Component val)\
	{	Pixel::setAlpha(ConstPixel::mPixel, val);	}\
	\
	void setRed(Component val)\
	{	Pixel::setRed(ConstPixel::mPixel, val);	}\
	\
	void setGreen(Component val)\
	{	Pixel::setGreen(ConstPixel::mPixel, val);	}\
	\
	void setBlue(Component val)\
	{	Pixel::setBlue(ConstPixel::mPixel, val);	}\
\
	void setRGBA(Component r, Component g, Component b, Component a)\
	{	Pixel::setRGBA(ConstPixel::mPixel, r, g, b, a);	}\
\
public:\
	static void setAlpha(Component* pixel, Component val)\
	{	pixel[ConstPixel::ALPHA] = val;	}\
	\
	static void setRed(Component* pixel, Component val)\
	{	pixel[ConstPixel::RED] = val;		}\
	\
	static void setGreen(Component* pixel, Component val)\
	{	pixel[ConstPixel::GREEN] = val;	}\
	\
	static void setBlue(Component* pixel, Component val)\
	{	pixel[ConstPixel::BLUE] = val;	}\
\
	static void setRGBA(Component* pixel, Component r, Component g, Component b, Component a)\
	{	\
		setRed(pixel, r);\
		setGreen(pixel, g);\
		setBlue(pixel, b);\
		setAlpha(pixel,a);\
	}\
};




#define RGBPixelFamily(_C1, _C2, _C3)\
template <class C>\
class Const ## _C1 ## _C2 ## _C3 ## Pixel\
{\
private:\
	class ComponentOrdering { public: enum {_C1, _C2, _C3, COMPONENT_COUNT}; };\
public:\
	typedef C			  Component;\
	typedef Const ## _C1 ## _C2 ## _C3 ## Pixel ConstPixel;\
	typedef enum\
	{\
		RED = ComponentOrdering::R,\
		GREEN = ComponentOrdering::G,\
		BLUE = ComponentOrdering::B,\
		COMPONENT_COUNT = ComponentOrdering::COMPONENT_COUNT\
	} Index;\
\
	enum {	DEFAULT_COLOR_PROFILE = MK_COLORPROFILE_UNCALIBRATED_RGBA	};\
\
	DECLARE_CONST_PIXEL(Const ## _C1 ## _C2 ## _C3 ## Pixel);\
\
public:\
	const Component red() const\
	{	return ConstPixel::red(mPixel);		}\
	\
	const Component green() const\
	{	return ConstPixel::green(mPixel);		}\
	\
	const Component blue() const\
	{	return ConstPixel::blue(mPixel);		}\
\
public:\
	static const Component red(const Component* pixel)\
	{	return pixel[RED];		}\
	\
	static const Component green(const Component* pixel)\
	{	return pixel[GREEN];	}\
	\
	static const Component blue(const Component* pixel)\
	{	return pixel[BLUE];	}\
\
protected:	\
	/*	not const because we want to derive a non-const version*/\
	/*const*/	Component* mPixel;\
};\
\
template <class C>\
class _C1 ## _C2 ## _C3 ## Pixel: public Const ## _C1 ## _C2 ## _C3 ## Pixel<C>\
{\
public:\
	typedef C Component;\
	typedef _C1 ## _C2 ## _C3 ## Pixel						Pixel;\
	typedef Const ## _C1 ## _C2 ## _C3 ## Pixel<Component>	ConstPixel;\
\
public:\
	DECLARE_PIXEL(_C1 ## _C2 ## _C3 ## Pixel);\
\
public:\
	template<class RHS>\
	Pixel& copy(const RHS &rhs)\
	{\
		setRGB(static_cast<C>(rhs.red()), static_cast<C>(rhs.green()), static_cast<C>(rhs.blue()));\
		return *this;\
	}\
	\
	template<class RHS>\
	Pixel& compositeOver(const RHS &rhs)\
	{\
		/* fixme */\
		return copy(rhs);\
	}\
\
	void setRed(Component val)\
	{	Pixel::setRed(ConstPixel::mPixel, val);	}\
	\
	void setGreen(Component val)\
	{	Pixel::setGreen(ConstPixel::mPixel, val);	}\
	\
	void setBlue(Component val)\
	{	Pixel::setBlue(ConstPixel::mPixel, val);	}\
	\
	void setRGB(Component r, Component g, Component b)\
	{	Pixel::setRGB(ConstPixel::mPixel, r, g, b);	}\
\
public:\
	static void setRed(Component* pixel, Component val)\
	{	pixel[ConstPixel::RED] = val;		}\
	\
	static void setGreen(Component* pixel, Component val)\
	{	pixel[ConstPixel::GREEN] = val;	}\
	\
	static void setBlue(Component* pixel, Component val)\
	{	pixel[ConstPixel::BLUE] = val;	}\
\
	static void setRGB(Component* pixel, Component r, Component g, Component b)\
	{	\
		setRed(pixel, r);\
		setGreen(pixel, g);\
		setBlue(pixel, b);\
	}\
};




//==============================================================================
//	CLASS ConstARGBPixel
//==============================================================================
RGBAPixelFamily(A, R, G, B)
RGBAPixelFamily(R, G, B, A)
RGBAPixelFamily(B, G, R, A)
RGBAPixelFamily(A, B, G, R)
RGBPixelFamily(R, G, B)
RGBPixelFamily(B, G, R)



//==============================================================================
//	CLASS ConstLPixel
//==============================================================================
template <class C>
class ConstLPixel
{
public:
	typedef C Component;
	typedef ConstLPixel ConstPixel;
	typedef enum
	{
		LUMINANCE = 0,
		COMPONENT_COUNT
	} Index;

	enum {	DEFAULT_COLOR_PROFILE = MK_COLORPROFILE_UNCALIBRATED_LUMINANCE	};

public:
	DECLARE_CONST_PIXEL(ConstLPixel);

public:
	const Component luminance() const
	{	return ConstPixel::luminance(mPixel);		}

	static const Component luminance(const Component *pixel)
	{	return pixel[LUMINANCE];	}

protected:	
	//	not const because we want to derive a non-const version
	/*const*/	Component *mPixel;
};


//==============================================================================
//	CLASS LPixel
//==============================================================================
template <class C>
class LPixel: public ConstLPixel<C>
{
public:
	typedef C								Component;
	typedef LPixel							Pixel;
	typedef ConstLPixel<Component>			ConstPixel;

public:
	DECLARE_PIXEL(LPixel);

public:
	template<class RHS>
	Pixel& copy(const RHS &rhs)
	{
		setLuminance(static_cast<C>(rhs.luminance()));
		return *this;
	}
	
	template<class RHS>
	Pixel& compositeOver(const RHS &rhs)
	{
		// fixme
		return copy(rhs);
	}

	void setLuminance(Component val)
	{	Pixel::setLuminance(ConstPixel::mPixel, val);	}
	
public:
	static void setLuminance(Component* pixel, Component val)
	{	pixel[ConstPixel::LUMINANCE] = val;	}
};



//==============================================================================
//	CLASS ConstLAPixel
//==============================================================================
template <class C>
class ConstLAPixel
{
public:
	typedef C Component;
	typedef ConstLAPixel ConstPixel;
	typedef enum
	{
		LUMINANCE = 0,
		ALPHA,
		COMPONENT_COUNT
	} Index;

	enum {	DEFAULT_COLOR_PROFILE = MK_COLORPROFILE_UNCALIBRATED_LUMINANCE	};

	DECLARE_CONST_PIXEL(ConstLAPixel);

public:
	const Component luminance() const
	{	return ConstPixel::luminance(mPixel);		}

	const Component alpha() const
	{	return ConstPixel::alpha(mPixel);		}

public:
	static const Component luminance(const Component *pixel)
	{	return pixel[LUMINANCE];	}

	static const Component alpha(const Component *pixel)
	{	return pixel[ALPHA];	}

protected:	
	//	not const because we want to derive a non-const version
	/*const*/	Component *mPixel;
};


//==============================================================================
//	CLASS LPixel
//==============================================================================
template <class C>
class LAPixel: public ConstLAPixel<C>
{
public:
	typedef C								Component;
	typedef LAPixel							Pixel;
	typedef ConstLAPixel<Component>			ConstPixel;

public:
	DECLARE_PIXEL(LAPixel);

public:
	template<class RHS>
	Pixel& copy(const RHS &rhs)
	{
		setLA(static_cast<C>(rhs.luminance()), static_cast<C>(rhs.alpha()));
		return *this;
	}
	
	template<class RHS>
	Pixel& compositeOver(const RHS &rhs)
	{
		// fixme
		return copy(rhs);
	}

	void setLuminance(Component val)
	{	Pixel::setLuminance(ConstPixel::mPixel, val);	}

	void setAlpha(Component val)
	{	Pixel::setAlpha(ConstPixel::mPixel, val);	}

	void setLA(Component l, Component a)
	{	Pixel::setLA(ConstPixel::mPixel, l, a);	}
	
public:
	static void setLuminance(Component* pixel, Component val)
	{	pixel[ConstPixel::LUMINANCE] = val;	}

	static void setAlpha(Component* pixel, Component val)
	{	pixel[ConstPixel::ALPHA] = val;	}

	static void setLA(Component* pixel, Component l, Component a)
	{	
		setLuminance(pixel, l);
		setAlpha(pixel, a);
	}
};

//==============================================================================
//	CLASS ConstYCbCrPixel
//==============================================================================
template <class C>
class ConstYCbCrPixel
{
public:
	typedef C				Component;
	typedef ConstYCbCrPixel ConstPixel;
	typedef enum
	{
		LUMINANCE = 0,
		CHROMINANCE_BLUE,
		CHROMINANCE_RED,
		COMPONENT_COUNT
	} Index;

	enum {	DEFAULT_COLOR_PROFILE = MK_COLORPROFILE_UNCALIBRATED_YCbCrA_NTSC};

	DECLARE_CONST_PIXEL(ConstYCbCrPixel);

public:
	const Component luminance() const
	{	return ConstPixel::luminance(mPixel);		}
	
	const Component cb() const
	{	return ConstPixel::cb(mPixel);		}
	
	const Component cr() const
	{	return ConstPixel::cr(mPixel);		}

public:
	static const Component luminance(const Component* pixel)
	{	return pixel[LUMINANCE];		}
	
	static const Component cb(const Component* pixel)
	{	return pixel[CHROMINANCE_BLUE];	}
	
	static const Component cr(const Component* pixel)
	{	return pixel[CHROMINANCE_RED];	}

protected:	
	//	not const because we want to derive a non-const version
	/*const*/	Component* mPixel;
};


//==============================================================================
//	CLASS RGBPixel
//==============================================================================
template <class C>
class YCbCrPixel: public ConstYCbCrPixel<C>
{
public:
	typedef C Component;
	typedef YCbCrPixel						Pixel;
	typedef ConstYCbCrPixel<Component>		ConstPixel;

public:
	DECLARE_PIXEL(YCbCrPixel);

public:
	template<class RHS>
	Pixel& copy(const RHS &rhs)
	{
		setYCbCr(static_cast<C>(rhs.luminance()), 
			static_cast<C>(rhs.cb()), 
			static_cast<C>(rhs.cr()));
		return *this;
	}
	
	template<class RHS>
	Pixel& compositeOver(const RHS &rhs)
	{
		// fixme
		return copy(rhs);
	}

	void setLuminance(Component val)
	{	Pixel::setLuminance(ConstPixel::mPixel, val);	}
	
	void setCb(Component val)
	{	Pixel::setCb(ConstPixel::mPixel, val);	}
	
	void setCr(Component val)
	{	Pixel::setCr(ConstPixel::mPixel, val);	}

	void setYCbCr(Component y, Component cb, Component cr)
	{	Pixel::setYCbCr(ConstPixel::mPixel, y, cb, cr);	}
	
public:
	static void setLuminance(Component* pixel, Component val)
	{	pixel[ConstPixel::LUMINANCE] = val;		}
	
	static void setCb(Component* pixel, Component val)
	{	pixel[ConstPixel::CHROMINANCE_BLUE] = val;	}
	
	static void setCr(Component* pixel, Component val)
	{	pixel[ConstPixel::CHROMINANCE_RED] = val;	}

	static void setYCbCr(Component* pixel, Component y, Component cb, Component cr)
	{	
		setLuminance(pixel, y);
		setCb(pixel, cb);
		setCr(pixel, cr);
	}
};

}

#include "src/Pixel.inline.h"

#endif // __GENERIC_IMAGE_PIXEL__
