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
#ifndef __ITL_PIXELMANIPULATION_H__
#define __ITL_PIXELMANIPULATION_H__

//==============================================================================
// FILE PixelManipulation.h
//==============================================================================
// Manipulation of pixels (setting and getting colors) has been centralized here
// such that operations can be easily overloaded if there is a faster way to
// execute them on a given architecture.  For example, the setRGBA defaults to
// setRed, setGreen, setBlue and setAlpha, but it might be faster to do it in 
// one shot for RGBA32 pixels (dst = red << 24 | green << 16 | blue << 8 | alpha)
//
// This would be done by specializing the function for the RGB32Pixel:
//
// template<>
// void PixelManipulation::setRGBA<RGBA32Pixel>(const unsigned char &r, const unsigned char &g, const unsigned char &b, const unsigned char &a)
// {  ... }
//------------------------------------------------------------------------------

//==============================================================================
// CLASS PixelManipulation
//==============================================================================
class PixelManipulation
{
public:
	template<typename COMPONENT_STORAGE>
	static void setRGB(COMPONENT_STORAGE &storage, const typename COMPONENT_STORAGE::ComponentType &r, const typename COMPONENT_STORAGE::ComponentType &g, const typename COMPONENT_STORAGE::ComponentType &b)
	{
		setRed(storage, r);
		setGreen(storage, g);
		setBlue(storage, b);
	}

	template<typename COMPONENT_STORAGE>
	static void setRGBA(COMPONENT_STORAGE &storage, const typename COMPONENT_STORAGE::ComponentType &r, const typename COMPONENT_STORAGE::ComponentType &g, const typename COMPONENT_STORAGE::ComponentType &b, const typename COMPONENT_STORAGE::ComponentType &a)
	{
		setRGB(storage, r, g, b);
		setAlpha(storage, a);
	}

	template<typename COMPONENT_STORAGE>
	static const typename COMPONENT_STORAGE::ComponentType red(const COMPONENT_STORAGE &storage)
	{
		return storage.red();
	}

	template<typename COMPONENT_STORAGE>
	static const typename COMPONENT_STORAGE::ComponentType green(const COMPONENT_STORAGE &storage)
	{
		return storage.green();
	}

	template<typename COMPONENT_STORAGE>
	static const typename COMPONENT_STORAGE::ComponentType blue(const COMPONENT_STORAGE &storage)
	{
		return storage.blue();
	}

	template<typename COMPONENT_STORAGE>
	static void setRed(COMPONENT_STORAGE &storage, const typename COMPONENT_STORAGE::ComponentType &val)
	{
		storage.setRed(val);
	}

	template<typename COMPONENT_STORAGE>
	static void setGreen(COMPONENT_STORAGE &storage, const typename COMPONENT_STORAGE::ComponentType &val)
	{
		storage.setGreen(val);
	}

	template<typename COMPONENT_STORAGE>
	static void setBlue(COMPONENT_STORAGE &storage, const typename COMPONENT_STORAGE::ComponentType &val)
	{
		storage.setBlue(val);
	}

public:
	template<typename COMPONENT_STORAGE>
	static void setYCbYCr(COMPONENT_STORAGE &storage, const typename COMPONENT_STORAGE::ComponentType &y0, const typename COMPONENT_STORAGE::ComponentType &cb, const typename COMPONENT_STORAGE::ComponentType &y1, const typename COMPONENT_STORAGE::ComponentType &cr)
	{
		setLuminance0(storage, y0);
		setChromaBlue(storage, cb);
		setLuminance1(storage, y1);
		setChromaRed(storage, cr);
	}

	template<typename COMPONENT_STORAGE>
	static void setYCbCr(COMPONENT_STORAGE &storage, const typename COMPONENT_STORAGE::ComponentType &y, const typename COMPONENT_STORAGE::ComponentType &cb, const typename COMPONENT_STORAGE::ComponentType &cr)
	{
		setLuminance(storage, y);
		setChromaBlue(storage, cb);
		setChromaRed(storage, cr);
	}

	template<typename COMPONENT_STORAGE>
	static void setYCbCrA(COMPONENT_STORAGE &storage, const typename COMPONENT_STORAGE::ComponentType &y, const typename COMPONENT_STORAGE::ComponentType &cb, const typename COMPONENT_STORAGE::ComponentType &cr, const typename COMPONENT_STORAGE::ComponentType &a)
	{
		setLuminance(storage, y);
		setChromaBlue(storage, cb);
		setChromaRed(storage, cr);
		setAlpha(storage, a);
	}

	template<typename COMPONENT_STORAGE>
	static const typename COMPONENT_STORAGE::ComponentType luminance(const COMPONENT_STORAGE &storage)
	{
		return storage.luminance();
	}

	template<typename COMPONENT_STORAGE>
	static const typename COMPONENT_STORAGE::ComponentType luminance0(const COMPONENT_STORAGE &storage)
	{
		return storage.luminance0();
	}

	template<typename COMPONENT_STORAGE>
	static const typename COMPONENT_STORAGE::ComponentType luminance1(const COMPONENT_STORAGE &storage)
	{
		return storage.luminance1();
	}

	template<typename COMPONENT_STORAGE>
	static const typename COMPONENT_STORAGE::ComponentType chromaBlue(const COMPONENT_STORAGE &storage)
	{
		return storage.chromaBlue();
	}

	template<typename COMPONENT_STORAGE>
	static const typename COMPONENT_STORAGE::ComponentType chromaRed(const COMPONENT_STORAGE &storage)
	{
		return storage.chromaRed();
	}

	template<typename COMPONENT_STORAGE>
	static void setLuminance(COMPONENT_STORAGE &storage, const typename COMPONENT_STORAGE::ComponentType &val)
	{
		storage.setLuminance(val);
	}

	template<typename COMPONENT_STORAGE>
	static void setLuminance0(COMPONENT_STORAGE &storage, const typename COMPONENT_STORAGE::ComponentType &val)
	{
		storage.setLuminance0(val);
	}

	template<typename COMPONENT_STORAGE>
	static void setLuminance1(COMPONENT_STORAGE &storage, const typename COMPONENT_STORAGE::ComponentType &val)
	{
		storage.setLuminance1(val);
	}

	template<typename COMPONENT_STORAGE>
	static void setChromaBlue(COMPONENT_STORAGE &storage, const typename COMPONENT_STORAGE::ComponentType &val)
	{
		storage.setChromaBlue(val);
	}

	template<typename COMPONENT_STORAGE>
	static void setChromaRed(COMPONENT_STORAGE &storage, const typename COMPONENT_STORAGE::ComponentType &val)
	{
		storage.setChromaRed(val);
	}

public:
	template<typename COMPONENT_STORAGE>
	static void setCMYKA(COMPONENT_STORAGE &storage, const typename COMPONENT_STORAGE::ComponentType &c, const typename COMPONENT_STORAGE::ComponentType &m, const typename COMPONENT_STORAGE::ComponentType &y, const typename COMPONENT_STORAGE::ComponentType &k, const typename COMPONENT_STORAGE::ComponentType &a)
	{
		setCyan(storage, c);
		setMagenta(storage, m);
		setYellow(storage, y);
		setBlack(storage, k);
		setAlpha(storage, a);
	}

	template<typename COMPONENT_STORAGE>
	static void setCMYK(COMPONENT_STORAGE &storage, const typename COMPONENT_STORAGE::ComponentType &c, const typename COMPONENT_STORAGE::ComponentType &m, const typename COMPONENT_STORAGE::ComponentType &y, const typename COMPONENT_STORAGE::ComponentType &k)
	{
		setCyan(storage, c);
		setMagenta(storage, m);
		setYellow(storage, y);
		setBlack(storage, k);
	}

	template<typename COMPONENT_STORAGE>
	static void setCMY(COMPONENT_STORAGE &storage, const typename COMPONENT_STORAGE::ComponentType &c, const typename COMPONENT_STORAGE::ComponentType &m, const typename COMPONENT_STORAGE::ComponentType &y)
	{
		setCyan(storage, c);
		setMagenta(storage, m);
		setYellow(storage, y);
	}

	template<typename COMPONENT_STORAGE>
	static void setCMYA(COMPONENT_STORAGE &storage, const typename COMPONENT_STORAGE::ComponentType &c, const typename COMPONENT_STORAGE::ComponentType &m, const typename COMPONENT_STORAGE::ComponentType &y, const typename COMPONENT_STORAGE::ComponentType &a)
	{
		setCMY(storage, c, m, y);
		setAlpha(storage, a);
	}

	template<typename COMPONENT_STORAGE>
	static const typename COMPONENT_STORAGE::ComponentType cyan(const COMPONENT_STORAGE &storage)
	{
		return storage.cyan();
	}

	template<typename COMPONENT_STORAGE>
	static const typename COMPONENT_STORAGE::ComponentType magenta(const COMPONENT_STORAGE &storage)
	{
		return storage.magenta();
	}

	template<typename COMPONENT_STORAGE>
	static const typename COMPONENT_STORAGE::ComponentType yellow(const COMPONENT_STORAGE &storage)
	{
		return storage.yellow();
	}

	template<typename COMPONENT_STORAGE>
	static const typename COMPONENT_STORAGE::ComponentType black(const COMPONENT_STORAGE &storage)
	{
		return storage.black();
	}

	template<typename COMPONENT_STORAGE>
	static void setCyan(COMPONENT_STORAGE &storage, const typename COMPONENT_STORAGE::ComponentType &val)
	{
		storage.setCyan(val);
	}

	template<typename COMPONENT_STORAGE>
	static void setMagenta(COMPONENT_STORAGE &storage, const typename COMPONENT_STORAGE::ComponentType &val)
	{
		storage.setMagenta(val);
	}

	template<typename COMPONENT_STORAGE>
	static void setYellow(COMPONENT_STORAGE &storage, const typename COMPONENT_STORAGE::ComponentType &val)
	{
		storage.setYellow(val);
	}

	template<typename COMPONENT_STORAGE>
	static void setBlack(COMPONENT_STORAGE &storage, const typename COMPONENT_STORAGE::ComponentType &val)
	{
		storage.setBlack(val);
	}

public:
	template<typename COMPONENT_STORAGE>
	static const typename COMPONENT_STORAGE::ComponentType alpha(const COMPONENT_STORAGE &storage)
	{
		return storage.alpha();
	}

	template<typename COMPONENT_STORAGE>
	static void setAlpha(COMPONENT_STORAGE &storage, const typename COMPONENT_STORAGE::ComponentType &val)
	{
		storage.setAlpha(val);
	}
	
public:
	template<typename COMPONENT_STORAGE>
	static void setXYZ(COMPONENT_STORAGE &storage, const typename COMPONENT_STORAGE::ComponentType &x, const typename COMPONENT_STORAGE::ComponentType &y, const typename COMPONENT_STORAGE::ComponentType &z)
	{
		setX(storage, x);
		setY(storage, y);
		setZ(storage, z);
	}

	template<typename COMPONENT_STORAGE>
	static const typename COMPONENT_STORAGE::ComponentType x(const COMPONENT_STORAGE &storage)
	{
		return storage.x();
	}

	template<typename COMPONENT_STORAGE>
	static const typename COMPONENT_STORAGE::ComponentType y(const COMPONENT_STORAGE &storage)
	{
		return storage.y();
	}

	template<typename COMPONENT_STORAGE>
	static const typename COMPONENT_STORAGE::ComponentType z(const COMPONENT_STORAGE &storage)
	{
		return storage.z();
	}

	template<typename COMPONENT_STORAGE>
	static void setX(COMPONENT_STORAGE &storage, const typename COMPONENT_STORAGE::ComponentType &val)
	{
		storage.setX(val);
	}

	template<typename COMPONENT_STORAGE>
	static void setY(COMPONENT_STORAGE &storage, const typename COMPONENT_STORAGE::ComponentType &val)
	{
		storage.setY(val);
	}

	template<typename COMPONENT_STORAGE>
	static void setZ(COMPONENT_STORAGE &storage, const typename COMPONENT_STORAGE::ComponentType &val)
	{
		storage.setZ(val);
	}
	
	template<typename COMPONENT_STORAGE_LHS, typename COMPONENT_STORAGE_RHS>
	static inline void copy(COMPONENT_STORAGE_LHS &lhs, const COMPONENT_STORAGE_RHS &rhs);
};


#endif // __ITL_PIXELMANIPULATION_H__
