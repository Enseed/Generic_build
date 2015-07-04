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
#ifndef __ITL_CMYKPIXELDEFINITION_H__
#define __ITL_CMYKPIXELDEFINITION_H__

#include "CMYPixelDefinition.h"
#include "BlackPixelDefinition.h"

//==============================================================================
// FILE CMYPixelDefinition.h
//==============================================================================
// Various definitions to create CMYK packed pixels (see CMYKPixel.h)
//------------------------------------------------------------------------------

//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================
#include <cstddef>

//==============================================================================
// CLASS ConstCMYKPixelFamily
//==============================================================================
template<typename COMPONENT_STORAGE>
class ConstCMYKPixelFamily: public ConstCMYPixelFamilyBase<ConstBlackPixelFamilyBase<ConstCyanPixelFamilyBase<ConstMagentaPixelFamilyBase<ConstYellowPixelFamilyBase<ConstPixelBase<COMPONENT_STORAGE, ConstCMYKPixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE> >
{
private:
	typedef ConstCMYPixelFamilyBase<ConstBlackPixelFamilyBase<ConstCyanPixelFamilyBase<ConstMagentaPixelFamilyBase<ConstYellowPixelFamilyBase<ConstPixelBase<COMPONENT_STORAGE, ConstCMYKPixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE> > _Super;

public:
	ConstCMYKPixelFamily() {}
	
protected:
	ConstCMYKPixelFamily(const ConstCMYKPixelFamily &rhs) : _Super(rhs) {}
};

//==============================================================================
// CLASS CMYKPixelFamilyBase
//==============================================================================
template<typename PARENT>
class CMYKPixelFamilyBase: public PARENT
{
private:
	typedef PARENT _Super;

protected:
	typedef typename _Super::_Manip _Manip;

public:
	typedef typename _Super::CyanComponentType CyanComponentType;
	typedef typename _Super::MagentaComponentType MagentaComponentType;
	typedef typename _Super::YellowComponentType YellowComponentType;
	typedef typename _Super::BlackComponentType BlackComponentType;

public:
	CMYKPixelFamilyBase() {}
	
public:
	CMYKPixelFamilyBase(const CMYKPixelFamilyBase &rhs) : _Super(rhs) {}
	CMYKPixelFamilyBase(const CyanComponentType &cyan, const MagentaComponentType &magenta, const YellowComponentType &yellow, const BlackComponentType &black) : _Super() { setCMYK(cyan, magenta, yellow, black); }
	CMYKPixelFamilyBase& operator=(const CMYKPixelFamilyBase &rhs) { _Super::operator=(rhs); return *this; }

public:
	void setCMYK(const CyanComponentType &c, const MagentaComponentType &m, const YellowComponentType &y, const YellowComponentType &k) { _Manip::setCMYK(_Super::_storage, c, m, y, k); }

public:
	template<typename PIXELSRC>
	void convert(const PIXELSRC &fromPixel)
	{
		_Super::convert(fromPixel);
	}
};

//==============================================================================
// CLASS CMYKPixelFamily
//==============================================================================
template<typename COMPONENT_STORAGE>
class CMYKPixelFamily: public CMYKPixelFamilyBase<BlackPixelFamilyBase<CyanPixelFamilyBase<MagentaPixelFamilyBase<YellowPixelFamilyBase<PixelBase<COMPONENT_STORAGE, CMYKPixelFamily<COMPONENT_STORAGE>,ConstCMYKPixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE> >
{
private:
	typedef CMYKPixelFamilyBase<BlackPixelFamilyBase<CyanPixelFamilyBase<MagentaPixelFamilyBase<YellowPixelFamilyBase<PixelBase<COMPONENT_STORAGE, CMYKPixelFamily<COMPONENT_STORAGE>,ConstCMYKPixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE> > _Super;

public:
	typedef typename _Super::CyanComponentType CyanComponentType;
	typedef typename _Super::MagentaComponentType MagentaComponentType;
	typedef typename _Super::YellowComponentType YellowComponentType;
	
public:
	CMYKPixelFamily() {}
	
public:
	CMYKPixelFamily(const CMYKPixelFamily &rhs) : _Super(rhs) {}
	CMYKPixelFamily(const CyanComponentType &cyan, const MagentaComponentType &magenta, const YellowComponentType &yellow, const YellowComponentType &black) : _Super() { setCMYK(cyan, magenta, yellow, black); }
	CMYKPixelFamily& operator=(const CMYKPixelFamily &rhs) { _Super::_storage = rhs._storage; return *this; }
};


//==============================================================================
// CLASS ConstCMYKAPixelFamily
//==============================================================================
template<typename COMPONENT_STORAGE>
class ConstCMYKAPixelFamily: public ConstAlphaPixelFamilyBase<ConstCyanPixelFamilyBase<ConstMagentaPixelFamilyBase<ConstYellowPixelFamilyBase<ConstPixelBase<COMPONENT_STORAGE, ConstCMYKAPixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE>
{
private:
	typedef ConstAlphaPixelFamilyBase<ConstCyanPixelFamilyBase<ConstMagentaPixelFamilyBase<ConstYellowPixelFamilyBase<ConstPixelBase<COMPONENT_STORAGE, ConstCMYKAPixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE> _Super;

public:
	ConstCMYKAPixelFamily() {}
	
protected:
	ConstCMYKAPixelFamily(const ConstCMYKAPixelFamily &rhs) : _Super(rhs) {}
};

//==============================================================================
// CLASS CMYKAPixelFamily
//==============================================================================
template<typename COMPONENT_STORAGE>
class CMYKAPixelFamily: public AlphaPixelFamilyBase<CyanPixelFamilyBase<MagentaPixelFamilyBase<YellowPixelFamilyBase<PixelBase<COMPONENT_STORAGE, CMYKAPixelFamily<COMPONENT_STORAGE>, ConstCMYKAPixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE>
{
private:
	typedef AlphaPixelFamilyBase<CyanPixelFamilyBase<MagentaPixelFamilyBase<YellowPixelFamilyBase<PixelBase<COMPONENT_STORAGE, CMYKAPixelFamily<COMPONENT_STORAGE>, ConstCMYKAPixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE>, COMPONENT_STORAGE> _Super;

protected:
	typedef typename _Super::_Manip _Manip;

public:
	typedef typename _Super::CyanComponentType CyanComponentType;
	typedef typename _Super::MagentaComponentType MagentaComponentType;
	typedef typename _Super::YellowComponentType YellowComponentType;
	typedef typename _Super::AlphaComponentType AlphaComponentType;

public:
	CMYKAPixelFamily() {}
	
public:
	CMYKAPixelFamily(const CMYKAPixelFamily &rhs) : _Super(rhs) {}
	CMYKAPixelFamily(const CyanComponentType &cyan, const MagentaComponentType &magenta, const YellowComponentType &yellow, const AlphaComponentType &alpha) : _Super() { setCMYKA(cyan, magenta, yellow, alpha); }

	void setCMYKA(const CyanComponentType &r, const MagentaComponentType &g, const YellowComponentType &b, const AlphaComponentType &a) { _Manip::setCMYKA(_Super::_storage, r, g, b, a); }

public:
	template<typename PIXELSRC>
	void convert(const PIXELSRC &fromPixel)
	{
		_Super::convert(fromPixel);
	}
};


template<typename STORAGE, int INDEX>
class ConstBlackPixelBitBase
{
public:
	typedef typename STORAGE::ComponentModel ComponentModel;
	typedef typename STORAGE::ColorSpace ColorSpace;
	typedef STORAGE PacketStorageType;
	typedef STORAGE BlackStorageType;
	
	typename BlackStorageType::ComponentType black() const { return _storage.template value<INDEX>(); }

protected:
	PacketStorageType _storage;
};

template<typename STORAGE, int INDEX>
class ConstBlackPixelBit: public ConstBlackPixelBitBase<STORAGE, INDEX>
{};


template<typename STORAGE, int INDEX, typename DERIVED>
class BlackPixelBitBase: public ConstBlackPixelBitBase<STORAGE, INDEX>
{
private:
	typedef ConstBlackPixelBitBase<STORAGE, INDEX> _Super;
	
public:
	typedef typename _Super::BlackStorageType BlackStorageType;
	
	void setBlack(typename BlackStorageType::ComponentType value) { _Super::_storage.template setValue<INDEX>(value); }

	template<typename PIXELTYPE>
	void convert(const PIXELTYPE &rhs)
	{
		setBlack(PixelConvertExtractBlack<PIXELTYPE, DERIVED>::eval(rhs));
	}
};


template<typename STORAGE, int INDEX>
class BlackPixelBit: public BlackPixelBitBase<STORAGE, INDEX, BlackPixelBit<STORAGE, INDEX> >
{
};



template<typename PARENT, int NBBIT=PARENT::PacketStorageType::NBBIT>
class ConstBlackPixelBitPacketFamilyBaseNbBit;

template<typename PARENT>
class ConstBlackPixelBitPacketFamilyBaseNbBit<PARENT, 1>: public PARENT
{
private:
	typedef PARENT _Super;
	
public:
	typedef typename _Super::PacketStorageType BlackStorageType;

public:
	enum { PIXEL_PER_PACKET = BlackStorageType::BITPACKET_PER_PACKET };

	typedef ConstBlackPixelBit<BlackStorageType, 0> ConstBlackPixelBit0;
	typedef ConstBlackPixelBit<BlackStorageType, 1> ConstBlackPixelBit1;
	typedef ConstBlackPixelBit<BlackStorageType, 2> ConstBlackPixelBit2;
	typedef ConstBlackPixelBit<BlackStorageType, 3> ConstBlackPixelBit3;
	typedef ConstBlackPixelBit<BlackStorageType, 4> ConstBlackPixelBit4;
	typedef ConstBlackPixelBit<BlackStorageType, 5> ConstBlackPixelBit5;
	typedef ConstBlackPixelBit<BlackStorageType, 6> ConstBlackPixelBit6;
	typedef ConstBlackPixelBit<BlackStorageType, 7> ConstBlackPixelBit7;
	typedef ConstBlackPixelBit<BlackStorageType, 8> ConstBlackPixelBit8;
	
	
	const ConstBlackPixelBit0& pixel0() const { return *(const ConstBlackPixelBit0*)this; }
	const ConstBlackPixelBit1& pixel1() const { return *(const ConstBlackPixelBit1*)this; }
	const ConstBlackPixelBit2& pixel2() const { return *(const ConstBlackPixelBit2*)this; }
	const ConstBlackPixelBit3& pixel3() const { return *(const ConstBlackPixelBit3*)this; }
	const ConstBlackPixelBit4& pixel4() const { return *(const ConstBlackPixelBit4*)this; }
	const ConstBlackPixelBit5& pixel5() const { return *(const ConstBlackPixelBit5*)this; }
	const ConstBlackPixelBit6& pixel6() const { return *(const ConstBlackPixelBit6*)this; }
	const ConstBlackPixelBit7& pixel7() const { return *(const ConstBlackPixelBit7*)this; }
};

template<typename PARENT>
class ConstBlackPixelBitPacketFamilyBaseNbBit<PARENT, 4>: public PARENT
{
private:
	typedef PARENT _Super;
	
public:
	typedef typename _Super::PacketStorageType BlackStorageType;

public:
	enum { PIXEL_PER_PACKET = BlackStorageType::BITPACKET_PER_PACKET };

	typedef ConstBlackPixelBit<BlackStorageType, 0> ConstBlackPixelBit0;
	typedef ConstBlackPixelBit<BlackStorageType, 1> ConstBlackPixelBit1;

	const ConstBlackPixelBit0& pixel0() const { return *(const ConstBlackPixelBit0*)this; }
	const ConstBlackPixelBit1& pixel1() const { return *(const ConstBlackPixelBit1*)this; }
};




template<typename PARENT>
class ConstBlackPixelBitPacketFamilyBase: public ConstBlackPixelBitPacketFamilyBaseNbBit<PARENT>
{
private:
	typedef PARENT _Super;
	
public:
	typedef typename _Super::PacketStorageType BlackStorageType;
};


template<typename COMPONENT_STORAGE>
class ConstBlackPixelBitPacketFamily: public ConstBlackPixelBitPacketFamilyBase<ConstPixelBase<COMPONENT_STORAGE, ConstBlackPixelBitPacketFamily<COMPONENT_STORAGE> > >
{
private:
	typedef ConstBlackPixelBitPacketFamilyBase<ConstPixelBase<COMPONENT_STORAGE, ConstBlackPixelBitPacketFamily<COMPONENT_STORAGE> > > _Super;
	
public:
	typedef typename _Super::BlackStorageType BlackStorageType;

};


template<typename PARENT, int NBBIT=PARENT::PacketStorageType::NBBIT>
class BlackPixelBitPacketFamilyBaseNbBit;

template<typename PARENT>
class BlackPixelBitPacketFamilyBaseNbBit<PARENT, 1>: public PARENT
{
private:
	typedef PARENT _Super;
	
public:
	typedef typename _Super::PacketStorageType BlackStorageType;

public:
	template<typename PIXELTYPE0, typename PIXELTYPE1, typename PIXELTYPE2, typename PIXELTYPE3, typename PIXELTYPE4, typename PIXELTYPE5, typename PIXELTYPE6, typename PIXELTYPE7>
	void convert(const PIXELTYPE0 &p0, const PIXELTYPE1 &p1, const PIXELTYPE2 &p2, const PIXELTYPE3 &p3, const PIXELTYPE4 &p4, const PIXELTYPE5 &p5, const PIXELTYPE6 &p6, const PIXELTYPE7 &p7)
	{
		pixel0().convert(p0);
		pixel1().convert(p1);
		pixel2().convert(p2);
		pixel3().convert(p3);
		pixel4().convert(p4);
		pixel5().convert(p5);
		pixel6().convert(p6);
		pixel7().convert(p7);
	}

	enum { PIXEL_PER_PACKET = BlackStorageType::BITPACKET_PER_PACKET };

	typedef BlackPixelBit<BlackStorageType, 0> BlackPixelBit0;
	typedef BlackPixelBit<BlackStorageType, 1> BlackPixelBit1;
	typedef BlackPixelBit<BlackStorageType, 2> BlackPixelBit2;
	typedef BlackPixelBit<BlackStorageType, 3> BlackPixelBit3;
	typedef BlackPixelBit<BlackStorageType, 4> BlackPixelBit4;
	typedef BlackPixelBit<BlackStorageType, 5> BlackPixelBit5;
	typedef BlackPixelBit<BlackStorageType, 6> BlackPixelBit6;
	typedef BlackPixelBit<BlackStorageType, 7> BlackPixelBit7;
	typedef BlackPixelBit<BlackStorageType, 8> BlackPixelBit8;
	
	
	using _Super::pixel0;
	using _Super::pixel1;
	using _Super::pixel2;
	using _Super::pixel3;
	using _Super::pixel4;
	using _Super::pixel5;
	using _Super::pixel6;
	using _Super::pixel7;

	BlackPixelBit0& pixel0() const { return *(BlackPixelBit0*)this; }
	BlackPixelBit1& pixel1() const { return *(BlackPixelBit1*)this; }
	BlackPixelBit2& pixel2() const { return *(BlackPixelBit2*)this; }
	BlackPixelBit3& pixel3() const { return *(BlackPixelBit3*)this; }
	BlackPixelBit4& pixel4() const { return *(BlackPixelBit4*)this; }
	BlackPixelBit5& pixel5() const { return *(BlackPixelBit5*)this; }
	BlackPixelBit6& pixel6() const { return *(BlackPixelBit6*)this; }
	BlackPixelBit7& pixel7() const { return *(BlackPixelBit7*)this; }
};

template<typename PARENT>
class BlackPixelBitPacketFamilyBaseNbBit<PARENT, 4>: public PARENT
{
private:
	typedef PARENT _Super;
	
public:
	typedef typename _Super::PacketStorageType BlackStorageType;

public:
	template<typename PIXELTYPE0, typename PIXELTYPE1>
	void convert(const PIXELTYPE0 &p0, const PIXELTYPE1 &p1)
	{
		pixel0().convert(p0);
		pixel1().convert(p1);
	}

	template<typename PACKETTYPE>
	void convert(const PACKETTYPE &packet)
	{
		pixel0().convert(packet.pixel0());
		pixel1().convert(packet.pixel1());
	}

	enum { PIXEL_PER_PACKET = BlackStorageType::BITPACKET_PER_PACKET };

	typedef BlackPixelBit<BlackStorageType, 0> BlackPixelBit0;
	typedef BlackPixelBit<BlackStorageType, 1> BlackPixelBit1;
	
	using _Super::pixel0;
	using _Super::pixel1;

	BlackPixelBit0& pixel0() const { return *(BlackPixelBit0*)this; }
	BlackPixelBit1& pixel1() const { return *(BlackPixelBit1*)this; }
};


template<typename PARENT>
class BlackPixelBitPacketFamilyBase: public BlackPixelBitPacketFamilyBaseNbBit<ConstBlackPixelBitPacketFamilyBase<PARENT> >
{
private:
	typedef BlackPixelBitPacketFamilyBaseNbBit<ConstBlackPixelBitPacketFamilyBase<PARENT> > _Super;
};


template<typename COMPONENT_STORAGE>
class BlackPixelBitPacketFamily: public BlackPixelBitPacketFamilyBase<PixelBase<COMPONENT_STORAGE, BlackPixelBitPacketFamily<COMPONENT_STORAGE>, ConstBlackPixelBitPacketFamily<COMPONENT_STORAGE> > >
{
private:
	typedef BlackPixelBitPacketFamilyBase<PixelBase<COMPONENT_STORAGE, BlackPixelBitPacketFamily<COMPONENT_STORAGE>, ConstBlackPixelBitPacketFamily<COMPONENT_STORAGE> > > _Super;
	
public:
	typedef typename _Super::BlackStorageType BlackStorageType;
};


#endif // __ITL_CMYKPIXELDEFINITION_H__
