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
#ifndef __ITL_PIXROWREF_H__
#define __ITL_PIXROWREF_H__

//==============================================================================
// FILE PixRowRef
//==============================================================================
// Reference to a row in a pixmap
//------------------------------------------------------------------------------

		// FIXME:
		// PIXELPACKET::Plane0Storage::ComponentType is not const when 
		// PIXELPACKET is const. As a result, we have to use const_casts
		// in order to increment our row (see advance()).

//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================
#include "PixelIterator.h"
#include "../Utils/Iterator.h"
#include "../Utils/PtrManip.h"

//==============================================================================
// ITL NAMESPACE
//==============================================================================
namespace ITL {

template<typename PIXELPACKET, typename FUNCT, int PIXELPERPACKET = PIXELPACKET::PIXEL_PER_PACKET>
class ForEachPixelInPacketFunctor;

//==============================================================================
// CLASS PixRowRefBase
//==============================================================================
template<typename DERIVED, typename PIXELPACKET>
class PixRowRefBase
{
public:
	typedef class PixelRef<PIXELPACKET> PixelRef;
	typedef PixelIterator<PIXELPACKET> Iterator;
	typedef PixelIterator<const PIXELPACKET> ConstIterator;
	typedef ReverseIteratorAdaptor<Iterator> ReverseIterator;
	typedef ReverseIteratorAdaptor<ConstIterator> ConstReverseIterator;

	enum { PLANE_COUNT = PIXELPACKET::PLANE_COUNT };

public:
	PixRowRefBase()
	:
		_width(),
		_rowBegin()
	{}

	PixRowRefBase(const PixelRef &rowBegin, int width)
	:
		_width(width),
		_rowBegin(rowBegin)
	{}

	PixRowRefBase& operator=(const PixRowRefBase &rhs)
	{
		_rowBegin = rhs._rowBegin;
		_width = rhs._width;
		return *this;
	}

	typedef PIXELPACKET PixelType;

	int width() const { return _width; }
	int planes() const { return PLANE_COUNT; }

	bool operator!=(const DERIVED &rhs) const
	{  return _rowBegin != rhs._rowBegin; }

	bool operator==(const DERIVED &rhs) const
	{	return _rowBegin == rhs._rowBegin; }

public: // RANDOM ACCESS
	PIXELPACKET operator[](int x) { return *(begin() + x); }
	const PIXELPACKET operator[](int x) const { return *(begin() + x); }

public:
	Iterator begin() { return _rowBegin;  }
	Iterator end() { return begin() + (_width / PIXELPACKET::PIXEL_PER_PACKET); }

	ConstIterator begin() const { return ConstIterator(_rowBegin);  }
	ConstIterator end() const { return begin() + (_width / PIXELPACKET::PIXEL_PER_PACKET); }

public:
	ReverseIterator rbegin() { return rend()-(_width / PIXELPACKET::PIXEL_PER_PACKET);  }
	ReverseIterator rend() { return ReverseIterator(_rowBegin); }

	ConstReverseIterator rbegin() const { return rend()-(_width / PIXELPACKET::PIXEL_PER_PACKET);  }
	ConstReverseIterator rend() const { return _rowBegin; }

public:
	template<typename FUNCT>
	void forEachPacket(const FUNCT &funct)
	{
		for (Iterator iter = begin(); iter != end(); ++iter)
			funct(*iter);
	}

	template<typename FUNCT>
	void forEachPixel(const FUNCT &funct)
	{
		forEachPacket(ForEachPixelInPacketFunctor<PIXELPACKET, FUNCT>(funct));
	}

protected:
	int _width;
	PixelRef _rowBegin;
};

//==============================================================================
// CLASS PixRowRef 
//==============================================================================
template<class PIXELPACKET, int PLANECOUNT=PIXELPACKET::PLANE_COUNT>
class PixRowRef {};

//------------------------------------------------------------------------------
// CLASS PixRowRef  - for 1 plane
//------------------------------------------------------------------------------
template<typename PIXELPACKET>
class PixRowRef<PIXELPACKET, 1>: public PixRowRefBase<PixRowRef<PIXELPACKET, 1>, PIXELPACKET>
{
private:
	typedef PixRowRefBase<PixRowRef<PIXELPACKET, 1>, PIXELPACKET> _Super;
	template<typename, int> friend class PixRowRef;

public:
	typedef typename _Super::PixelRef PixelRef;

	PixRowRef()
	:
		_Super(),
		_rowBytes()
	{}

	PixRowRef(const PixelRef &rowBegin, int width, int rowBytes)
	:
		_Super(rowBegin, width),
		_rowBytes(rowBytes)
	{}

	template<typename RHS_PIXELPACKET>
	PixRowRef(const PixRowRef<RHS_PIXELPACKET, 1> &rhs)
	:
		_Super(rhs._rowBegin, rhs._width),
		_rowBytes(rhs._rowBytes)
	{}

public:
	PixRowRef& operator=(const PixRowRef &rhs)
	{
		_Super::operator=(rhs);
		_rowBytes = rhs._rowBytes;
		return *this;
	}

	void advance(int nb)
	{
		_Super::_rowBegin = PixelRef(PtrManip::advanceNBytes(baseAddr(), nb*_rowBytes));
	}

public: // RANDOM ACCESS
	// Override so we return a reference instead of a copy
	PIXELPACKET& operator[](int x)				{ return *(_Super::begin() + x); }
	const PIXELPACKET& operator[](int x) const	{ return *(_Super::begin() + x); }

	PIXELPACKET* plane()				{ return &*_Super::_rowBegin; }
	const PIXELPACKET* plane() const	{ return &*_Super::_rowBegin; }

	typename PIXELPACKET::Plane0Storage::ComponentType* baseAddr()				{	
		// FIXME
		return const_cast<typename PIXELPACKET::Plane0Storage::ComponentType*>(plane()->storage().ptr()); 
	}
	const typename PIXELPACKET::Plane0Storage::ComponentType* baseAddr() const 	{	return plane()->storage().ptr(); }

	int rowBytes() const { return _rowBytes; }
protected:
	int _rowBytes;
};

//------------------------------------------------------------------------------
// CLASS PixRowRef  - for 3 planes
//------------------------------------------------------------------------------
template<typename PIXELPACKET>
class PixRowRef<PIXELPACKET, 3>: public PixRowRefBase<PixRowRef<PIXELPACKET, 3>, PIXELPACKET>
{
private:
	typedef PixRowRefBase<PixRowRef<PIXELPACKET, 3>, PIXELPACKET> _Super;
	template<typename, int> friend class PixRowRef;

public:
	typedef typename _Super::PixelRef PixelRef;
	
	PixRowRef()
	:
		_Super(),
		_rowBytes0(),
		_rowBytes1(),
		_rowBytes2()
	{}	

	PixRowRef(const PixelRef &rowBegin, int width, int rowBytes0, int rowBytes1, int rowBytes2)
	:
		_Super(rowBegin, width),
		_rowBytes0(rowBytes0),
		_rowBytes1(rowBytes1),
		_rowBytes2(rowBytes2)
	{}

	template<typename RHS_PIXELPACKET>
	PixRowRef(const PixRowRef<RHS_PIXELPACKET, 3> &rhs)
	:
		_Super(rhs._rowBegin, rhs._width),
		_rowBytes0(rhs._rowBytes0),
		_rowBytes1(rhs._rowBytes1),
		_rowBytes2(rhs._rowBytes2)
	{}

public:
	PixRowRef& operator=(const PixRowRef &rhs)
	{
		_Super::operator=(rhs);
		_rowBytes0 = rhs._rowBytes0;
		_rowBytes1 = rhs._rowBytes1;
		_rowBytes2 = rhs._rowBytes2;
		return *this;
	}

	void advance(int nb)
	{
		typename PIXELPACKET::Plane0Storage::ComponentType *newAddr0 = PtrManip::advanceNBytes(baseAddr0(), nb*_rowBytes0);
		typename PIXELPACKET::Plane1Storage::ComponentType *newAddr1 = PtrManip::advanceNBytes(baseAddr1(), nb*_rowBytes1);
		typename PIXELPACKET::Plane2Storage::ComponentType *newAddr2 = PtrManip::advanceNBytes(baseAddr2(), nb*_rowBytes2);
		_Super::_rowBegin = PixelRef(newAddr0, newAddr1, newAddr2);
	}

	typename PIXELPACKET::Plane0Type::PacketType* plane0() {
		// FIXME
		return const_cast<typename PIXELPACKET::Plane0Type::PacketType*>(_Super::_rowBegin->plane0Ptr()); 
	}
	const typename PIXELPACKET::Plane0Type::PacketType* plane0() const	{ return _Super::_rowBegin->plane0Ptr(); } 

	typename PIXELPACKET::Plane1Type::PacketType* plane1() {
		// FIXME
		return const_cast<typename PIXELPACKET::Plane1Type::PacketType*>(_Super::_rowBegin->plane1Ptr());
	}
	const typename PIXELPACKET::Plane1Type::PacketType* plane1() const	{ return _Super::_rowBegin->plane1Ptr(); }

	typename PIXELPACKET::Plane2Type::PacketType* plane2() {
		// FIXME
		return const_cast<typename PIXELPACKET::Plane2Type::PacketType*>(_Super::_rowBegin->plane2Ptr());
	}
	const typename PIXELPACKET::Plane2Type::PacketType* plane2() const	{ return _Super::_rowBegin->plane2Ptr(); }

	int rowBytes0() const { return _rowBytes0; }
	int rowBytes1() const { return _rowBytes1; }
	int rowBytes2() const { return _rowBytes2; }

	typename PIXELPACKET::Plane0Storage::ComponentType* baseAddr0()				{	return plane0()->storage().ptr(); }
	const typename PIXELPACKET::Plane0Storage::ComponentType* baseAddr0() const {	return plane0()->storage().ptr(); }

	typename PIXELPACKET::Plane1Storage::ComponentType* baseAddr1()				{	return plane1()->storage().ptr(); }
	const typename PIXELPACKET::Plane1Storage::ComponentType* baseAddr1() const {	return plane1()->storage().ptr(); }

	typename PIXELPACKET::Plane2Storage::ComponentType* baseAddr2() 			{	return plane2()->storage().ptr(); }
	const typename PIXELPACKET::Plane2Storage::ComponentType* baseAddr2() const {	return plane2()->storage().ptr(); }
protected:
	int _rowBytes0;
	int _rowBytes1;
	int _rowBytes2;
};

//------------------------------------------------------------------------------
// CLASS PixRowRef  - for 4 planes
//------------------------------------------------------------------------------
template<typename PIXELPACKET>
class PixRowRef<PIXELPACKET, 4>: public PixRowRefBase<PixRowRef<PIXELPACKET, 4>, PIXELPACKET>
{
private:
	typedef PixRowRefBase<PixRowRef<PIXELPACKET, 4>, PIXELPACKET> _Super;
	template<typename, int> friend class PixRowRef;

public:
	typedef typename _Super::PixelRef PixelRef;
	
	PixRowRef(const PixelRef &rowBegin, int width, int rowBytes0, int rowBytes1, int rowBytes2, int rowBytes3)
	:
		_Super(rowBegin, width),
		_rowBytes0(rowBytes0),
		_rowBytes1(rowBytes1),
		_rowBytes2(rowBytes2),
		_rowBytes3(rowBytes3)
	{}

	template<typename RHS_PIXELPACKET>
	PixRowRef(const PixRowRef<RHS_PIXELPACKET, 4> &rhs)
	:
		_Super(rhs._rowBegin, rhs._width),
		_rowBytes0(rhs._rowBytes0),
		_rowBytes1(rhs._rowBytes1),
		_rowBytes2(rhs._rowBytes2),
		_rowBytes3(rhs._rowBytes3)
	{}

public:
	PixRowRef& operator=(const PixRowRef &rhs)
	{
		_Super::operator=(rhs);
		_rowBytes0 = rhs._rowBytes0;
		_rowBytes1 = rhs._rowBytes1;
		_rowBytes2 = rhs._rowBytes2;
		_rowBytes3 = rhs._rowBytes3;
		return *this;
	}

	void advance(int nb)
	{
		int bytesToSkip0 = nb*_rowBytes0;
		typename PIXELPACKET::Plane0Storage::ComponentType *baseAddr0 = const_cast<typename PIXELPACKET::Plane0Storage::ComponentType *>((*_Super::_rowBegin).plane0Ptr());
		typename PIXELPACKET::Plane0Storage::ComponentType *newAddr0 = PtrManip::advanceNBytes(baseAddr0, bytesToSkip0);

		int bytesToSkip1 = nb*_rowBytes1;
		typename PIXELPACKET::Plane1Storage::ComponentType *baseAddr1 = const_cast<typename PIXELPACKET::Plane1Storage::ComponentType *>((*_Super::_rowBegin).plane1Ptr());
		typename PIXELPACKET::Plane1Storage::ComponentType *newAddr1 = PtrManip::advanceNBytes(baseAddr1, bytesToSkip1);

		int bytesToSkip2 = nb*_rowBytes2;
		typename PIXELPACKET::Plane2Storage::ComponentType *baseAddr2 = const_cast<typename PIXELPACKET::Plane2Storage::ComponentType *>((*_Super::_rowBegin).plane2Ptr());
		typename PIXELPACKET::Plane2Storage::ComponentType *newAddr2 = PtrManip::advanceNBytes(baseAddr2, bytesToSkip2);

		int bytesToSkip3 = nb*_rowBytes3;
		typename PIXELPACKET::Plane2Storage::ComponentType *baseAddr3 = const_cast<typename PIXELPACKET::Plane3Storage::ComponentType *>((*_Super::_rowBegin).plane3Ptr());
		typename PIXELPACKET::Plane3Storage::ComponentType *newAddr3 = PtrManip::advanceNBytes(baseAddr3, bytesToSkip3);

		_Super::_rowBegin = PixelRef(newAddr0, newAddr1, newAddr2, newAddr3);
	}

	typename PIXELPACKET::Plane0Storage::ComponentType* baseAddr0()				{	return plane0()->storage().ptr(); }
	const typename PIXELPACKET::Plane0Storage::ComponentType* baseAddr0() const {	return plane0()->storage().ptr(); }

	typename PIXELPACKET::Plane1Storage::ComponentType* baseAddr1()				{	return plane1()->storage().ptr(); }
	const typename PIXELPACKET::Plane1Storage::ComponentType* baseAddr1() const {	return plane1()->storage().ptr(); }

	typename PIXELPACKET::Plane2Storage::ComponentType* baseAddr2() 			{	return plane2()->storage().ptr(); }
	const typename PIXELPACKET::Plane2Storage::ComponentType* baseAddr2() const {	return plane2()->storage().ptr(); }

	typename PIXELPACKET::Plane3Storage::ComponentType* baseAddr3() 			{	return plane3()->storage().ptr(); }
	const typename PIXELPACKET::Plane3Storage::ComponentType* baseAddr3() const {	return plane3()->storage().ptr(); }

	typename PIXELPACKET::Plane0Type::PacketType* plane0() 				{ return _Super::_rowBegin->plane0Ptr(); }
	const typename PIXELPACKET::Plane0Type::PacketType* plane0() const	{ return _Super::_rowBegin->plane0Ptr(); } 

	typename PIXELPACKET::Plane1Type::PacketType* plane1()				{ return _Super::_rowBegin->plane1Ptr(); }
	const typename PIXELPACKET::Plane1Type::PacketType* plane1() const	{ return _Super::_rowBegin->plane1Ptr(); }

	typename PIXELPACKET::Plane2Type::PacketType* plane2()				{ return _Super::_rowBegin->plane2Ptr(); }
	const typename PIXELPACKET::Plane2Type::PacketType* plane2() const	{ return _Super::_rowBegin->plane2Ptr(); }

	typename PIXELPACKET::Plane3Type::PacketType* plane3()				{ return _Super::_rowBegin->plane3Ptr(); }
	const typename PIXELPACKET::Plane3Type::PacketType* plane3() const	{ return _Super::_rowBegin->plane3Ptr(); }

	int rowBytes0() const { return _rowBytes0; }
	int rowBytes1() const { return _rowBytes1; }
	int rowBytes2() const { return _rowBytes2; }
	int rowBytes3() const { return _rowBytes3; }

protected:
	int _rowBytes0;
	int _rowBytes1;
	int _rowBytes2;
	int _rowBytes3;
};



template<typename PIXELPACKET, typename FUNCT>
class ForEachPixelInPacketFunctor<PIXELPACKET, FUNCT, 1>
{
public:
	ForEachPixelInPacketFunctor(const FUNCT &funct) : _funct(funct) {}
	void operator()(PIXELPACKET &packet) const
	{
		_funct(packet);
	}

	void operator()(const PIXELPACKET &packet) const
	{
		_funct(packet);
	}

private:
	const FUNCT &_funct;
};

template<typename PIXELPACKET, typename FUNCT>
class ForEachPixelInPacketFunctor<PIXELPACKET, FUNCT, 2>
{
public:
	ForEachPixelInPacketFunctor(const FUNCT &funct) : _funct(funct) {}
	void operator()(PIXELPACKET &packet) const
	{
		_funct(packet.pixel0());
		_funct(packet.pixel1());
	}

private:
	const FUNCT &_funct;
};

template<typename PIXELPACKET, typename FUNCT>
class ForEachPixelInPacketFunctor<PIXELPACKET, FUNCT, 3>
{
public:
	ForEachPixelInPacketFunctor(const FUNCT &funct) : _funct(funct) {}
	void operator()(PIXELPACKET &packet) const
	{
		_funct(packet.pixel0());
		_funct(packet.pixel1());
		_funct(packet.pixel2());
	}

private:
	const FUNCT &_funct;
};

template<typename PIXELPACKET, typename FUNCT>
class ForEachPixelInPacketFunctor<PIXELPACKET, FUNCT, 4>
{
public:
	ForEachPixelInPacketFunctor(const FUNCT &funct) : _funct(funct) {}
	void operator()(PIXELPACKET &packet) const
	{
		_funct(packet.pixel0());
		_funct(packet.pixel1());
		_funct(packet.pixel2());
		_funct(packet.pixel3());
	}

private:
	const FUNCT &_funct;
};


template<typename PIXELPACKET, typename FUNCT>
class ForEachPixelInPacketFunctor<PIXELPACKET, FUNCT, 8>
{
public:
	ForEachPixelInPacketFunctor(const FUNCT &funct) : _funct(funct) {}
	void operator()(PIXELPACKET &packet) const
	{
		_funct(packet.pixel0());
		_funct(packet.pixel1());
		_funct(packet.pixel2());
		_funct(packet.pixel3());
		_funct(packet.pixel4());
		_funct(packet.pixel5());
		_funct(packet.pixel6());
		_funct(packet.pixel7());
	}

private:
	const FUNCT &_funct;
};


}

#endif // __ITL_PIXROWREF_H__
