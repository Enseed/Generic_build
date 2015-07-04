/*******************************************************************************
 Copyright 2009 Gaspard Petit
 
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
#ifndef __ITL_PIXMAPORIGIN_H__
#define __ITL_PIXMAPORIGIN_H__

//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================
#include "PixMap.declare.h"
#include "PixelIterator.h"
#include "PixRowRef.h"
#include "PixRowIterator.h"


//==============================================================================
// GENERIC NAMESPACE
//==============================================================================
namespace ITL {

template<typename PIXELPACKET>
class PixMapOriginBase
{
public:
	typedef class PixRowRef<const PIXELPACKET> ConstPixRowRef;
	typedef class PixRowRef<PIXELPACKET> PixRowRef;

	typedef PixRowIterator<PIXELPACKET> RowIterator;
	typedef PixRowIterator<const PIXELPACKET> ConstRowIterator;

	typedef ReverseIteratorAdaptor<PixRowIterator<PIXELPACKET> > ReverseRowIterator;
	typedef ReverseIteratorAdaptor<PixRowIterator<const PIXELPACKET> > ConstReverseRowIterator;
};

template<typename PIXELPACKET, typename ORIGIN>
class PixMapOrigin {};

template<typename PIXELPACKET>
class PixMapOrigin<PIXELPACKET, PixMapDrawsFromBottom>: public PixMapOriginBase<PIXELPACKET>
{
private:
	typedef PixMapOriginBase<PIXELPACKET> _Super;
public:
	typedef typename _Super::ReverseRowIterator ReverseRowIterator;
	typedef typename _Super::ConstReverseRowIterator ConstReverseRowIterator;

	typedef typename _Super::RowIterator RowIterator;
	typedef typename _Super::ConstRowIterator ConstRowIterator;
	
	typedef typename _Super::PixRowRef PixRowRef;
	typedef typename _Super::ConstPixRowRef ConstPixRowRef;

	typedef ReverseRowIterator TopToBottomIterator;
	typedef ConstReverseRowIterator ConstTopToBottomIterator;

	typedef RowIterator BottomToTopIterator;
	typedef ConstRowIterator ConstBottomToTopIterator;
	
	static TopToBottomIterator beginFromTop(const PixRowRef &firstRow, int height)
	{	return TopToBottomIterator(firstRow) - height; }

//	static ConstTopToBottomIterator beginFromTop(const ConstPixRowRef &firstRow, int height)
//	{	return TopToBottomIterator(firstRow) - height; }

	static BottomToTopIterator beginFromBottom(const PixRowRef &firstRow, int height)
	{	return BottomToTopIterator(firstRow); }

//	static ConstBottomToTopIterator beginFromBottom(const ConstPixRowRef &firstRow, int height)
//	{	return ConstBottomToTopIterator(firstRow); }

	static TopToBottomIterator endFromTop(const PixRowRef &firstRow, int height)
	{	return TopToBottomIterator(firstRow); }

//	static ConstTopToBottomIterator endFromTop(const ConstPixRowRef &firstRow, int height)
//	{	return TopToBottomIterator(firstRow); }

	static BottomToTopIterator endFromBottom(const PixRowRef &firstRow, int height)
	{	return BottomToTopIterator(firstRow) + height; }

//	static ConstBottomToTopIterator endFromBottom(const ConstPixRowRef &firstRow, int height)
//	{	return ConstBottomToTopIterator(firstRow) + height; }
};

template<typename PIXELPACKET>
class PixMapOrigin<PIXELPACKET, PixMapDrawsFromTop>: public PixMapOriginBase<PIXELPACKET>
{
private:
	typedef PixMapOriginBase<PIXELPACKET> _Super;

public:
	typedef typename _Super::ReverseRowIterator ReverseRowIterator;
	typedef typename _Super::ConstReverseRowIterator ConstReverseRowIterator;
	
	typedef typename _Super::RowIterator RowIterator;
	typedef typename _Super::ConstRowIterator ConstRowIterator;
	
	typedef typename _Super::PixRowRef PixRowRef;
	typedef typename _Super::ConstPixRowRef ConstPixRowRef;

	typedef RowIterator TopToBottomIterator;
	typedef ConstRowIterator ConstTopToBottomIterator;

	typedef ReverseRowIterator BottomToTopIterator;
	typedef ConstReverseRowIterator ConstBottomToTopIterator;

	static TopToBottomIterator beginFromTop(const PixRowRef &firstRow, int height)
	{	return TopToBottomIterator(firstRow); }

//	static ConstTopToBottomIterator beginFromTop(const ConstPixRowRef &firstRow, int height)
//	{	return ConstTopToBottomIterator(firstRow); }

	static BottomToTopIterator beginFromBottom(const PixRowRef &firstRow, int height)
	{	return endFromBottom(firstRow, height) - height; }

//	static ConstBottomToTopIterator beginFromBottom(const ConstPixRowRef &firstRow, int height)
//	{	return endFromBottom(firstRow, height) - height; }

	static TopToBottomIterator endFromTop(const PixRowRef &firstRow, int height)
	{	return TopToBottomIterator(firstRow) + height; }

//	static ConstTopToBottomIterator endFromTop(const ConstPixRowRef &firstRow, int height)
//	{	return ConstTopToBottomIterator(firstRow) + height; }

	static BottomToTopIterator endFromBottom(const PixRowRef &firstRow, int height)
	{	return BottomToTopIterator(firstRow); }

//	static ConstBottomToTopIterator endFromBottom(const ConstPixRowRef &firstRow, int height)
//	{	return ConstBottomToTopIterator(firstRow); }
};

}

#endif // __ITL_PIXMAPORIGIN_H__
