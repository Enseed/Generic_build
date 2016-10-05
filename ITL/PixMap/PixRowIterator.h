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
#ifndef __ITL_PIXROWITERATOR_H__
#define __ITL_PIXROWITERATOR_H__

//==============================================================================
// FILE PixRowIterator.h
//==============================================================================
// Iterates over the rows of a PixMap
//------------------------------------------------------------------------------

//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================
#include "PixelIterator.h"
#include "PixRowRef.h"
#include "../Utils/Iterator.h"

//==============================================================================
// ITL NAMESPACE
//==============================================================================
namespace ITL {

//==============================================================================
// CLASS PixRowIterator
//==============================================================================
template<typename PIXELPACKET>
class PixRowIterator: public IteratorBase<PixRowIterator<PIXELPACKET>, PixRowRef<PIXELPACKET>, PixRowRef<PIXELPACKET>*, PixRowRef<PIXELPACKET>*, PixRowRef<PIXELPACKET>&, PixRowRef<PIXELPACKET>& >
{
private:
	template<class> friend class PixRowIterator;
	typedef IteratorBase<PixRowIterator<PIXELPACKET>, PixRowRef<PIXELPACKET>, PixRowRef<PIXELPACKET>*, PixRowRef<PIXELPACKET>*, PixRowRef<PIXELPACKET>&, PixRowRef<PIXELPACKET>& > _Super;

public:
	template<class RHS_PIXELPACKET>
	PixRowIterator(const PixRowIterator<RHS_PIXELPACKET> &rhs) : _row(rhs._row) {}
	PixRowIterator(const PixRowRef<PIXELPACKET> &row) : _row(row) {}

public: // ITERATOR METHODS
	void advance(int nb) { _row.advance(nb); }
	bool equals(const PixRowIterator &rhs) const { return _row == rhs._row; }
	PixRowRef<PIXELPACKET>& dereference()  { return _row; }
	const PixRowRef<PIXELPACKET>& dereference() const  { return _row; }

private:
	PixRowRef<PIXELPACKET> _row;

public:
	PixRowIterator(const PixRowIterator &rhs)
	{
		_row = rhs._row;
	}

	PixRowIterator& operator=(const PixRowIterator &rhs)
	{
		_row = rhs._row;
		return *this;
	}
};


}

#endif // __ITL_PIXROWITERATOR_H__
