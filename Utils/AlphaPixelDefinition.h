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
#ifndef __ITL_ALPHAPIXELDEFINITION_H__
#define __ITL_ALPHAPIXELDEFINITION_H__

#include "../PixelBase.h"
#include "../PixelConvert/Alpha.h"

//==============================================================================
// FILE AlphaPixelDefinition.h
//==============================================================================
// Various definitions to create Alpha packed pixels (see RGBPixel.h)
//------------------------------------------------------------------------------


//==============================================================================
// CLASS ConstAlphaPixelFamilyBase
//==============================================================================
template<typename PARENT, typename STORAGE_TYPE>
class ConstAlphaPixelFamilyBase: public PARENT
{
private:
	typedef PARENT _Super;

protected:
	typedef typename _Super::_Manip	_Manip;

public:
	typedef STORAGE_TYPE AlphaStorageType;
	typedef typename AlphaStorageType::ComponentType 	AlphaComponentType;

public:
	ConstAlphaPixelFamilyBase() {}
	
public:
	ConstAlphaPixelFamilyBase(const ConstAlphaPixelFamilyBase &rhs) : _Super(rhs) {}

public:
	static AlphaComponentType alpha(const AlphaStorageType &storage)	{ return _Manip::template Alpha<AlphaStorageType>(storage);   }
	AlphaComponentType alpha()   const	{ return alpha(_Super::_storage);   }
};

//==============================================================================
// CLASS AlphaPixelFamilyBase
//==============================================================================
template<typename PARENT, typename STORAGE_TYPE>
class AlphaPixelFamilyBase: public PARENT
{
private:
	typedef PARENT _Super;

protected:
	typedef typename _Super::DerivedType DerivedType;
	typedef typename _Super::_Manip	_Manip;

public:
	typedef STORAGE_TYPE AlphaStorageType;
	typedef typename AlphaStorageType::ComponentType 	AlphaComponentType;

public:
	AlphaPixelFamilyBase() {}
	
public:
	AlphaPixelFamilyBase(const AlphaPixelFamilyBase &rhs) : _Super(rhs) {}
	AlphaPixelFamilyBase(const AlphaStorageType &alpha) : _Super() { setAlpha(alpha); }
	AlphaPixelFamilyBase& operator=(const AlphaPixelFamilyBase &rhs) { _Super::operator=(rhs); return *this; }

public:
	static void setAlpha  (AlphaStorageType &storage, const AlphaComponentType &val)	{ _Manip::template setAlpha<AlphaStorageType>(storage, val);   }
	void setAlpha(const AlphaComponentType &val)	{ setAlpha(_Super::_storage, val);   }

	using _Super::plane0Ptr;
	AlphaComponentType* plane0Ptr() { return storage().ptr(); }

	using _Super::storage;
	AlphaStorageType& storage() { return _Super::_storage; }

public:
	template<typename PIXELSRC>
	void convert(const PIXELSRC &fromPixel)
	{
		_Super::convert(fromPixel);
		setAlpha(PixelConvertExtractAlpha<PIXELSRC, DerivedType>::eval(fromPixel));
	}
};

//==============================================================================
// CLASS ConstAlphaPixelFamily
//==============================================================================
template<typename COMPONENT_STORAGE>
class ConstAlphaPixelFamily: public ConstAlphaPixelFamilyBase<ConstPixelBase<COMPONENT_STORAGE, ConstAlphaPixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>
{
private:
	typedef ConstAlphaPixelFamilyBase<ConstPixelBase<COMPONENT_STORAGE, ConstAlphaPixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE> _Super;

public:
	ConstAlphaPixelFamily() {}
	ConstAlphaPixelFamily(const ConstAlphaPixelFamily &rhs) : _Super(rhs) {}
};


//==============================================================================
// CLASS AlphaPixelFamily
//==============================================================================
template<typename COMPONENT_STORAGE>
class AlphaPixelFamily: public AlphaPixelFamilyBase<ConstAlphaPixelFamilyBase<PixelBase<ConstPixelBase<COMPONENT_STORAGE, AlphaPixelFamily<COMPONENT_STORAGE> > >, COMPONENT_STORAGE>, COMPONENT_STORAGE>
{
private:
	typedef AlphaPixelFamilyBase<ConstAlphaPixelFamilyBase<PixelBase<ConstPixelBase<COMPONENT_STORAGE, AlphaPixelFamily<COMPONENT_STORAGE> > >, COMPONENT_STORAGE>, COMPONENT_STORAGE> _Super;

public:
	AlphaPixelFamily() {}
	AlphaPixelFamily(const AlphaPixelFamily &rhs) : _Super(rhs) {}
};

#endif // __ITL_ALPHAPIXELDEFINITION_H__
