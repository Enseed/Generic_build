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
#ifndef __ITL_PIXELITERATOR_H__
#define __ITL_PIXELITERATOR_H__

//==============================================================================
// FILE PixelIterator.h
//==============================================================================
// Iterate over pixels
//
// USAGE:
//    RGB24Pixel rgb[10];
//    PixelIterator<RGB24Pixel> begin(&rgb[0]);
//    PixelIterator<RGB24Pixel> end(&rgb[10]);
//    for (PixelIterator<RGB24Pixel> iter = begin; iter != end; ++iter)
//        iter->setRGB(1, 2, 3);
//
//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================
#include "../Utils/Iterator.h"
#include "../PixMap/PixelRef.h"

namespace ITL {

//==============================================================================
// CLASS PixelIterator
//==============================================================================
template<typename PIXELPACKET, int PLANECOUNT=PIXELPACKET::PLANE_COUNT>
class PixelIterator: public IteratorBase<PixelIterator<PIXELPACKET>, PIXELPACKET, PIXELPACKET*, PIXELPACKET*, PIXELPACKET, PIXELPACKET >
{
private:
	typedef IteratorBase<PixelIterator<PIXELPACKET>, PIXELPACKET, PIXELPACKET*, PIXELPACKET*, PIXELPACKET, PIXELPACKET > _Super;
public:
	PixelIterator(const PixelRef<PIXELPACKET> &ref) : _ref(ref) {}

	PIXELPACKET dereference() { return *_ref; }
	const PIXELPACKET dereference() const { return *_ref; }

	void advance(int nb)	{ _ref.advance(nb); }

	bool equals(const PixelIterator &rhs) const
	{
		return _ref == rhs._ref;
	}
private:
	PixelRef<PIXELPACKET> _ref;

public:
	PixelIterator(const PixelIterator &rhs)
	{
		_ref = rhs._ref;
	}

	PixelIterator& operator=(const PixelIterator &rhs)
	{
		_ref = rhs._ref;
	}
};

//------------------------------------------------------------------------------
// CLASS PixelIterator - Special case for 1 pixel plane
//------------------------------------------------------------------------------
// When we only have 1 plane, the data is the actual pixel, not a reference
// to a pixel.  We can't do this with planar representations since the iterator
// has to return a pointer to the component of each planes. This breaks
// the symmetry with multi planar code, but it's more convenient with single
// plane pixmaps - and this is the most common case...
template<typename PIXELPACKET>
class PixelIterator<PIXELPACKET, 1>: public IteratorBase<PixelIterator<PIXELPACKET>, PIXELPACKET, PIXELPACKET*, PIXELPACKET*, PIXELPACKET&, PIXELPACKET& >
{
private:
	typedef IteratorBase<PixelIterator<PIXELPACKET>, PIXELPACKET, PIXELPACKET*, PIXELPACKET*, PIXELPACKET&, PIXELPACKET& > _Super;
public:
	PixelIterator(const PixelRef<PIXELPACKET> &ref) : _ref(ref) {}

	PIXELPACKET& dereference() { return *_ref; }
	const PIXELPACKET& dereference() const { return *_ref; }

	void advance(int nb)	{ _ref.advance(nb); }

	bool equals(const PixelIterator &rhs) const
	{
		return _ref == rhs._ref;
	}
private:
	PixelRef<PIXELPACKET> _ref;

public:
	PixelIterator(const PixelIterator &rhs)
	{
		_ref = rhs._ref;
	}

	PixelIterator& operator=(const PixelIterator &rhs)
	{
		_ref = rhs._ref;
	}
};


}

#endif // __ITL_PIXELITERATOR_H__
