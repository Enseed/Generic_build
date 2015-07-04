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
#ifndef __ITL_YCBCR422PIXELDEFINITION_H__
#define __ITL_YCBCR422PIXELDEFINITION_H__


#include <cassert>

//==============================================================================
// CLASS YCbCr422LuminanceEven
//==============================================================================
template<typename COMPONENT_STORAGE, typename PIXEL_MANIPULATOR>
class YCbCr422LuminanceEven
{
public:
	static typename COMPONENT_STORAGE::ComponentType luminance(const COMPONENT_STORAGE &storage)	{ return PIXEL_MANIPULATOR::template luminance0<COMPONENT_STORAGE>(storage);   }
};

//==============================================================================
// CLASS YCbCr422LuminanceOdd
//==============================================================================
template<typename COMPONENT_STORAGE, typename PIXEL_MANIPULATOR>
class YCbCr422LuminanceOdd
{
public:
	static typename COMPONENT_STORAGE::ComponentType luminance(const COMPONENT_STORAGE &storage)	{ return PIXEL_MANIPULATOR::template luminance1<COMPONENT_STORAGE>(storage);   }
};

//==============================================================================
// CLASS ConstYCbCr422PixelFamily_OLD
//==============================================================================
template<typename COMPONENT_STORAGE, typename PIXEL_MANIPULATOR, typename LUMINANCE_SELECTOR>
class ConstYCbCr422PixelFamily_OLD
{
public:
	typedef typename COMPONENT_STORAGE::ColorSpace ColorSpace;

public:
	typedef COMPONENT_STORAGE ComponentStorageType;
	typedef typename ComponentStorageType::ComponentType ComponentType, Y0ComponentType, CbComponentType, Y1ComponentType, CrComponentType;;
	typedef PIXEL_MANIPULATOR PixelManipulatorType;

private:
	ConstYCbCr422PixelFamily_OLD();
	ConstYCbCr422PixelFamily_OLD(const ConstYCbCr422PixelFamily_OLD &rhs);
	ConstYCbCr422PixelFamily_OLD& operator=(const ConstYCbCr422PixelFamily_OLD &rhs);

public:
	static ComponentType luminance(const ComponentStorageType &storage)	{ return LUMINANCE_SELECTOR::luminance(storage);   }
	static ComponentType chromaBlue(const ComponentStorageType &storage)	{ return PixelManipulatorType::template chromaBlue<ComponentStorageType>(storage);   }
	static ComponentType chromaRed(const ComponentStorageType &storage)	{ return PixelManipulatorType::template chromaRed<ComponentStorageType>(storage);   }

	ComponentType luminance() const	{ return luminance(_storage);   }
	ComponentType chromaBlue() const	{ return chromaBlue(_storage); }
	ComponentType chromaRed()  const	{ return chromaRed(_storage);  }
	
	static ComponentType minLuminance() { return ComponentStorageType::min(); }
	static ComponentType maxLuminance() { return ComponentStorageType::max(); }
	static ComponentType minChromaBlue() { return ComponentStorageType::min(); }
	static ComponentType maxChromaBlue() { return ComponentStorageType::max(); }
	static ComponentType minChromaRed() { return ComponentStorageType::min(); }
	static ComponentType maxChromaRed() { return ComponentStorageType::max(); }
	
	
private:
	ComponentStorageType _storage;
};

//==============================================================================
// CLASS ConstYCbCr422PixelPacket
//==============================================================================
template<typename PIXEL_TYPE0, typename PIXEL_TYPE1>
class ConstYCbCr422PixelPacket
{
public:
	typedef typename PIXEL_TYPE0::ComponentStorageType ComponentStorageType;
	typedef PIXEL_TYPE0 PixelType0;
	typedef PIXEL_TYPE1 PixelType1;
	typedef typename PixelType0::Y0ComponentType Y0ComponentType;
	typedef typename PixelType0::CbComponentType CbComponentType;
	typedef typename PixelType0::Y1ComponentType Y1ComponentType;
	typedef typename PixelType1::CrComponentType CrComponentType;
	typedef typename PixelType0::PixelManipulatorType PixelManipulatorType;
	enum { PIXEL_PER_PACKET = 2 };

	typedef typename PIXEL_TYPE0::ColorSpace ColorSpace;

	typedef ComponentStorageType Plane0Storage;
	typedef typename ComponentStorageType::ComponentType ComponentType;
	enum { PLANE_COUNT = 1 };

public:
	ConstYCbCr422PixelPacket() : _storage() {}
	ConstYCbCr422PixelPacket(const ConstYCbCr422PixelPacket &rhs) : _storage(rhs._storage) {}
	ConstYCbCr422PixelPacket& operator=(const ConstYCbCr422PixelPacket &rhs) { _storage = rhs._storage; return *this; }

public:
	Y0ComponentType luminance0() const
	{ return _storage.luminance0(); }

	CbComponentType chromaBlue() const
	{ return _storage.chromaBlue(); }

	Y1ComponentType luminance1() const
	{ return _storage.luminance1(); }

	CrComponentType chromaRed() const
	{ return _storage.chromaRed(); }

	const PixelType0& pixel0() const 	{ return reinterpret_cast<const PixelType0&>(_storage); }
	PixelType0& pixel0() { return reinterpret_cast<PixelType0&>(_storage); }

	const PixelType1& pixel1() const 	{ return reinterpret_cast<const PixelType1&>(_storage); }
	PixelType1& pixel1() { return reinterpret_cast<PixelType1&>(_storage); }

	static ComponentType minLuminance0() { return ComponentStorageType::min(); }
	static ComponentType maxLuminance0() { return ComponentStorageType::max(); }
	static ComponentType minLuminance1() { return ComponentStorageType::min(); }
	static ComponentType maxLuminance1() { return ComponentStorageType::max(); }
	static ComponentType minChromaBlue() { return ComponentStorageType::min(); }
	static ComponentType maxChromaBlue() { return ComponentStorageType::max(); }
	static ComponentType minChromaRed() { return ComponentStorageType::min(); }
	static ComponentType maxChromaRed() { return ComponentStorageType::max(); }

protected:
	ComponentStorageType _storage;
};

//==============================================================================
// CLASS YCbCr422PixelPacket
//==============================================================================
template<typename PIXEL_TYPE0, typename PIXEL_TYPE1>
class YCbCr422PixelPacket: public ConstYCbCr422PixelPacket<PIXEL_TYPE0, PIXEL_TYPE1>
{
private:
	typedef ConstYCbCr422PixelPacket<PIXEL_TYPE0, PIXEL_TYPE1> _Super;

	typedef typename _Super::PixelManipulatorType PixelManipulatorType;

public:
	typedef typename _Super::Y0ComponentType Y0ComponentType;
	typedef typename _Super::Y1ComponentType Y1ComponentType;
	typedef typename _Super::CbComponentType CbComponentType;
	typedef typename _Super::CrComponentType CrComponentType;
	
	YCbCr422PixelPacket() : _Super() {}
	YCbCr422PixelPacket(const YCbCr422PixelPacket &rhs) : _Super(rhs) {}
	YCbCr422PixelPacket(const Y0ComponentType& y0, const CbComponentType& cb, const Y1ComponentType &y1, const CrComponentType &cr) : _Super() { setYCbYCr(y0, cb, y1, cr); }
	YCbCr422PixelPacket& operator=(const YCbCr422PixelPacket &rhs) { _Super::_storage = rhs._storage; return *this; }

public:
	void setYCbYCr(const Y0ComponentType &y0, const CbComponentType &cb, const Y1ComponentType &y1, const CrComponentType &cr) { PixelManipulatorType::setYCbYCr(_Super::_storage, y0, cb, y1, cr); }
};








































//==============================================================================
// CLASS ConstYCbCr422PixelFamilyBase
//==============================================================================
template<typename PARENT>
class ConstYCbCr422PixelFamilyBase: public PARENT
{
private:
	typedef PARENT _Super;

public:
	ConstYCbCr422PixelFamilyBase() {}

protected:
	ConstYCbCr422PixelFamilyBase(const ConstYCbCr422PixelFamilyBase &rhs) : _Super(rhs) {}
};


//==============================================================================
// CLASS Const0YCbCr422PixelFamily
//==============================================================================
template<typename COMPONENT_STORAGE>
class ConstY0CbCr422PixelFamily: public ConstYCbCr422PixelFamilyBase<ConstLuminance0PixelFamilyBase<ConstChromaBluePixelFamilyBase<ConstChromaRedPixelFamilyBase<ConstPixelBase<COMPONENT_STORAGE, ConstY0CbCr422PixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE> >
{
private:
	typedef ConstYCbCr422PixelFamilyBase<ConstLuminance0PixelFamilyBase<ConstChromaBluePixelFamilyBase<ConstChromaRedPixelFamilyBase<ConstPixelBase<COMPONENT_STORAGE, ConstY0CbCr422PixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE> > _Super;

public:
	typedef typename _Super::Luminance0StorageType LuminanceStorageType;
	typedef typename _Super::Luminance0ComponentType LuminanceComponentType;
	
	LuminanceComponentType luminance() const { return _Super::luminance0(); }

	ConstY0CbCr422PixelFamily() {}
	
protected:
	ConstY0CbCr422PixelFamily(const ConstY0CbCr422PixelFamily &rhs) : _Super(rhs) {}
};

//==============================================================================
// CLASS Const0YCbCr422PixelFamily
//==============================================================================
template<typename COMPONENT_STORAGE>
class ConstY1CbCr422PixelFamily: public ConstYCbCr422PixelFamilyBase<ConstLuminance1PixelFamilyBase<ConstChromaBluePixelFamilyBase<ConstChromaRedPixelFamilyBase<ConstPixelBase<COMPONENT_STORAGE, ConstY1CbCr422PixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE> >
{
private:
	typedef ConstYCbCr422PixelFamilyBase<ConstLuminance1PixelFamilyBase<ConstChromaBluePixelFamilyBase<ConstChromaRedPixelFamilyBase<ConstPixelBase<COMPONENT_STORAGE, ConstY1CbCr422PixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE> > _Super;

public:
	typedef typename _Super::Luminance1StorageType LuminanceStorageType;
	typedef typename _Super::Luminance1ComponentType LuminanceComponentType;

	LuminanceComponentType luminance() const { return _Super::luminance1(); }

public:
	ConstY1CbCr422PixelFamily() {}
	
protected:
	ConstY1CbCr422PixelFamily(const ConstY1CbCr422PixelFamily &rhs) : _Super(rhs) {}
};


//==============================================================================
// CLASS ConstYCbCr422PixelFamilyBase
//==============================================================================
template<typename PARENT>
class ConstYCbCr422PixelPacketFamilyBase: public PARENT
{
private:
	typedef PARENT _Super;

public:
	typedef typename _Super::PacketStorageType PacketStorageType;
	
	enum { PIXEL_PER_PACKET = 2 };

	ConstYCbCr422PixelPacketFamilyBase() {}
	
	const ConstY0CbCr422PixelFamily<PacketStorageType>& pixel0() const 
	{ return *(ConstY0CbCr422PixelFamily<PacketStorageType>*)this; }

	const ConstY1CbCr422PixelFamily<PacketStorageType>& pixel1() const 
	{ return *(ConstY1CbCr422PixelFamily<PacketStorageType>*)this; }


protected:
	ConstYCbCr422PixelPacketFamilyBase(const ConstYCbCr422PixelPacketFamilyBase &rhs) : _Super(rhs) {}
};


//==============================================================================
// CLASS ConstYCbCr422PixelPacketFamily
//==============================================================================
template<typename COMPONENT_STORAGE>
class ConstYCbCr422PixelPacketFamily: public ConstYCbCr422PixelPacketFamilyBase<ConstLuminance0PixelFamilyBase<ConstLuminance1PixelFamilyBase<ConstChromaBluePixelFamilyBase<ConstChromaRedPixelFamilyBase<ConstPixelBase<COMPONENT_STORAGE, ConstY1CbCr422PixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE> >
{
private:
	typedef ConstYCbCr422PixelFamilyBase<ConstLuminance0PixelFamilyBase<ConstLuminance1PixelFamilyBase<ConstChromaBluePixelFamilyBase<ConstChromaRedPixelFamilyBase<ConstPixelBase<COMPONENT_STORAGE, ConstY1CbCr422PixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE> > _Super;

public:
	ConstYCbCr422PixelPacketFamily() {}
	
protected:
	ConstYCbCr422PixelPacketFamily(const ConstYCbCr422PixelPacketFamily &rhs) : _Super(rhs) {}
};


//==============================================================================
// CLASS YCbCr422PixelPacketFamilyBase
//==============================================================================
template<typename PARENT>
class YCbCr422PixelPacketFamilyBase: public ConstYCbCr422PixelPacketFamilyBase<PARENT>
{
private:
	typedef ConstYCbCr422PixelPacketFamilyBase<PARENT> _Super;

protected:
	typedef typename _Super::_Manip _Manip;

public:
	typedef typename _Super::Luminance0ComponentType Luminance0ComponentType;
	typedef typename _Super::Luminance1ComponentType Luminance1ComponentType;
	typedef typename _Super::ChromaBlueComponentType ChromaBlueComponentType;
	typedef typename _Super::ChromaRedComponentType ChromaRedComponentType;	

public:
	YCbCr422PixelPacketFamilyBase() {}

	enum { PIXEL_PER_PACKET = 2 };
	
public:
	YCbCr422PixelPacketFamilyBase(const YCbCr422PixelPacketFamilyBase &rhs) : _Super(rhs) {}
	YCbCr422PixelPacketFamilyBase(const Luminance0ComponentType &y0, const ChromaBlueComponentType &cb, const Luminance1ComponentType &y1, const ChromaRedComponentType &cr) : _Super() { setYCbYCr(y0, cb, y1, cr); }
	YCbCr422PixelPacketFamilyBase& operator=(const YCbCr422PixelPacketFamilyBase &rhs) { _Super::operator=(rhs); return *this; }

public:
	void setYCbYCr(const Luminance0ComponentType &y0, const ChromaBlueComponentType &cb, const Luminance1ComponentType &y1, const ChromaRedComponentType &cr) { _Manip::setYCbYCr(_Super::_storage, y0, cb, y1, cr); }

public:
	template<typename PIXELSRC>
	void convert(const PIXELSRC &fromPixel)
	{
		setYCbYCr(fromPixel.luminance0(), fromPixel.chromaBlue(), fromPixel.luminance1(), fromPixel.chromaRed());
	}

	template<typename PIXELSRC0, typename PIXELSRC1>
	void convert(const PIXELSRC0 &fromPixel0, const PIXELSRC1 &fromPixel1)
	{
		printf("Undefined conversion: %s + %s -> %s\n", typeid(fromPixel0).name(), typeid(fromPixel1).name(), typeid(*this).name());
		assert(0);
//		_Super::convert(fromPixel);
	}
};

//==============================================================================
// CLASS YCbCr422PixelPacketFamily
//==============================================================================
template<typename COMPONENT_STORAGE>
class YCbCr422PixelPacketFamily: public YCbCr422PixelPacketFamilyBase<Luminance0PixelFamilyBase<Luminance1PixelFamilyBase<ChromaBluePixelFamilyBase<ChromaRedPixelFamilyBase<PixelBase<COMPONENT_STORAGE, YCbCr422PixelPacketFamily<COMPONENT_STORAGE>, ConstYCbCr422PixelPacketFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE> >
{
private:
	typedef YCbCr422PixelPacketFamilyBase<Luminance0PixelFamilyBase<Luminance1PixelFamilyBase<ChromaBluePixelFamilyBase<ChromaRedPixelFamilyBase<PixelBase<COMPONENT_STORAGE, YCbCr422PixelPacketFamily<COMPONENT_STORAGE>, ConstYCbCr422PixelPacketFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE> > _Super;

public:
	typedef typename _Super::Luminance0ComponentType Luminance0ComponentType;
	typedef typename _Super::Luminance1ComponentType Luminance1ComponentType;
	typedef typename _Super::ChromaBlueComponentType ChromaBlueComponentType;
	typedef typename _Super::ChromaRedComponentType ChromaRedComponentType;

public:
	YCbCr422PixelPacketFamily() {}
	
public:
	YCbCr422PixelPacketFamily(const YCbCr422PixelPacketFamily &rhs) : _Super(rhs) {}
	YCbCr422PixelPacketFamily(const Luminance0ComponentType &y0, const ChromaBlueComponentType &cb, const Luminance1ComponentType &y1, const ChromaRedComponentType &cr) : _Super() { setYCbYCr(y0, cb, y1, cr); }
	YCbCr422PixelPacketFamily& operator=(const YCbCr422PixelPacketFamily &rhs) { _Super::_storage = rhs._storage; return *this; }
};













#endif // __ITL_YCBCR422PIXELDEFINITION_H__ 0
