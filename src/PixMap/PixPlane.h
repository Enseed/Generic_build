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
#ifndef __ITL_PIXPLANE_H__
#define __ITL_PIXPLANE_H__

//==============================================================================
// FILE PixPlane.h
//==============================================================================
// Holds the data for a single pixel plane
//------------------------------------------------------------------------------

//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================
#include "PixelIterator.h"
#include "PixRowRef.h"
#include "PixRowIterator.h"
#include "PixMapOrigin.h"

//==============================================================================
// ITL NAMESPACE
//==============================================================================
#ifdef ITL_NAMESPACE
namespace ITL_NAMESPACE {
#endif

//==============================================================================
// CLASS PixMapPlaneBase
//==============================================================================
template<int PIXEL_PER_PACKET, int BYTES_PER_PACKET, class PTRTYPE>
class PixMapPlaneBase
{
public:
	PixMapPlaneBase() : _baseAddr(0), _rowBytes(0) {}
	PixMapPlaneBase(int width, int height, int rowBytes) : _baseAddr(0), _rowBytes(0) { resize(width, height, rowBytes); }
	PixMapPlaneBase(int width, int height) : _baseAddr(0), _rowBytes(0) { resize(width, height); }

	~PixMapPlaneBase()
	{ if (_baseAddr) free(_baseAddr); }

	static int packetPerRow(int width)
	{ return (width+PIXEL_PER_PACKET-1)/PIXEL_PER_PACKET; }

	void resize(int width, int height)
	{
		int rowBytes = packetPerRow(width)*BYTES_PER_PACKET;
		resize(width, height, rowBytes);
	}

	void resize(int width, int height, int rowBytes)
	{
		_baseAddr = realloc(_baseAddr, height*rowBytes);
		_rowBytes = rowBytes;
	}

	PTRTYPE *baseAddr() { return reinterpret_cast<PTRTYPE*>(_baseAddr); }
	const PTRTYPE *baseAddr() const { return reinterpret_cast<const PTRTYPE*>(_baseAddr); }
	int rowBytes() const  { return _rowBytes; }

private:
	void *_baseAddr;
	int _rowBytes;
};

//==============================================================================
// CLASS PixMapPlane
//==============================================================================
template <class PIXELPACKET, int PLANEINDEX>
class PixMapPlane;

//------------------------------------------------------------------------------
// CLASS PixMapPlane - for the first index (index = 0)
//------------------------------------------------------------------------------
template <class PIXELPACKET>
class PixMapPlane<PIXELPACKET, 0>: public PixMapPlaneBase<PIXELPACKET::PIXEL_PER_PACKET, PIXELPACKET::Plane0Storage::BYTES_PER_PACKET, typename PIXELPACKET::Plane0Storage::ComponentType>
{
	typedef PixMapPlaneBase<PIXELPACKET::PIXEL_PER_PACKET, PIXELPACKET::Plane0Storage::BYTES_PER_PACKET, typename PIXELPACKET::Plane0Storage::ComponentType> _Super;

public:
	PixMapPlane() : _Super() {}
	PixMapPlane(int width, int height, int rowBytes) : _Super(width, height, rowBytes) {}
	PixMapPlane(int width, int height) : _Super(width, height) {}
};


//------------------------------------------------------------------------------
// CLASS PixMapPlane - for the second index (index = 1)
//------------------------------------------------------------------------------
template <class PIXELPACKET>
class PixMapPlane<PIXELPACKET, 1>: public PixMapPlaneBase<PIXELPACKET::PIXEL_PER_PACKET, PIXELPACKET::Plane1Storage::BYTES_PER_PACKET, typename PIXELPACKET::Plane1Storage::ComponentType>
{
	typedef PixMapPlaneBase<PIXELPACKET::PIXEL_PER_PACKET, PIXELPACKET::Plane1Storage::BYTES_PER_PACKET, typename PIXELPACKET::Plane1Storage::ComponentType> _Super;

public:
	PixMapPlane() : _Super() {}
	PixMapPlane(int width, int height, int rowBytes) : _Super(width, height, rowBytes) {}
	PixMapPlane(int width, int height) : _Super(width, height) {}
};

//------------------------------------------------------------------------------
// CLASS PixMapPlane - for the third index (index = 2)
//------------------------------------------------------------------------------
template <class PIXELPACKET>
class PixMapPlane<PIXELPACKET, 2>: public PixMapPlaneBase<PIXELPACKET::PIXEL_PER_PACKET, PIXELPACKET::Plane2Storage::BYTES_PER_PACKET, typename PIXELPACKET::Plane2Storage::ComponentType>
{
private:
	typedef PixMapPlaneBase<PIXELPACKET::PIXEL_PER_PACKET, PIXELPACKET::Plane2Storage::BYTES_PER_PACKET, typename PIXELPACKET::Plane2Storage::ComponentType> _Super;

public:
	PixMapPlane() : _Super() {}
	PixMapPlane(int width, int height, int rowBytes) : _Super(width, height, rowBytes) {}
	PixMapPlane(int width, int height) : _Super(width, height) {}
};

//------------------------------------------------------------------------------
// CLASS PixMapPlane - for the fourth index (index = 3)
//------------------------------------------------------------------------------
template <class PIXELPACKET>
class PixMapPlane<PIXELPACKET, 3>: public PixMapPlaneBase<PIXELPACKET::PIXEL_PER_PACKET, PIXELPACKET::Plane3Storage::BYTES_PER_PACKET, typename PIXELPACKET::Plane3Storage::ComponentType>
{
private:
	typedef PixMapPlaneBase<PIXELPACKET::PIXEL_PER_PACKET, PIXELPACKET::Plane3Storage::BYTES_PER_PACKET, typename PIXELPACKET::Plane3Storage::ComponentType> _Super;

public:
	PixMapPlane() : _Super() {}
	PixMapPlane(int width, int height, int rowBytes) : _Super(width, height, rowBytes) {}
	PixMapPlane(int width, int height) : _Super(width, height) {}
};

#ifdef ITL_NAMESPACE
}
#endif

#endif // __ITL_PIXPLANE_H__
