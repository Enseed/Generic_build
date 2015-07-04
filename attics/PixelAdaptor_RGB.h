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
#if 0
#ifndef __ITL_PIXELADAPTOR_RGB_H__
#define __ITL_PIXELADAPTOR_RGB_H__

//==============================================================================
//	FILE PixelAdaptor_RGB.h
//==============================================================================

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "PixelAdaptor.h"

//==============================================================================
//	CLASS PixelAdator
//==============================================================================
template<typename ADAPTED_TYPE, typename ACTUAL_TYPE>
class PixelAdaptor<ADAPTED_TYPE, ACTUAL_TYPE, ColorSpace_sRGB, ColorSpace_sRGB, 1>
{
	typedef typename ACTUAL_TYPE::ComponentStorageType ComponentStorageType;
	typedef typename ADAPTED_TYPE::ComponentStorageType::ColorSpace ColorSpace;
	typedef typename ADAPTED_TYPE::ComponentType ComponentType;
	typedef typename ADAPTED_TYPE::PixelManipulatorType PixelManipulatorType;
	
	typedef ComponentType RedComponentType;
	typedef ComponentType GreenComponentType;
	typedef ComponentType BlueComponentType;
	
	enum { PIXEL_PER_PACKET = ACTUAL_TYPE::PIXEL_PER_PACKET };
	static size_t size() { ACTUAL_TYPE::size(); }
	
	typedef ComponentStorageType Plane0Type;
	enum { PLANE_COUNT = ACTUAL_TYPE::PLANE_COUNT };
	
public:
	ConstRGBPixelFamily() {}
	
public:
	ConstRGBPixelFamily(const ConstRGBPixelFamily &rhs) : _storage(rhs._storage) {}
	
public:
	static ComponentType red(const ComponentStorageType &storage)	{ return PixelManipulatorType::template red<ComponentStorageType>(storage);   }
	static ComponentType green(const ComponentStorageType &storage)	{ return PixelManipulatorType::template green<ComponentStorageType>(storage);   }
	static ComponentType blue (const ComponentStorageType &storage)	{ return PixelManipulatorType::template blue<ComponentStorageType>(storage);   }
	
	ComponentType red()   const	{ return red(_storage);   }
	ComponentType green() const	{ return green(_storage); }
	ComponentType blue()  const	{ return blue(_storage);  }
	
	const ComponentStorageType& storage() const { return _storage; }
	
protected:
	ComponentStorageType _storage;
};
#endif // __ITL_PIXELADAPTOR_RGB_H__

#endif // 0
