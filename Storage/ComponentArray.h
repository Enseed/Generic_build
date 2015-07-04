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
#ifndef __ITL_COMPONENTSTORAGE_H__
#define __ITL_COMPONENTSTORAGE_H__

//==============================================================================
//	FILE ComponentArray.h
//==============================================================================
// The ComponentArray is used to build pixel storage based on an array scheme.
// This is the most common scheme, a pixel having N components, all of the
// same type T, packed one after the other.  If the pixel is planar, we
// use a ComponentArrayRef - meaning we expect the memory to be already
// allocated and we point to it.  The ComponentArray can be used on existing
// memory - for instance, allocate 3 bytes and cast the buffer as a 
// ComponentArray used for RGB will allow you to use the buffer as a RGB pixel.
// In both cases (the ComponentArray or ComponentArrayRef), you can then call 
// .red(), .luminance(), .alpha(), etc... on it, as long as it is defined in 
// the COMPONENT_ORDERING provided.
//
// The COMPONENT_ORDERING is simply a class with an enum that defines how many
// components are in the ComponentArray and in what order.  For example:
//
// // define a RGB pixel with COMPONENT_COUNT = 3
// struct RGBPixelOrder { enum { RED, GREEN, BLUE, COMPONENT_COUNT }; };
//
// // define a BGR pixel with COMPONENT_COUNT = 3
// struct BGRPixelOrder { enum { BLUE, GREEN, RED, COMPONENT_COUNT }; };
//
//------------------------------------------------------------------------------

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include <cstddef>

#include "ComponentSpecification.h"

//==============================================================================
//	CLASS ConstComponentArrayBase
//==============================================================================
// Allow array access based on the component ordering.
// We are exploiting a particularity of copilers here: not all of the enum 
// needs to be defined.  The compiler validates the enum as we it instantiates
// the member function.  For instance, calling red() will generate an error if
// COMPONENT_ORDERING::RED is not defined, but not having COMPONENT_ORDERING::RED
// defined will not cause any error unless red() is called.  
//------------------------------------------------------------------------------
template<typename COMPONENT_TYPE, typename COMPONENT_ORDERING, typename STORAGE_TYPE, typename COMPONENT_MODEL, typename COLOR_SPACE, typename COMPONENT_RANGE>
class ConstComponentArrayBase: public ComponentSpecification<COMPONENT_TYPE, COMPONENT_RANGE>
{
public:
	typedef COMPONENT_TYPE ComponentType;
	typedef COLOR_SPACE ColorSpace;
	typedef COMPONENT_MODEL ComponentModel;
	enum { BYTES_PER_PACKET = sizeof(COMPONENT_TYPE)*COMPONENT_ORDERING::COMPONENT_COUNT}; 
	
	ConstComponentArrayBase() : _storage() {}
	ConstComponentArrayBase(const STORAGE_TYPE &storage) : _storage(storage) {}

public:
	const ComponentType& red() const			{ return _storage[COMPONENT_ORDERING::RED];   }
	const ComponentType& green() const			{ return _storage[COMPONENT_ORDERING::GREEN]; }
	const ComponentType& blue() const			{ return _storage[COMPONENT_ORDERING::BLUE];  }

	const ComponentType& luminance() const		{ return _storage[COMPONENT_ORDERING::Y];   }
	const ComponentType& luminance0() const		{ return _storage[COMPONENT_ORDERING::Y0];   }
	const ComponentType& chromaBlue() const		{ return _storage[COMPONENT_ORDERING::CB]; }
	const ComponentType& luminance1() const		{ return _storage[COMPONENT_ORDERING::Y1];  }
	const ComponentType& chromaRed() const		{ return _storage[COMPONENT_ORDERING::CR];  }

	const ComponentType& alpha() const			{ return _storage[COMPONENT_ORDERING::ALPHA];  }

	const ComponentType& x() const				{ return _storage[COMPONENT_ORDERING::X]; }
	const ComponentType& y() const				{ return _storage[COMPONENT_ORDERING::Y]; }
	const ComponentType& z() const				{ return _storage[COMPONENT_ORDERING::Z]; }

	const ComponentType* ptr() const { return _storage; }

	const ComponentType& cyan() const			{ return _storage[COMPONENT_ORDERING::CYAN];   }
	const ComponentType& magenta() const		{ return _storage[COMPONENT_ORDERING::MAGENTA]; }
	const ComponentType& yellow() const			{ return _storage[COMPONENT_ORDERING::YELLOW];  }
	const ComponentType& black() const			{ return _storage[COMPONENT_ORDERING::BLACK];  }

	bool operator==(const ConstComponentArrayBase &rhs) const
	{ return _storage == rhs._storage; }

	bool operator!=(const ConstComponentArrayBase &rhs) const
	{ return _storage != rhs._storage; }

	static size_t size() { return sizeof(STORAGE_TYPE); }

public:
	STORAGE_TYPE _storage;
};

//==============================================================================
//	CLASS ComponentArrayBase
//==============================================================================
// Non-const version
//------------------------------------------------------------------------------
template<typename COMPONENT_TYPE, typename COMPONENT_ORDERING, typename STORAGE_TYPE, typename COMPONENT_MODEL, typename COLOR_SPACE, typename COMPONENT_RANGE>
class ComponentArrayBase: public ConstComponentArrayBase<COMPONENT_TYPE, COMPONENT_ORDERING, STORAGE_TYPE, COMPONENT_MODEL, COLOR_SPACE, COMPONENT_RANGE>
{
private:
	typedef ConstComponentArrayBase<COMPONENT_TYPE, COMPONENT_ORDERING, STORAGE_TYPE, COMPONENT_MODEL, COLOR_SPACE, COMPONENT_RANGE> _Super;

public:
	typedef COMPONENT_TYPE ComponentType;

	ComponentArrayBase() {}
	ComponentArrayBase(STORAGE_TYPE storage) : _Super(storage) {}

public:
	void setRed(const ComponentType &val)		{ _Super::_storage[COMPONENT_ORDERING::RED] = val;   }
	void setGreen(const ComponentType &val)		{ _Super::_storage[COMPONENT_ORDERING::GREEN] = val; }
	void setBlue(const ComponentType &val)		{ _Super::_storage[COMPONENT_ORDERING::BLUE] = val;  }

	void setLuminance(const ComponentType &val)	{ _Super::_storage[COMPONENT_ORDERING::Y] = val;    }
	void setLuminance0(const ComponentType &val){ _Super::_storage[COMPONENT_ORDERING::Y0] = val;   }
	void setLuminance1(const ComponentType &val){ _Super::_storage[COMPONENT_ORDERING::Y1] = val;   }

	void setChromaBlue(const ComponentType &val){ _Super::_storage[COMPONENT_ORDERING::CB] = val;   }
	void setChromaRed(const ComponentType &val)	{ _Super::_storage[COMPONENT_ORDERING::CR] = val;   }

	void setAlpha(const ComponentType &val)		{ _Super::_storage[COMPONENT_ORDERING::ALPHA] = val;}

	void setX(const ComponentType &val) 		{ _Super::_storage[COMPONENT_ORDERING::X] = val; }
	void setY(const ComponentType &val) 		{ _Super::_storage[COMPONENT_ORDERING::Y] = val; }
	void setZ(const ComponentType &val) 		{ _Super::_storage[COMPONENT_ORDERING::Z] = val; }

	void setCyan(const ComponentType &val) 		{ _Super::_storage[COMPONENT_ORDERING::CYAN] = val; }
	void setMagenta(const ComponentType &val) 	{ _Super::_storage[COMPONENT_ORDERING::MAGENTA] = val; }
	void setYellow(const ComponentType &val) 	{ _Super::_storage[COMPONENT_ORDERING::YELLOW] = val; }
	void setBlack(const ComponentType &val) 	{ _Super::_storage[COMPONENT_ORDERING::BLACK] = val; }

	ComponentType* ptr()			 			{ return _Super::_storage; }
	const ComponentType* ptr() const 			{ return _Super::ptr(); }
};

//==============================================================================
//	CLASS ComponentArrayStorage
//==============================================================================
// Storage in the form of an array of components
//------------------------------------------------------------------------------
template<typename COMPONENT_TYPE, int SIZE>
class ComponentArrayStorage
{
public:
	COMPONENT_TYPE& operator[](int index) { return _buffer[index]; }
	const COMPONENT_TYPE& operator[](int index) const { return _buffer[index]; }
	
	operator COMPONENT_TYPE* () { return _buffer; }
	operator const COMPONENT_TYPE* () const { return _buffer; }
	
private:
	COMPONENT_TYPE _buffer[SIZE];
};

//==============================================================================
//	CLASS ComponentArray
//==============================================================================
// This is a ComponentArray on top of an actual array (as opposed to a reference
// to existing memory - see ComponentArrayRef)
//------------------------------------------------------------------------------
template<typename COMPONENT_TYPE, typename COMPONENT_ORDERING, typename COMPONENT_MODEL, typename COLOR_SPACE, typename COMPONENT_RANGE>
class ComponentArray: public ComponentArrayBase<COMPONENT_TYPE, COMPONENT_ORDERING, ComponentArrayStorage<COMPONENT_TYPE, COMPONENT_ORDERING::COMPONENT_COUNT>, COMPONENT_MODEL, COLOR_SPACE, COMPONENT_RANGE>
{};

//==============================================================================
//	CLASS ComponentArrayRef
//==============================================================================
// ComponentArray that points to existing memory.
//------------------------------------------------------------------------------
template<typename COMPONENT_TYPE, typename COMPONENT_ORDERING, typename COMPONENT_MODEL, typename COLOR_SPACE, typename COMPONENT_RANGE>
class ComponentArrayRef: public ComponentArrayBase<COMPONENT_TYPE, COMPONENT_ORDERING, COMPONENT_TYPE*, COMPONENT_MODEL, COLOR_SPACE, COMPONENT_RANGE>
{
public:
	ComponentArrayRef(COMPONENT_TYPE *ref)
	:
		ComponentArrayBase<COMPONENT_TYPE, COMPONENT_ORDERING, COMPONENT_TYPE*, COMPONENT_MODEL, COLOR_SPACE, COMPONENT_RANGE>(ref)
	{}
};

//==============================================================================
//	CLASS ConstComponentArrayRef
//==============================================================================
// ComponentArray that points to existing const memory.
//------------------------------------------------------------------------------
template<typename COMPONENT_TYPE, typename COMPONENT_ORDERING, typename COMPONENT_MODEL, typename COLOR_SPACE, typename COMPONENT_RANGE>
class ConstComponentArrayRef: public ConstComponentArrayBase<COMPONENT_TYPE, COMPONENT_ORDERING, const COMPONENT_TYPE*, COMPONENT_MODEL, COLOR_SPACE, COMPONENT_RANGE>
{
public:
	ConstComponentArrayRef(const COMPONENT_TYPE *ref)
	:
		ConstComponentArrayBase<COMPONENT_TYPE, COMPONENT_ORDERING, const COMPONENT_TYPE*, COMPONENT_MODEL, COLOR_SPACE, COMPONENT_RANGE>(ref)
	{}
};

#include "ComponentRange.h"
#include "ComponentModel.h"
#include "ColorSpace.h"

struct SingleComponentStorageOrdering { enum { COMPONENT_COUNT = 1}; };

typedef ComponentArray<float, SingleComponentStorageOrdering, ComponentModel_Value, ColorSpace_None, DefaultRange<float> > FloatComponent;
typedef ComponentArray<float, SingleComponentStorageOrdering, ComponentModel_Value, ColorSpace_None, ComponentRange<float, -1, 2, 1, 2> > SignedFloatComponent;








#include "../Utils/BitIO.h"



template<int BITS, typename COMPONENT_ORDERING, typename COMPONENT_MODEL, typename COLOR_SPACE, typename COMPONENT_RANGE>
class BitStorage: public COMPONENT_RANGE
{
public:
	typedef COLOR_SPACE ColorSpace;
	typedef COMPONENT_MODEL ComponentModel;
	typedef unsigned char ComponentType;
	typedef enum { BYTES_PER_PACKET = 1 };
	
	enum { NBBIT = BITS };
	enum { BITPACKET_PER_PACKET = 8 / BITS };


	template<int INDEX>
	ComponentType value() const
	{	return BitIO::readBits<unsigned char, ComponentType, 8-INDEX*NBBIT-NBBIT, NBBIT>(&_byte); 	}

	template<int INDEX>
	void setValue(ComponentType val)
	{	BitIO::writeBits<unsigned char, ComponentType, 8-INDEX*NBBIT-NBBIT, NBBIT>(&_byte, val); }
	
	ComponentType* ptr() { return &_byte; }
	const ComponentType* ptr() const { return &_byte; }
private:
	unsigned char _byte;
};


#endif // __ITL_COMPONENTSTORAGE_H__

