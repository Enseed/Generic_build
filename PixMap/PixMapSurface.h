
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
#ifndef __ITL_PIXMAPSURFACE_H__
#define __ITL_PIXMAPSURFACE_H__

//==============================================================================
// FILE PixMapSurface.h
//==============================================================================
// Holds the actual buffer(s) for the PixMap.  For each plane, a PixMapPlane
// will be used to allocate the required amount of memory.
//------------------------------------------------------------------------------

//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================
#include "PixelIterator.h"
#include "PixRowRef.h"
#include "PixRowIterator.h"
#include "PixMapOrigin.h"
#include "PixPlane.h"

//==============================================================================
// ITL NAMESPACE
//==============================================================================
namespace ITL {

//==============================================================================
// CLASS PixMapSurfaceBase
//==============================================================================
template<class PIXELPACKET>
class PixMapSurfaceBase
{
public:
	PixMapSurfaceBase(int width, int height)
	:
		_width(width),
		_height(height)
	{}

	void resize(int width, int height)
	{
		_width = width;
		_height = height;
	}

public:
	int width() const { return _width; }
	int height() const { return _height; }
	int planes() const { return PIXELPACKET::PLANE_COUNT; }

protected:
	int _width;
	int _height;
};

template<class PIXELPACKET, int PLANECOUNT=PIXELPACKET::PLANE_COUNT>
class PixMapRowByteDescription;

template<class PIXELPACKET>
class PixMapRowByteDescription<PIXELPACKET, 1>
{
public:
	PixMapRowByteDescription(int rb0) : _rb(rb0) {}
	int rowBytes() const { return _rb; }

private:
	int _rb;
};

template<class PIXELPACKET>
class PixMapRowByteDescription<PIXELPACKET, 3>
{
public:
	PixMapRowByteDescription(int rb0, int rb1, int rb2) : _rb0(rb0), _rb1(rb1), _rb2(rb2) {}
	
	int rowBytes0() const { return _rb0; }
	int rowBytes1() const { return _rb1; }
	int rowBytes2() const { return _rb2; }

private:
	int _rb0;
	int _rb1;
	int _rb2;
};

//==============================================================================
// CLASS PixMapSurface
//==============================================================================
template<class PIXELPACKET, int PLANECOUNT=PIXELPACKET::PLANE_COUNT>
class PixMapSurface;

//------------------------------------------------------------------------------
// CLASS PixMapSurface - for 1 plane
//------------------------------------------------------------------------------
template<class PIXELPACKET>
class PixMapSurface<PIXELPACKET, 1>: public PixMapSurfaceBase<PIXELPACKET>
{
private:
	typedef PixMapSurfaceBase<PIXELPACKET> _Super;
	typedef PixMapPlane<PIXELPACKET, 0> Plane0Type;

public:
	PixMapSurface(int width, int height)
	:
		PixMapSurfaceBase<PIXELPACKET>(width, height),
		_plane0(width, height)
	{}

	PixMapSurface(int width, int height, const PixMapRowByteDescription<PIXELPACKET> &rowByteDesc)
	:
		PixMapSurfaceBase<PIXELPACKET>(width, height),
		_plane0(width, height, rowByteDesc.rowBytes())
	{}

	void resize(int width, int height)
	{ _plane0.resize(width, height); }

	size_t size()
	{ return _plane0.rowBytes()*_Super::height(); }

public:
	Plane0Type& plane0()			 { return _plane0; }
	const Plane0Type& plane0() const { return _plane0; }

	PixRowRef<PIXELPACKET> firstRow()
	{ return PixRowRef<PIXELPACKET>(firstPixel(), _Super::width(), _plane0.rowBytes()); }

	PixelRef<PIXELPACKET> firstPixel()
	{ return PixelRef<PIXELPACKET>(_plane0.baseAddr()); }

private:
	Plane0Type _plane0;
};

//------------------------------------------------------------------------------
// CLASS PixMapSurface - for 3 planes
//------------------------------------------------------------------------------
template<class PIXELPACKET>
class PixMapSurface<PIXELPACKET, 3>: public PixMapSurfaceBase<PIXELPACKET>
{
private:
	typedef PixMapSurfaceBase<PIXELPACKET> _Super;
private:
	typedef PixMapPlane<PIXELPACKET, 0> Plane0Type;
	typedef PixMapPlane<PIXELPACKET, 1> Plane1Type;
	typedef PixMapPlane<PIXELPACKET, 2> Plane2Type;

public:
	PixMapSurface(int width, int height)
	:
		_Super(width, height),
		_plane0(width, height),
		_plane1(width, height),
		_plane2(width, height)
	{}

	PixMapSurface(int width, int height, const PixMapRowByteDescription<PIXELPACKET> &rowByteDesc)
	:
		_Super(width, height),
		_plane0(width, height, rowByteDesc.rowBytes0()),
		_plane1(width, height, rowByteDesc.rowBytes1()),
		_plane2(width, height, rowByteDesc.rowBytes2())
	{}

	void resize(int width, int height)
	{
		_Super::resize(width, height);
		_plane0.resize(width, height);
		_plane1.resize(width, height);
		_plane2.resize(width, height);
	}

	size_t size()
	{ return (_plane0.rowBytes() + _plane1.rowBytes() + _plane2.rowBytes())*_Super::height(); }

	PixRowRef<PIXELPACKET> firstRow()
	{ return PixRowRef<PIXELPACKET>(firstPixel(), _Super::width(), _plane0.rowBytes(), _plane1.rowBytes(), _plane2.rowBytes()); }

	PixelRef<PIXELPACKET> firstPixel()
	{ return PixelRef<PIXELPACKET>(_plane0.baseAddr(), _plane1.baseAddr(), _plane2.baseAddr()); }

public:
	Plane0Type& plane0()			 { return _plane0; }
	const Plane0Type& plane0() const { return _plane0; }

	Plane1Type& plane1()			 { return _plane1; }
	const Plane1Type& plane1() const { return _plane1; }

	Plane2Type& plane2()			 { return _plane2; }
	const Plane2Type& plane2() const { return _plane2; }

private:
	Plane0Type _plane0;
	Plane1Type _plane1;
	Plane2Type _plane2;
};

//------------------------------------------------------------------------------
// CLASS PixMapSurface - for 4 planes
//------------------------------------------------------------------------------
template<class PIXELPACKET>
class PixMapSurface<PIXELPACKET, 4>: public PixMapSurfaceBase<PIXELPACKET>
{
private:
	typedef PixMapSurfaceBase<PIXELPACKET> _Super;
private:
	typedef PixMapPlane<PIXELPACKET, 0> Plane0Type;
	typedef PixMapPlane<PIXELPACKET, 1> Plane1Type;
	typedef PixMapPlane<PIXELPACKET, 2> Plane2Type;
	typedef PixMapPlane<PIXELPACKET, 3> Plane3Type;

public:
	PixMapSurface(int width, int height)
	:
		_Super(width, height),
		_plane0(width, height),
		_plane1(width, height),
		_plane2(width, height),
		_plane3(width, height)
	{}

	PixMapSurface(int width, int height, const PixMapRowByteDescription<PIXELPACKET> &rowByteDesc)
	:
		_Super(width, height),
		_plane0(width, height, rowByteDesc.rowBytes0()),
		_plane1(width, height, rowByteDesc.rowBytes1()),
		_plane2(width, height, rowByteDesc.rowBytes2()),
		_plane3(width, height, rowByteDesc.rowBytes3())
	{}

		void resize(int width, int height)
	{
		_Super::resize(width, height);
		_plane0.resize(width, height);
		_plane1.resize(width, height);
		_plane2.resize(width, height);
		_plane3.resize(width, height);
	}

	size_t size()
	{ return (_plane0.rowBytes() + _plane1.rowBytes() + _plane2.rowBytes() + _plane3.rowBytes())*_Super::height(); }

	PixRowRef<PIXELPACKET> firstRow()
	{ return PixRowRef<PIXELPACKET>(firstPixel(), _Super::width(), _plane0.rowBytes(), _plane1.rowBytes(), _plane2.rowBytes(), _plane3.rowBytes()); }

	PixelRef<PIXELPACKET> firstPixel()
	{ return PixelRef<PIXELPACKET>(_plane0.baseAddr(), _plane1.baseAddr(), _plane2.baseAddr(), _plane3.baseAddr()); }

public:
	Plane0Type& plane0()			 { return _plane0; }
	const Plane0Type& plane0() const { return _plane0; }

	Plane1Type& plane1()			 { return _plane1; }
	const Plane1Type& plane1() const { return _plane1; }

	Plane2Type& plane2()			 { return _plane2; }
	const Plane2Type& plane2() const { return _plane2; }

	Plane3Type& plane3()			 { return _plane3; }
	const Plane3Type& plane3() const { return _plane3; }

private:
	Plane0Type _plane0;
	Plane1Type _plane1;
	Plane2Type _plane2;
	Plane3Type _plane3;
};

}

#endif // __ITL_PIXMAPSURFACE_H__
