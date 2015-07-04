/*******************************************************************************
 Copyright 2009 Enseed,Inc & Gaspard Petit <gaspardpetit@enseed.com>
 
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
#ifndef __ITL_PIXELREF_H__
#define __ITL_PIXELREF_H__

//==============================================================================
// FILE: PixelRef.h
//==============================================================================
// This class is used as a glue to deal with the fact that planar pixel types
// are inherently different from packed pixel types.  Planar pixel types
// always hold a reference to a pixel (they hold a pointer to a number of data
// planes).  Packet pixels on the other hand, ARE they actual data.  Since
// we'd like to use the same kind of iterators for both types, we use the
// PixelRef to make all pixels as though they were references. This class
// is however specialized to support both cases (planar vs packet). As a result,
// these differences are almost transparent to the iterators.
//------------------------------------------------------------------------------

		// FIXME
		// This will have to be fixed, but for now, a const PIXELPACKET does
		// not return a const type under PIXELPACKET::Plane0Type which
		// makes the whole thing collapse when dealing with const pixels.
		// For that reason, there will be (ab)use of const_casts here and there

//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================
#include "../Utils/Iterator.h"
#include "../Utils/PtrManip.h"

namespace ITL {

//==============================================================================
// CLASS PixelRef
//==============================================================================
template<class PIXELPACKET, int PLANECOUNT=PIXELPACKET::PLANE_COUNT>
class PixelRef;

//------------------------------------------------------------------------------
// CLASS PixelRef - Special case for 1 plane (packed)
//------------------------------------------------------------------------------
template<class PIXELPACKET>
class PixelRef<PIXELPACKET, 1>
{
public:
	PixelRef() : _baseAddr(NULL) {}
	PixelRef(typename PIXELPACKET::ComponentType  *ptr) : _baseAddr(ptr) {}
	PixelRef(PIXELPACKET *ptr) : _baseAddr(reinterpret_cast<typename PIXELPACKET::ComponentType*>(ptr)) {}

	template<class RHS_PIXELPACKET>
	PixelRef(const PixelRef<RHS_PIXELPACKET> &rhs) : _baseAddr(rhs._baseAddr) {}

	bool operator==(const PixelRef &rhs) const
	{ return _baseAddr == rhs._baseAddr; }

	PixelRef& operator=(const PixelRef &rhs)
	{ 
		_baseAddr = rhs._baseAddr;
		return *this;
	}

	PIXELPACKET& operator*() { return *reinterpret_cast<PIXELPACKET*>(_baseAddr); }
	const PIXELPACKET& operator*() const { return *reinterpret_cast<const PIXELPACKET*>(_baseAddr);; }

	PIXELPACKET* operator->() { return reinterpret_cast<PIXELPACKET*>(_baseAddr); }
	const PIXELPACKET* operator->() const { return reinterpret_cast<PIXELPACKET*>(_baseAddr); }

	typename PIXELPACKET::ComponentType* baseAddr() { return _baseAddr; }
	const typename PIXELPACKET::ComponentType* baseAddr() const { return _baseAddr; }

	void advance(int nb)
	{ _baseAddr = const_cast<typename PIXELPACKET::ComponentType*>(reinterpret_cast<const typename PIXELPACKET::ComponentType*>(reinterpret_cast<PIXELPACKET*>(_baseAddr)+nb)); }

public:
	typename PIXELPACKET::ComponentType* _baseAddr;
};

		// FIXME
		// These specialization can probably be simplified with a common
		// base for multi-plane types.  For now, we just reimplement the whole
		// thing each time...

//------------------------------------------------------------------------------
// CLASS PixelRef - Special case for 3 planes
//------------------------------------------------------------------------------
template<class PIXELPACKET>
class PixelRef<PIXELPACKET, 3>
{
public:
	typedef typename PIXELPACKET::Plane0Storage::ComponentType Plane0Type;
	typedef typename PIXELPACKET::Plane1Storage::ComponentType Plane1Type;
	typedef typename PIXELPACKET::Plane2Storage::ComponentType Plane2Type;

public:
	PixelRef() : _packet(NULL, NULL, NULL) {}

	PixelRef(Plane0Type *plane0, Plane1Type *plane1, Plane2Type *plane2) : _packet(plane0, plane1, plane2) {}

	template<class RHS_PIXELPACKET>
	PixelRef(const PixelRef<RHS_PIXELPACKET> &rhs) : _packet(rhs._packet) {}

	bool operator==(const PixelRef &rhs) const
	{ return _packet == rhs._packet; }

	PixelRef& operator=(const PixelRef &rhs)
	{
		const_cast<typename TypeInfo<PIXELPACKET>::BaseType &>(_packet) = PIXELPACKET(
			const_cast<Plane0Type*>(rhs._packet.plane0Ptr()->storage().ptr()),
			const_cast<Plane1Type*>(rhs._packet.plane1Ptr()->storage().ptr()),
			const_cast<Plane2Type*>(rhs._packet.plane2Ptr()->storage().ptr())
		);
		return *this;
	}

	PIXELPACKET& operator*() { return _packet; }
	const PIXELPACKET& operator*() const { return _packet; }

	PIXELPACKET* operator->() { return &_packet; }
	const PIXELPACKET* operator->() const { return &_packet; }

	void advance(int nb)
	{
		int bytesToSkip0 = nb*PIXELPACKET::Plane0Storage::BYTES_PER_PACKET;
		Plane0Type *baseAddr0 = const_cast<Plane0Type *>(_packet.plane0Ptr()->storage().ptr());
		Plane0Type *newAddr0 = PtrManip::advanceNBytes(baseAddr0, bytesToSkip0);

		int bytesToSkip1 = nb*PIXELPACKET::Plane1Storage::BYTES_PER_PACKET;
		Plane1Type *baseAddr1 = const_cast<Plane1Type*>(_packet.plane1Ptr()->storage().ptr());
		Plane1Type *newAddr1 = PtrManip::advanceNBytes(baseAddr1, bytesToSkip1);

		int bytesToSkip2 = nb*PIXELPACKET::Plane2Storage::BYTES_PER_PACKET;
		Plane2Type *baseAddr2 = const_cast<Plane2Type*>(_packet.plane2Ptr()->storage().ptr());
		Plane2Type *newAddr2 = PtrManip::advanceNBytes(baseAddr2, bytesToSkip2);

		const_cast<typename TypeInfo<PIXELPACKET>::BaseType&>(_packet) = PIXELPACKET(newAddr0, newAddr1, newAddr2);
	}

public:
	PIXELPACKET _packet;
};

//------------------------------------------------------------------------------
// CLASS PixelRef - Special case for 4 planes
//------------------------------------------------------------------------------
template<class PIXELPACKET>
class PixelRef<PIXELPACKET, 4>
{
public:
	typedef typename PIXELPACKET::Plane0Storage::ComponentType Plane0Type;
	typedef typename PIXELPACKET::Plane1Storage::ComponentType Plane1Type;
	typedef typename PIXELPACKET::Plane2Storage::ComponentType Plane2Type;
	typedef typename PIXELPACKET::Plane3Storage::ComponentType Plane3Type;

public:
	PixelRef(Plane0Type *plane0, Plane1Type *plane1, Plane2Type *plane2, Plane3Type *plane3) : _packet(plane0, plane1, plane2, plane3) {}

	template<class RHS_PIXELPACKET>
	PixelRef(const PixelRef<RHS_PIXELPACKET> &rhs) : _packet(rhs._packet) {}

	bool operator==(const PixelRef &rhs) const
	{ return _packet == rhs._packet; }

	PixelRef& operator=(const PixelRef &rhs)
	{
		const_cast<typename TypeInfo<PIXELPACKET>::BaseType &>(_packet) = PIXELPACKET(
			const_cast<Plane0Type*>(rhs._packet.plane0Ptr()),
			const_cast<Plane1Type*>(rhs._packet.plane1Ptr()),
			const_cast<Plane2Type*>(rhs._packet.plane2Ptr()),
			const_cast<Plane3Type*>(rhs._packet.plane3Ptr())
		);
		return *this;
	}

	PIXELPACKET& operator*() { return _packet; }
	const PIXELPACKET& operator*() const { return _packet; }

	PIXELPACKET* operator->() { return &_packet; }
	const PIXELPACKET* operator->() const { return &_packet; }

	void advance(int nb)
	{
		int bytesToSkip0 = nb*PIXELPACKET::Plane0Storage::BYTES_PER_PACKET;
		Plane0Type *baseAddr0 = const_cast<Plane0Type*>(_packet.plane0Ptr());
		Plane0Type *newAddr0 = PtrManip::advanceNBytes(baseAddr0, bytesToSkip0);

		int bytesToSkip1 = nb*PIXELPACKET::Plane1Storage::BYTES_PER_PACKET;
		Plane1Type *baseAddr1 = const_cast<Plane1Type*>(_packet.plane1Ptr());
		Plane1Type *newAddr1 = PtrManip::advanceNBytes(baseAddr1, bytesToSkip1);

		int bytesToSkip2 = nb*PIXELPACKET::Plane2Storage::BYTES_PER_PACKET;
		Plane2Type *baseAddr2 = const_cast<Plane2Type*>(_packet.plane2Ptr());
		Plane2Type *newAddr2 = PtrManip::advanceNBytes(baseAddr2, bytesToSkip2);

		int bytesToSkip3 = nb*PIXELPACKET::Plane3Storage::BYTES_PER_PACKET;
		Plane2Type *baseAddr3 = const_cast<Plane3Type*>(_packet.plane3Ptr());
		Plane2Type *newAddr3 = PtrManip::advanceNBytes(baseAddr3, bytesToSkip3);

		const_cast<typename TypeInfo<PIXELPACKET>::BaseType&>(_packet) = PIXELPACKET(newAddr0, newAddr1, newAddr2, newAddr3);
	}

public:
	PIXELPACKET _packet;
};


}

#endif // __ITL_PIXELREF_H__
