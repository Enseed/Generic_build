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
#ifndef __ITL_CMYPIXELDEFINITION_H__
#define __ITL_CMYPIXELDEFINITION_H__

#include "CyanPixelDefinition.h"
#include "MagentaPixelDefinition.h"
#include "YellowPixelDefinition.h"
#include "../RGB/AlphaPixelDefinition.h"

//==============================================================================
// FILE CMYPixelDefinition.h
//==============================================================================
// Various definitions to create CMY packed pixels (see CMYPixel.h)
//------------------------------------------------------------------------------

//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================
#include <cstddef>

//==============================================================================
// CLASS ConstCMYPixelFamily
//==============================================================================
template<typename PARENT>
class ConstCMYPixelFamilyBase: public PARENT
{
private:
	typedef PARENT _Super;

public:
	ConstCMYPixelFamilyBase() {}
	
protected:
	ConstCMYPixelFamilyBase(const ConstCMYPixelFamilyBase &rhs) : _Super(rhs) {}
};

//==============================================================================
// CLASS ConstCMYPixelFamily
//==============================================================================
template<typename COMPONENT_STORAGE>
class ConstCMYPixelFamily: public ConstCMYPixelFamilyBase<ConstCyanPixelFamilyBase<ConstMagentaPixelFamilyBase<ConstYellowPixelFamilyBase<ConstPixelBase<COMPONENT_STORAGE, ConstCMYPixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE> >
{
private:
	typedef ConstCyanPixelFamilyBase<ConstMagentaPixelFamilyBase<ConstYellowPixelFamilyBase<ConstPixelBase<COMPONENT_STORAGE, ConstCMYPixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE> _Super;

public:
	ConstCMYPixelFamily() {}
	
protected:
	ConstCMYPixelFamily(const ConstCMYPixelFamily &rhs) : _Super(rhs) {}
};

//==============================================================================
// CLASS CMYPixelFamilyBase
//==============================================================================
template<typename PARENT>
class CMYPixelFamilyBase: public PARENT
{
private:
	typedef PARENT _Super;

protected:
	typedef typename _Super::_Manip _Manip;

public:
	typedef typename _Super::CyanComponentType CyanComponentType;
	typedef typename _Super::MagentaComponentType MagentaComponentType;
	typedef typename _Super::YellowComponentType YellowComponentType;

public:
	CMYPixelFamilyBase() {}
	
public:
	CMYPixelFamilyBase(const CMYPixelFamilyBase &rhs) : _Super(rhs) {}
	CMYPixelFamilyBase(const CyanComponentType &cyan, const MagentaComponentType &magenta, const YellowComponentType &yellow) : _Super() { setCMY(cyan, magenta, yellow); }
	CMYPixelFamilyBase& operator=(const CMYPixelFamilyBase &rhs) { _Super::operator=(rhs); return *this; }

public:
	void setCMY(const CyanComponentType &r, const MagentaComponentType &g, const YellowComponentType &b) { _Manip::setCMY(_Super::_storage, r, g, b); }

public:
	template<typename PIXELSRC>
	void convert(const PIXELSRC &fromPixel)
	{
		_Super::convert(fromPixel);
	}
};

//==============================================================================
// CLASS CMYPixelFamily
//==============================================================================
template<typename COMPONENT_STORAGE>
class CMYPixelFamily: public CMYPixelFamilyBase<CyanPixelFamilyBase<MagentaPixelFamilyBase<YellowPixelFamilyBase<PixelBase<COMPONENT_STORAGE, CMYPixelFamily<COMPONENT_STORAGE>, ConstCMYPixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE> >
{
private:
	typedef CMYPixelFamilyBase<CyanPixelFamilyBase<MagentaPixelFamilyBase<YellowPixelFamilyBase<PixelBase<COMPONENT_STORAGE, CMYPixelFamily<COMPONENT_STORAGE>, ConstCMYPixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE> > _Super;

public:
	typedef typename _Super::CyanComponentType CyanComponentType;
	typedef typename _Super::MagentaComponentType MagentaComponentType;
	typedef typename _Super::YellowComponentType YellowComponentType;

public:
	CMYPixelFamily() {}
	
public:
	CMYPixelFamily(const CMYPixelFamily &rhs) : _Super(rhs) {}
	CMYPixelFamily(const CyanComponentType &cyan, const MagentaComponentType &magenta, const YellowComponentType &yellow) : _Super() { setCMY(cyan, magenta, yellow); }
	CMYPixelFamily& operator=(const CMYPixelFamily &rhs) { _Super::_storage = rhs._storage; return *this; }
};


//==============================================================================
// CLASS ConstCMYAPixelFamily
//==============================================================================
template<typename COMPONENT_STORAGE>
class ConstCMYAPixelFamily: public ConstAlphaPixelFamilyBase<ConstCyanPixelFamilyBase<ConstMagentaPixelFamilyBase<ConstYellowPixelFamilyBase<ConstPixelBase<COMPONENT_STORAGE, ConstCMYAPixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE>
{
private:
	typedef ConstAlphaPixelFamilyBase<ConstCyanPixelFamilyBase<ConstMagentaPixelFamilyBase<ConstYellowPixelFamilyBase<ConstPixelBase<COMPONENT_STORAGE, ConstCMYAPixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE> _Super;

public:
	ConstCMYAPixelFamily() {}
	
protected:
	ConstCMYAPixelFamily(const ConstCMYAPixelFamily &rhs) : _Super(rhs) {}
};

//==============================================================================
// CLASS CMYAPixelFamily
//==============================================================================
template<typename COMPONENT_STORAGE>
class CMYAPixelFamily: public AlphaPixelFamilyBase<CyanPixelFamilyBase<MagentaPixelFamilyBase<YellowPixelFamilyBase<PixelBase<COMPONENT_STORAGE, CMYAPixelFamily<COMPONENT_STORAGE>, ConstCMYAPixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE>
{
private:
	typedef AlphaPixelFamilyBase<CyanPixelFamilyBase<MagentaPixelFamilyBase<YellowPixelFamilyBase<PixelBase<COMPONENT_STORAGE, CMYAPixelFamily<COMPONENT_STORAGE>, ConstCMYAPixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE> _Super;

protected:
	typedef typename _Super::_Manip _Manip;

public:
	typedef typename _Super::CyanComponentType CyanComponentType;
	typedef typename _Super::MagentaComponentType MagentaComponentType;
	typedef typename _Super::YellowComponentType YellowComponentType;
	typedef typename _Super::AlphaComponentType AlphaComponentType;

public:
	CMYAPixelFamily() {}
	
public:
	CMYAPixelFamily(const CMYAPixelFamily &rhs) : _Super(rhs) {}
	CMYAPixelFamily(const CyanComponentType &cyan, const MagentaComponentType &magenta, const YellowComponentType &yellow, const AlphaComponentType &alpha) : _Super() { setCMYA(cyan, magenta, yellow, alpha); }

	void setCMYA(const CyanComponentType &r, const MagentaComponentType &g, const YellowComponentType &b, const AlphaComponentType &a) { _Manip::setCMYA(_Super::_storage, r, g, b, a); }

public:
	template<typename PIXELSRC>
	void convert(const PIXELSRC &fromPixel)
	{
		_Super::convert(fromPixel);
	}
};


#endif // __ITL_CMYPIXELDEFINITION_H__
