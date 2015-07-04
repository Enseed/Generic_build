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
#ifndef __ITL_RGBPIXELDEFINITION_H__
#define __ITL_RGBPIXELDEFINITION_H__

#include "RedPixelDefinition.h"
#include "GreenPixelDefinition.h"
#include "BluePixelDefinition.h"
#include "AlphaPixelDefinition.h"

//==============================================================================
// FILE RGBPixelDefinition.h
//==============================================================================
// Various definitions to create RGB packed pixels (see RGBPixel.h)
//------------------------------------------------------------------------------

//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================
#include <cstddef>

//==============================================================================
// CLASS ConstRGBPixelFamily
//==============================================================================
template<typename COMPONENT_STORAGE> class RGBPixelFamily;
template<typename COMPONENT_STORAGE> class RGBAPixelFamily;

template<typename COMPONENT_STORAGE>
class ConstRGBPixelFamily: public ConstRedPixelFamilyBase<ConstGreenPixelFamilyBase<ConstBluePixelFamilyBase<ConstPixelBase<COMPONENT_STORAGE, ConstRGBPixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE>
{
private:
	typedef ConstRedPixelFamilyBase<ConstGreenPixelFamilyBase<ConstBluePixelFamilyBase<ConstPixelBase<COMPONENT_STORAGE, ConstRGBPixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE> _Super;

public:
	ConstRGBPixelFamily() {}
	
protected:
	ConstRGBPixelFamily(const ConstRGBPixelFamily &rhs) : _Super(rhs) {}
};

//==============================================================================
// CLASS RGBPixelFamilyBase
//==============================================================================
template<typename PARENT>
class RGBPixelFamilyBase: public PARENT
{
private:
	typedef PARENT _Super;

protected:
	typedef typename _Super::_Manip _Manip;

public:
	typedef typename _Super::RedComponentType RedComponentType;
	typedef typename _Super::GreenComponentType GreenComponentType;
	typedef typename _Super::BlueComponentType BlueComponentType;
	typedef typename _Super::PacketStorageType PacketStorageType;

public:
	RGBPixelFamilyBase() {}
	
public:
	RGBPixelFamilyBase(const RGBPixelFamilyBase &rhs) : _Super(rhs) {}
	RGBPixelFamilyBase(const RedComponentType &red, const GreenComponentType &green, const BlueComponentType &blue) : _Super() { setRGB(red, green, blue); }
	RGBPixelFamilyBase& operator=(const RGBPixelFamilyBase &rhs) { _Super::operator=(rhs); return *this; }

public:
	void setRGB(const RedComponentType &r, const GreenComponentType &g, const BlueComponentType &b) { _Manip::setRGB(_Super::_storage, r, g, b); }

public:
	template<typename PIXELSRC>
	void convert(const PIXELSRC &fromPixel)
	{
		_Super::convert(fromPixel);
	}
};

//==============================================================================
// CLASS RGBPixelFamily
//==============================================================================
template<typename COMPONENT_STORAGE>
class RGBPixelFamily: public RGBPixelFamilyBase<RedPixelFamilyBase<GreenPixelFamilyBase<BluePixelFamilyBase<PixelBase<COMPONENT_STORAGE, RGBPixelFamily<COMPONENT_STORAGE>, ConstRGBPixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE> >
{
private:
	typedef RGBPixelFamilyBase<RedPixelFamilyBase<GreenPixelFamilyBase<BluePixelFamilyBase<PixelBase<COMPONENT_STORAGE, RGBPixelFamily<COMPONENT_STORAGE>, ConstRGBPixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE> > _Super;

public:
	typedef typename _Super::RedComponentType RedComponentType;
	typedef typename _Super::GreenComponentType GreenComponentType;
	typedef typename _Super::BlueComponentType BlueComponentType;
	
public:
	RGBPixelFamily() {}
	
public:
	RGBPixelFamily<PacketStorageType> operator*(int val) const
	{	return RGBPixelFamily<PacketStorageType>(red()*val, green()*val, blue()*val); }

	template<class RHS_PIXEL>
	RGBPixelFamily& operator=(const RHS_PIXEL &rhs)
	{
		setRGB(rhs.red(), rhs.green(), rhs.blue());
		return *this;
	}

	template<class RHS_PIXEL>
	RGBPixelFamily& operator+=(const RHS_PIXEL &rhs)
	{
		setRGB(red()+rhs.red(), green()+rhs.green(), blue()+rhs.blue());
		return *this;
	}

	RGBPixelFamily operator+(int rhs) const
	{
		return RGBPixelFamily(red()+rhs, green()+rhs, blue()+rhs);
	}

	RGBPixelFamily operator/(int rhs) const
	{
		return RGBPixelFamily(red()/rhs, green()/rhs, blue()/rhs);
	}



public:
	RGBPixelFamily(const RGBPixelFamily &rhs) : _Super(rhs) {}
	RGBPixelFamily(const RedComponentType &red, const GreenComponentType &green, const BlueComponentType &blue) : _Super() { setRGB(red, green, blue); }
	RGBPixelFamily& operator=(const RGBPixelFamily &rhs) { _Super::_storage = rhs._storage; return *this; }

	template<class RHS_PIXEL>
	RGBPixelFamily(const RHS_PIXEL &rhs) : _Super() { setRGB(rhs.red(), rhs.green(), rhs.blue()); }
};


//==============================================================================
// CLASS ConstRGBAPixelFamily
//==============================================================================
template<typename COMPONENT_STORAGE>
class ConstRGBAPixelFamily: public ConstAlphaPixelFamilyBase<ConstRedPixelFamilyBase<ConstGreenPixelFamilyBase<ConstBluePixelFamilyBase<ConstPixelBase<COMPONENT_STORAGE, ConstRGBAPixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE>
{
private:
	typedef ConstAlphaPixelFamilyBase<ConstRedPixelFamilyBase<ConstGreenPixelFamilyBase<ConstBluePixelFamilyBase<ConstPixelBase<COMPONENT_STORAGE, ConstRGBAPixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE> _Super;

public:
	ConstRGBAPixelFamily() {}

public:
	RGBAPixelFamily<COMPONENT_STORAGE> operator*(int val) const
	{	return RGBAPixelFamily<COMPONENT_STORAGE>(red()*val, green()*val, blue()*val, alpha()*val); }

protected:
	ConstRGBAPixelFamily(const ConstRGBAPixelFamily &rhs) : _Super(rhs) {}
};

//==============================================================================
// CLASS RGBAPixelFamily
//==============================================================================
template<typename COMPONENT_STORAGE>
class RGBAPixelFamily: public AlphaPixelFamilyBase<RedPixelFamilyBase<GreenPixelFamilyBase<BluePixelFamilyBase<PixelBase<COMPONENT_STORAGE, RGBAPixelFamily<COMPONENT_STORAGE>, ConstRGBAPixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE>
{
private:
	typedef AlphaPixelFamilyBase<RedPixelFamilyBase<GreenPixelFamilyBase<BluePixelFamilyBase<PixelBase<COMPONENT_STORAGE, RGBAPixelFamily<COMPONENT_STORAGE>, ConstRGBAPixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE> _Super;

protected:
	typedef typename _Super::_Manip _Manip;

public:
	typedef typename _Super::RedComponentType RedComponentType;
	typedef typename _Super::GreenComponentType GreenComponentType;
	typedef typename _Super::BlueComponentType BlueComponentType;
	typedef typename _Super::AlphaComponentType AlphaComponentType;

public:
	RGBAPixelFamily() {}
	
public:
	RGBAPixelFamily(const RGBAPixelFamily &rhs) : _Super(rhs) {}
	RGBAPixelFamily(const RedComponentType &red, const GreenComponentType &green, const BlueComponentType &blue, const AlphaComponentType &alpha) : _Super() { setRGBA(red, green, blue, alpha); }

	template<class RHS_PIXELTYPE>
	RGBAPixelFamily(const RHS_PIXELTYPE &rhs) : _Super() { setRGBA(rhs.red(), rhs.green(), rhs.blue(), rhs.alpha()); }

	void setRGBA(const RedComponentType &r, const GreenComponentType &g, const BlueComponentType &b, const AlphaComponentType &a) { _Manip::setRGBA(_Super::_storage, r, g, b, a); }

public:
	RGBAPixelFamily<COMPONENT_STORAGE> operator*(int val) const
	{	return RGBAPixelFamily<COMPONENT_STORAGE>(red()*val, green()*val, blue()*val, alpha()*val); }

	template<class RHS_PIXEL>
	RGBAPixelFamily& operator=(const RHS_PIXEL &rhs)
	{
		setRGBA(rhs.red(), rhs.green(), rhs.blue(), rhs.alpha());
		return *this;
	}

	template<class RHS_PIXEL>
	RGBAPixelFamily& operator+=(const RHS_PIXEL &rhs)
	{
		setRGBA(red()+rhs.red(), green()+rhs.green(), blue()+rhs.blue(), alpha()+rhs.alpha());
		return *this;
	}

	RGBAPixelFamily operator+(int rhs) const
	{
		return RGBAPixelFamily(red()+rhs, green()+rhs, blue()+rhs, alpha()+rhs);
	}

	RGBAPixelFamily operator/(int rhs) const
	{
		return RGBAPixelFamily(red()/rhs, green()/rhs, blue()/rhs, alpha()/rhs);
	}

public:
	template<typename PIXELSRC>
	void convert(const PIXELSRC &fromPixel)
	{
		_Super::convert(fromPixel);
	}
};




template<class RED_COMPONENT_PACKET, class GREEN_COMPONENT_PACKET, class BLUE_COMPONENT_PACKET, typename COMPONENT_MODEL, typename COLOR_SPACE, typename RED_PARENT, typename GREEN_PARENT, typename BLUE_PARENT, typename CONST_TYPE>
class ConstRGBPlanarPixelBase: public RED_PARENT, public GREEN_PARENT, public BLUE_PARENT
{
private:
	typedef ConstRGBPlanarPixelBase<RED_COMPONENT_PACKET, GREEN_COMPONENT_PACKET, BLUE_COMPONENT_PACKET, COMPONENT_MODEL, COLOR_SPACE, RED_PARENT, GREEN_PARENT, BLUE_PARENT, CONST_TYPE> _This;

protected:
	typedef RED_PARENT _SuperRed;
	typedef GREEN_PARENT _SuperGreen;
	typedef BLUE_PARENT _SuperBlue;

public:
	typedef CONST_TYPE ConstType;

	typedef _SuperRed Plane0Type;
	typedef _SuperGreen Plane1Type;
	typedef _SuperBlue Plane2Type;

	typedef typename _SuperRed::RedStorageType Plane0Storage;
	typedef typename _SuperGreen::GreenStorageType Plane1Storage;
	typedef typename _SuperBlue::BlueStorageType Plane2Storage;


	typedef COMPONENT_MODEL ComponentModel;
	typedef COLOR_SPACE ColorSpace;
	
	enum { PLANE_COUNT = 3 };
	enum { PIXEL_PER_PACKET = 1 };

	const RED_COMPONENT_PACKET* plane0Ptr() const { return _SuperRed::redPlanePtr(); }
	const GREEN_COMPONENT_PACKET* plane1Ptr() const { return _SuperGreen::greenPlanePtr(); }
	const BLUE_COMPONENT_PACKET* plane2Ptr() const { return _SuperBlue::bluePlanePtr(); }
public:
	bool operator==(const ConstRGBPlanarPixelBase &rhs) const
	{
		return 
			_SuperRed::operator==(rhs) && 
			_SuperGreen::operator==(rhs) && 
			_SuperBlue::operator==(rhs);
	}

	ConstRGBPlanarPixelBase(typename Plane0Storage::ComponentType *planeRed, typename Plane1Storage::ComponentType *planeGreen, typename Plane2Storage::ComponentType *planeBlue)
	:
		_SuperRed((RED_COMPONENT_PACKET*)planeRed),
		_SuperGreen((GREEN_COMPONENT_PACKET*)planeGreen),
		_SuperBlue((BLUE_COMPONENT_PACKET*)planeBlue)
	{}
};


template<class RED_COMPONENT_PACKET, class GREEN_COMPONENT_PACKET, class BLUE_COMPONENT_PACKET, typename COMPONENT_MODEL, typename COLOR_SPACE>
class ConstRGBPlanarPixel: public ConstRGBPlanarPixelBase<RED_COMPONENT_PACKET, GREEN_COMPONENT_PACKET, BLUE_COMPONENT_PACKET, COMPONENT_MODEL, COLOR_SPACE, ConstRedPlanarPixel<RED_COMPONENT_PACKET>, ConstGreenPlanarPixel<GREEN_COMPONENT_PACKET>, ConstBluePlanarPixel<BLUE_COMPONENT_PACKET>, ConstRGBPlanarPixel<RED_COMPONENT_PACKET, GREEN_COMPONENT_PACKET, BLUE_COMPONENT_PACKET, COMPONENT_MODEL, COLOR_SPACE> >
{
private:
	typedef ConstRGBPlanarPixelBase<RED_COMPONENT_PACKET, GREEN_COMPONENT_PACKET, BLUE_COMPONENT_PACKET, COMPONENT_MODEL, COLOR_SPACE, ConstRedPlanarPixel<RED_COMPONENT_PACKET>, ConstGreenPlanarPixel<GREEN_COMPONENT_PACKET>, ConstBluePlanarPixel<BLUE_COMPONENT_PACKET>, ConstRGBPlanarPixel<RED_COMPONENT_PACKET, GREEN_COMPONENT_PACKET, BLUE_COMPONENT_PACKET, COMPONENT_MODEL, COLOR_SPACE> > _Super;

public:
	typedef typename _Super::Plane0Storage Plane0Storage;
	typedef typename _Super::Plane1Storage Plane1Storage;
	typedef typename _Super::Plane2Storage Plane2Storage;
	
public:
	ConstRGBPlanarPixel(typename Plane0Storage::ComponentType *planeRed, typename Plane1Storage::ComponentType *planeGreen, typename Plane2Storage::ComponentType *planeBlue)
	:
		_Super(planeRed, planeGreen, planeBlue)
	{}
};


template<class RED_COMPONENT_PACKET, class GREEN_COMPONENT_PACKET, class BLUE_COMPONENT_PACKET, typename COMPONENT_MODEL, typename COLOR_SPACE, typename RED_PARENT, typename GREEN_PARENT, typename BLUE_PARENT, typename CONST_TYPE, typename DERIVED>
class RGBPlanarPixelBase: public ConstRGBPlanarPixelBase<RED_COMPONENT_PACKET, GREEN_COMPONENT_PACKET, BLUE_COMPONENT_PACKET, COMPONENT_MODEL, COLOR_SPACE, RED_PARENT, GREEN_PARENT, BLUE_PARENT, CONST_TYPE>
{
private:
	typedef ConstRGBPlanarPixelBase<RED_COMPONENT_PACKET, GREEN_COMPONENT_PACKET, BLUE_COMPONENT_PACKET, COMPONENT_MODEL, COLOR_SPACE, RED_PARENT, GREEN_PARENT, BLUE_PARENT, CONST_TYPE> _Super;
	typedef typename _Super::_SuperRed _SuperRed;
	typedef typename _Super::_SuperGreen _SuperGreen;
	typedef typename _Super::_SuperBlue _SuperBlue;

public:
	typedef typename _Super::ConstType ConstType;

	typedef typename _SuperRed::RedStorageType Plane0Storage;
	typedef typename _SuperGreen::GreenStorageType Plane1Storage;
	typedef typename _SuperBlue::BlueStorageType Plane2Storage;

	template<typename PIXELSRC>
	void convert(const PIXELSRC &fromPixel)
	{
		setRed(PixelConvertExtractRed<PIXELSRC, DERIVED>::eval(fromPixel));
		setGreen(PixelConvertExtractGreen<PIXELSRC, DERIVED>::eval(fromPixel));
		setBlue(PixelConvertExtractGreen<PIXELSRC, DERIVED>::eval(fromPixel));
	}

	using _Super::plane0Ptr;
	RED_COMPONENT_PACKET* plane0Ptr() { return _SuperRed::redPlanePtr(); }

	using _Super::plane1Ptr;
	GREEN_COMPONENT_PACKET* plane1Ptr() { return _SuperGreen::greenPlanePtr(); }

	using _Super::plane2Ptr;
	BLUE_COMPONENT_PACKET* plane2Ptr() { return _SuperBlue::bluePlanePtr(); }

	RGBPlanarPixelBase(typename Plane0Storage::ComponentType *planeRed, typename Plane1Storage::ComponentType *planeGreen, typename Plane2Storage::ComponentType *planeBlue)
	:
		_Super(planeRed, planeGreen, planeBlue)
	{}

};


template<class RED_COMPONENT_PACKET, class GREEN_COMPONENT_PACKET, class BLUE_COMPONENT_PACKET, typename COMPONENT_MODEL, typename COLOR_SPACE>
class RGBPlanarPixel: public RGBPlanarPixelBase<RED_COMPONENT_PACKET, GREEN_COMPONENT_PACKET, BLUE_COMPONENT_PACKET, COMPONENT_MODEL, COLOR_SPACE, RedPlanarPixel<RED_COMPONENT_PACKET>, GreenPlanarPixel<GREEN_COMPONENT_PACKET>, BluePlanarPixel<BLUE_COMPONENT_PACKET>, ConstRGBPlanarPixel<RED_COMPONENT_PACKET, GREEN_COMPONENT_PACKET, BLUE_COMPONENT_PACKET, COMPONENT_MODEL, COLOR_SPACE>, RGBPlanarPixel<RED_COMPONENT_PACKET, GREEN_COMPONENT_PACKET, BLUE_COMPONENT_PACKET, COMPONENT_MODEL, COLOR_SPACE> >
{
private:
	typedef RGBPlanarPixelBase<RED_COMPONENT_PACKET, GREEN_COMPONENT_PACKET, BLUE_COMPONENT_PACKET, COMPONENT_MODEL, COLOR_SPACE, RedPlanarPixel<RED_COMPONENT_PACKET>, GreenPlanarPixel<GREEN_COMPONENT_PACKET>, BluePlanarPixel<BLUE_COMPONENT_PACKET>, ConstRGBPlanarPixel<RED_COMPONENT_PACKET, GREEN_COMPONENT_PACKET, BLUE_COMPONENT_PACKET, COMPONENT_MODEL, COLOR_SPACE>, RGBPlanarPixel<RED_COMPONENT_PACKET, GREEN_COMPONENT_PACKET, BLUE_COMPONENT_PACKET, COMPONENT_MODEL, COLOR_SPACE> > _Super;

public:
	typedef typename _Super::Plane0Storage Plane0Storage;
	typedef typename _Super::Plane1Storage Plane1Storage;
	typedef typename _Super::Plane2Storage Plane2Storage;

	RGBPlanarPixel(typename Plane0Storage::ComponentType *planeRed, typename Plane1Storage::ComponentType *planeGreen, typename Plane2Storage::ComponentType *planeBlue)
	:
		_Super(planeRed, planeGreen, planeBlue)
	{}
};




#endif // __ITL_RGBPIXELDEFINITION_H__
