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
#ifndef __ITL_YCBCRPIXELDEFINITION_H__
#define __ITL_YCBCRPIXELDEFINITION_H__

#include "../Storage/PixelManipulation.h"

#include "LuminancePixelDefinition.h"
#include "ChromaBluePixelDefinition.h"
#include "ChromaRedPixelDefinition.h"
#include "../RGB/AlphaPixelDefinition.h"


//==============================================================================
// CLASS ConstYCbCrPixelFamily
//==============================================================================
template<typename PARENT>
class ConstYCbCrPixelFamilyBase: public PARENT
{
private:
	typedef PARENT _Super;

public:
	ConstYCbCrPixelFamilyBase() {}
	
protected:
	ConstYCbCrPixelFamilyBase(const ConstYCbCrPixelFamilyBase &rhs) : _Super(rhs) {}
};


//==============================================================================
// CLASS ConstYCbCrPixelFamily
//==============================================================================
template<typename COMPONENT_STORAGE>
class ConstYCbCrPixelFamily: public ConstYCbCrPixelFamilyBase<ConstLuminancePixelFamilyBase<ConstChromaBluePixelFamilyBase<ConstChromaRedPixelFamilyBase<ConstPixelBase<COMPONENT_STORAGE, ConstYCbCrPixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE> >
{
private:
	typedef ConstYCbCrPixelFamilyBase<ConstLuminancePixelFamilyBase<ConstChromaBluePixelFamilyBase<ConstChromaRedPixelFamilyBase<ConstPixelBase<COMPONENT_STORAGE, ConstYCbCrPixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE> > _Super;

public:
	ConstYCbCrPixelFamily() {}
	
protected:
	ConstYCbCrPixelFamily(const ConstYCbCrPixelFamily &rhs) : _Super(rhs) {}
};

//==============================================================================
// CLASS YCbCrPixelFamilyBase
//==============================================================================
template<typename PARENT>
class YCbCrPixelFamilyBase: public PARENT
{
private:
	typedef PARENT _Super;

protected:
	typedef typename _Super::_Manip _Manip;

public:
	typedef typename _Super::LuminanceComponentType LuminanceComponentType;
	typedef typename _Super::ChromaBlueComponentType ChromaBlueComponentType;
	typedef typename _Super::ChromaRedComponentType ChromaRedComponentType;

public:
	YCbCrPixelFamilyBase() {}
	
public:
	YCbCrPixelFamilyBase(const YCbCrPixelFamilyBase &rhs) : _Super(rhs) {}
	YCbCrPixelFamilyBase(const LuminanceComponentType &y, const ChromaBlueComponentType &cb, const ChromaRedComponentType &cr) : _Super() { setYCbCr(y, cb, cr); }
	YCbCrPixelFamilyBase& operator=(const YCbCrPixelFamilyBase &rhs) { _Super::operator=(rhs); return *this; }

public:
	void setYCbCr(const LuminanceComponentType &r, const ChromaBlueComponentType &g, const ChromaRedComponentType &b) { _Manip::setYCbCr(_Super::_storage, r, g, b); }

public:
	template<typename PIXELSRC>
	void convert(const PIXELSRC &fromPixel)
	{
		_Super::convert(fromPixel);
	}
};

//==============================================================================
// CLASS YCbCrPixelFamily
//==============================================================================
template<typename COMPONENT_STORAGE>
class YCbCrPixelFamily: public YCbCrPixelFamilyBase<LuminancePixelFamilyBase<ChromaBluePixelFamilyBase<ChromaRedPixelFamilyBase<PixelBase<COMPONENT_STORAGE, YCbCrPixelFamily<COMPONENT_STORAGE>, ConstYCbCrPixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE> >
{
private:
	typedef YCbCrPixelFamilyBase<LuminancePixelFamilyBase<ChromaBluePixelFamilyBase<ChromaRedPixelFamilyBase<PixelBase<COMPONENT_STORAGE, YCbCrPixelFamily<COMPONENT_STORAGE>, ConstYCbCrPixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE> > _Super;

public:
	typedef typename _Super::LuminanceComponentType LuminanceComponentType;
	typedef typename _Super::ChromaBlueComponentType ChromaBlueComponentType;
	typedef typename _Super::ChromaRedComponentType ChromaRedComponentType;

public:
	YCbCrPixelFamily() {}
	
public:
	YCbCrPixelFamily(const YCbCrPixelFamily &rhs) : _Super(rhs) {}
	YCbCrPixelFamily(const LuminanceComponentType &y, const ChromaBlueComponentType &cb, const ChromaRedComponentType &cr) : _Super() { setYCbCr(y, cb, cr); }
	YCbCrPixelFamily& operator=(const YCbCrPixelFamily &rhs) { _Super::_storage = rhs._storage; return *this; }
};

//==============================================================================
// CLASS ConstYCbCrAPixelFamily
//==============================================================================
template<typename COMPONENT_STORAGE, typename DEFINITION_Y, typename DEFINITION_CB, typename DEFINITION_CR, typename DEFINITION_A>
class ConstYCbCrAPixelFamily: public ConstAlphaPixelFamilyBase<ConstLuminancePixelFamilyBase<ConstChromaBluePixelFamilyBase<ConstChromaRedPixelFamilyBase<ConstPixelBase<COMPONENT_STORAGE, ConstYCbCrAPixelFamily<COMPONENT_STORAGE, DEFINITION_Y, DEFINITION_CB, DEFINITION_CR, DEFINITION_A> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE>
{
private:
	typedef ConstAlphaPixelFamilyBase<ConstLuminancePixelFamilyBase<ConstChromaBluePixelFamilyBase<ConstChromaRedPixelFamilyBase<ConstPixelBase<COMPONENT_STORAGE, ConstYCbCrAPixelFamily<COMPONENT_STORAGE, DEFINITION_Y, DEFINITION_CB, DEFINITION_CR, DEFINITION_A> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE> _Super;

public:
	ConstYCbCrAPixelFamily() {}

protected:
	ConstYCbCrAPixelFamily(const ConstYCbCrAPixelFamily &rhs) : _Super(rhs) {}
};


//==============================================================================
// CLASS YCbCrAPixelFamily
//==============================================================================
template<typename COMPONENT_STORAGE, typename DEFINITION_Y, typename DEFINITION_CB, typename DEFINITION_CR, typename DEFINITION_A>
class YCbCrAPixelFamily: public AlphaPixelFamilyBase<LuminancePixelFamilyBase<ChromaBluePixelFamilyBase<ChromaRedPixelFamilyBase<PixelBase<COMPONENT_STORAGE, YCbCrAPixelFamily<COMPONENT_STORAGE, DEFINITION_Y, DEFINITION_CB, DEFINITION_CR, DEFINITION_A>, ConstYCbCrAPixelFamily<COMPONENT_STORAGE, DEFINITION_Y, DEFINITION_CB, DEFINITION_CR, DEFINITION_A> >, DEFINITION_CR>, DEFINITION_CB>, DEFINITION_Y>, DEFINITION_A>
{
private:
	typedef AlphaPixelFamilyBase<LuminancePixelFamilyBase<ChromaBluePixelFamilyBase<ChromaRedPixelFamilyBase<PixelBase<COMPONENT_STORAGE, YCbCrAPixelFamily<COMPONENT_STORAGE, DEFINITION_Y, DEFINITION_CB, DEFINITION_CR, DEFINITION_A>, ConstYCbCrAPixelFamily<COMPONENT_STORAGE, DEFINITION_Y, DEFINITION_CB, DEFINITION_CR, DEFINITION_A> >, DEFINITION_CR>, DEFINITION_CB>, DEFINITION_Y>, DEFINITION_A> _Super;

protected:
	typedef typename _Super::_Manip _Manip;

public:
	typedef typename _Super::LuminanceComponentType LuminanceComponentType;
	typedef typename _Super::ChromaBlueComponentType ChromaBlueComponentType;
	typedef typename _Super::ChromaRedComponentType ChromaRedComponentType;
	typedef typename _Super::AlphaComponentType AlphaComponentType;

public:
	YCbCrAPixelFamily() {}
	
public:
	YCbCrAPixelFamily(const YCbCrAPixelFamily &rhs) : _Super(rhs) {}
	YCbCrAPixelFamily(const LuminanceComponentType &y, const ChromaBlueComponentType &cb, const ChromaRedComponentType &cr, const AlphaComponentType &alpha) : _Super() { setYCbCrA(y, cb, cr, alpha); }

	void setYCbCrA(const LuminanceComponentType &r, const ChromaBlueComponentType &g, const ChromaRedComponentType &b, const AlphaComponentType &a) { _Manip::setYCbCrA(_Super::_storage, r, g, b, a); }

public:
	template<typename PIXELSRC>
	void convert(const PIXELSRC &fromPixel)
	{
		_Super::convert(fromPixel);
	}
};

//==============================================================================
// CLASS ConstYAPixelFamily
//==============================================================================
template<typename COMPONENT_STORAGE, typename DEFINITION_Y, typename DEFINITION_A>
class ConstYAPixelFamily: public ConstAlphaPixelFamilyBase<ConstLuminancePixelFamilyBase<ConstChromaBluePixelFamilyBase<ConstChromaRedPixelFamilyBase<ConstPixelBase<COMPONENT_STORAGE, ConstYAPixelFamily<COMPONENT_STORAGE, DEFINITION_Y, DEFINITION_A> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE>
{
private:
	typedef ConstAlphaPixelFamilyBase<ConstLuminancePixelFamilyBase<ConstChromaBluePixelFamilyBase<ConstChromaRedPixelFamilyBase<ConstPixelBase<COMPONENT_STORAGE, ConstYAPixelFamily<COMPONENT_STORAGE, DEFINITION_Y, DEFINITION_A> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE> _Super;

public:
	ConstYAPixelFamily() {}

protected:
	ConstYAPixelFamily(const ConstYAPixelFamily &rhs) : _Super(rhs) {}
};


template<typename COMPONENT_STORAGE, typename DEFINITION_Y, typename DEFINITION_A>
class YAPixelFamily: public AlphaPixelFamilyBase<LuminancePixelFamilyBase<PixelBase<COMPONENT_STORAGE, YAPixelFamily<COMPONENT_STORAGE, DEFINITION_Y, DEFINITION_A>, ConstYAPixelFamily<COMPONENT_STORAGE, DEFINITION_Y, DEFINITION_A> >, DEFINITION_Y>, DEFINITION_A>
{
private:
	typedef AlphaPixelFamilyBase<LuminancePixelFamilyBase<PixelBase<COMPONENT_STORAGE, YAPixelFamily<COMPONENT_STORAGE, DEFINITION_Y, DEFINITION_A>, ConstYAPixelFamily<COMPONENT_STORAGE, DEFINITION_Y, DEFINITION_A> >, DEFINITION_Y>, DEFINITION_A> _Super;

protected:
	typedef typename _Super::_Manip _Manip;

public:
	typedef typename _Super::LuminanceComponentType LuminanceComponentType;
	typedef typename _Super::AlphaComponentType AlphaComponentType;

public:
	YAPixelFamily() {}

public:
	YAPixelFamily(const YAPixelFamily &rhs) : _Super(rhs) {}
	YAPixelFamily(const LuminanceComponentType &y, const AlphaComponentType &alpha) : _Super() { setYA(y, cb, cr, alpha); }

	void setYA(const LuminanceComponentType &r, const AlphaComponentType &a) { _Manip::setYA(_Super::_storage, r, a); }

public:
	template<typename PIXELSRC>
	void convert(const PIXELSRC &fromPixel)
	{
		_Super::convert(fromPixel);
	}
};










template<class LUMINANCE_COMPONENT_PACKET, class CHROMABLUE_COMPONENT_PACKET, class CHROMARED_COMPONENT_PACKET, typename COMPONENT_MODEL, typename COLOR_SPACE, typename LUMINANCE_PARENT, typename CHROMABLUE_PARENT, typename CHROMARED_PARENT, typename CONST_TYPE>
class ConstYCbCrPlanarPixelBase: public LUMINANCE_PARENT, public CHROMABLUE_PARENT, public CHROMARED_PARENT
{
private:
	typedef ConstYCbCrPlanarPixelBase<LUMINANCE_COMPONENT_PACKET, CHROMABLUE_COMPONENT_PACKET, CHROMARED_COMPONENT_PACKET, COMPONENT_MODEL, COLOR_SPACE, LUMINANCE_PARENT, CHROMABLUE_PARENT, CHROMARED_PARENT, CONST_TYPE> _This;

protected:
	typedef LUMINANCE_PARENT _SuperLuminance;
	typedef CHROMABLUE_PARENT _SuperChromaBlue;
	typedef CHROMARED_PARENT _SuperChromaRed;

public:
	typedef CONST_TYPE ConstType;

	typedef typename _SuperLuminance Plane0Type;
	typedef typename _SuperChromaBlue Plane1Type;
	typedef typename _SuperChromaRed Plane2Type;

	typedef typename _SuperLuminance::LuminanceStorageType Plane0Storage;
	typedef typename _SuperChromaBlue::ChromaBlueStorageType Plane1Storage;
	typedef typename _SuperChromaRed::ChromaRedStorageType Plane2Storage;
	typedef COMPONENT_MODEL ComponentModel;
	typedef COLOR_SPACE ColorSpace;
	
	enum { PLANE_COUNT = 3 };
	enum { PIXEL_PER_PACKET = 1 };

	const LUMINANCE_COMPONENT_PACKET* plane0Ptr() const { return _SuperLuminance::luminancePlanePtr(); }
	const CHROMABLUE_COMPONENT_PACKET* plane1Ptr() const { return _SuperChromaBlue::chromaBluePlanePtr(); }
	const CHROMARED_COMPONENT_PACKET* plane2Ptr() const { return _SuperChromaRed::chromaRedPlanePtr(); }
public:
	bool operator==(const ConstYCbCrPlanarPixelBase &rhs) const
	{
		return 
			_SuperLuminance::operator==(rhs) && 
			_SuperChromaBlue::operator==(rhs) && 
			_SuperChromaRed::operator==(rhs);
	}

	ConstYCbCrPlanarPixelBase(typename Plane0Storage::ComponentType *planeLuminance, typename Plane1Storage::ComponentType *planeChromaBlue, typename Plane2Storage::ComponentType *planeChromaRed)
	:
		_SuperLuminance((LUMINANCE_COMPONENT_PACKET*)planeLuminance),
		_SuperChromaBlue((CHROMABLUE_COMPONENT_PACKET*)planeChromaBlue),
		_SuperChromaRed((CHROMARED_COMPONENT_PACKET*)planeChromaRed)
	{}
};


template<class LUMINANCE_COMPONENT_PACKET, class CHROMABLUE_COMPONENT_PACKET, class CHROMARED_COMPONENT_PACKET, typename COMPONENT_MODEL, typename COLOR_SPACE>
class ConstYCbCrPlanarPixel: public ConstYCbCrPlanarPixelBase<LUMINANCE_COMPONENT_PACKET, CHROMABLUE_COMPONENT_PACKET, CHROMARED_COMPONENT_PACKET, COMPONENT_MODEL, COLOR_SPACE, ConstLuminancePlanarPixel<LUMINANCE_COMPONENT_PACKET>, ConstChromaBluePlanarPixel<CHROMABLUE_COMPONENT_PACKET>, ConstChromaRedPlanarPixel<CHROMARED_COMPONENT_PACKET>, ConstYCbCrPlanarPixel<LUMINANCE_COMPONENT_PACKET, CHROMABLUE_COMPONENT_PACKET, CHROMARED_COMPONENT_PACKET, COMPONENT_MODEL, COLOR_SPACE> >
{
private:
	typedef ConstYCbCrPlanarPixelBase<LUMINANCE_COMPONENT_PACKET, CHROMABLUE_COMPONENT_PACKET, CHROMARED_COMPONENT_PACKET, COMPONENT_MODEL, COLOR_SPACE, ConstLuminancePlanarPixel<LUMINANCE_COMPONENT_PACKET>, ConstChromaBluePlanarPixel<CHROMABLUE_COMPONENT_PACKET>, ConstChromaRedPlanarPixel<CHROMARED_COMPONENT_PACKET>, ConstYCbCrPlanarPixel<LUMINANCE_COMPONENT_PACKET, CHROMABLUE_COMPONENT_PACKET, CHROMARED_COMPONENT_PACKET, COMPONENT_MODEL, COLOR_SPACE> > _Super;

public:
	typedef typename _Super::Plane0Storage Plane0Storage;
	typedef typename _Super::Plane1Storage Plane1Storage;
	typedef typename _Super::Plane2Storage Plane2Storage;
	
public:
	ConstYCbCrPlanarPixel(typename Plane0Storage::ComponentType *planeLuminance, typename Plane1Storage::ComponentType *planeChromaBlue, typename Plane2Storage::ComponentType *planeChromaRed)
	:
		_Super(planeLuminance, planeChromaBlue, planeChromaRed)
	{}
};


template<class LUMINANCE_COMPONENT_PACKET, class CHROMABLUE_COMPONENT_PACKET, class CHROMARED_COMPONENT_PACKET, typename COMPONENT_MODEL, typename COLOR_SPACE, typename LUMINANCE_PARENT, typename CHROMABLUE_PARENT, typename CHROMARED_PARENT, typename CONST_TYPE, typename DERIVED>
class YCbCrPlanarPixelBase: public ConstYCbCrPlanarPixelBase<LUMINANCE_COMPONENT_PACKET, CHROMABLUE_COMPONENT_PACKET, CHROMARED_COMPONENT_PACKET, COMPONENT_MODEL, COLOR_SPACE, LUMINANCE_PARENT, CHROMABLUE_PARENT, CHROMARED_PARENT, CONST_TYPE>
{
private:
	typedef ConstYCbCrPlanarPixelBase<LUMINANCE_COMPONENT_PACKET, CHROMABLUE_COMPONENT_PACKET, CHROMARED_COMPONENT_PACKET, COMPONENT_MODEL, COLOR_SPACE, LUMINANCE_PARENT, CHROMABLUE_PARENT, CHROMARED_PARENT, CONST_TYPE> _Super;
	typedef typename _Super::_SuperLuminance _SuperLuminance;
	typedef typename _Super::_SuperChromaBlue _SuperChromaBlue;
	typedef typename _Super::_SuperChromaRed _SuperChromaRed;

public:
	typedef typename _Super::ConstType ConstType;

	typedef typename _SuperLuminance::LuminanceStorageType Plane0Storage;
	typedef typename _SuperChromaBlue::ChromaBlueStorageType Plane1Storage;
	typedef typename _SuperChromaRed::ChromaRedStorageType Plane2Storage;

	template<typename PIXELSRC>
	void convert(const PIXELSRC &fromPixel)
	{
		setLuminance(PixelConvertExtractLuminance<PIXELSRC, DERIVED>::eval(fromPixel));
		setChromaBlue(PixelConvertExtractChromaBlue<PIXELSRC, DERIVED>::eval(fromPixel));
		setChromaRed(PixelConvertExtractChromaBlue<PIXELSRC, DERIVED>::eval(fromPixel));
	}

	using _Super::plane0Ptr;
	LUMINANCE_COMPONENT_PACKET* plane0Ptr() { return _SuperLuminance::luminancePlanePtr(); }

	using _Super::plane1Ptr;
	CHROMABLUE_COMPONENT_PACKET* plane1Ptr() { return _SuperChromaBlue::chromaBluePlanePtr(); }

	using _Super::plane2Ptr;
	CHROMARED_COMPONENT_PACKET* plane2Ptr() { return _SuperChromaRed::chromaRedPlanePtr(); }

	YCbCrPlanarPixelBase(typename Plane0Storage::ComponentType *planeLuminance, typename Plane1Storage::ComponentType *planeChromaBlue, typename Plane2Storage::ComponentType *planeChromaRed)
	:
		_Super(planeLuminance, planeChromaBlue, planeChromaRed)
	{}

};


template<class LUMINANCE_COMPONENT_PACKET, class CHROMABLUE_COMPONENT_PACKET, class CHROMARED_COMPONENT_PACKET, typename COMPONENT_MODEL, typename COLOR_SPACE>
class YCbCrPlanarPixel: public YCbCrPlanarPixelBase<LUMINANCE_COMPONENT_PACKET, CHROMABLUE_COMPONENT_PACKET, CHROMARED_COMPONENT_PACKET, COMPONENT_MODEL, COLOR_SPACE, LuminancePlanarPixel<LUMINANCE_COMPONENT_PACKET>, ChromaBluePlanarPixel<CHROMABLUE_COMPONENT_PACKET>, ChromaRedPlanarPixel<CHROMARED_COMPONENT_PACKET>, ConstYCbCrPlanarPixel<LUMINANCE_COMPONENT_PACKET, CHROMABLUE_COMPONENT_PACKET, CHROMARED_COMPONENT_PACKET, COMPONENT_MODEL, COLOR_SPACE>, YCbCrPlanarPixel<LUMINANCE_COMPONENT_PACKET, CHROMABLUE_COMPONENT_PACKET, CHROMARED_COMPONENT_PACKET, COMPONENT_MODEL, COLOR_SPACE> >
{
private:
	typedef YCbCrPlanarPixelBase<LUMINANCE_COMPONENT_PACKET, CHROMABLUE_COMPONENT_PACKET, CHROMARED_COMPONENT_PACKET, COMPONENT_MODEL, COLOR_SPACE, LuminancePlanarPixel<LUMINANCE_COMPONENT_PACKET>, ChromaBluePlanarPixel<CHROMABLUE_COMPONENT_PACKET>, ChromaRedPlanarPixel<CHROMARED_COMPONENT_PACKET>, ConstYCbCrPlanarPixel<LUMINANCE_COMPONENT_PACKET, CHROMABLUE_COMPONENT_PACKET, CHROMARED_COMPONENT_PACKET, COMPONENT_MODEL, COLOR_SPACE>, YCbCrPlanarPixel<LUMINANCE_COMPONENT_PACKET, CHROMABLUE_COMPONENT_PACKET, CHROMARED_COMPONENT_PACKET, COMPONENT_MODEL, COLOR_SPACE> > _Super;

public:
	typedef typename _Super::Plane0Storage Plane0Storage;
	typedef typename _Super::Plane1Storage Plane1Storage;
	typedef typename _Super::Plane2Storage Plane2Storage;

	YCbCrPlanarPixel(typename Plane0Storage::ComponentType *planeLuminance, typename Plane1Storage::ComponentType *planeChromaBlue, typename Plane2Storage::ComponentType *planeChromaRed)
	:
		_Super(planeLuminance, planeChromaBlue, planeChromaRed)
	{}

};



#endif // __ITL_YCBCRPIXELDEFINITION_H__
