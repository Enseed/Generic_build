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
#ifndef __ITL_PIXMAP_H__
#define __ITL_PIXMAP_H__

//==============================================================================
// FILE PixMap.h
//==============================================================================
//
// USAGE:
//     // Allocate a packed RGB24 PixMap with width 720 and height 486:
//     PixMap<RGB24Pixel> pm1(720, 486);
//
//     // Allocate a planar RGB24 PixMap with width 720 and height 486:
//     PixMap<RGB24PlanarPixel> pm2(720, 486);
//
//     // Take a reference on which you can iterate and do some actual work:
//     pm2.forEach(ColorInBlue); // call ColorInBlue(RGB24PlanarPixel&) for each pixel
//
//------------------------------------------------------------------------------

//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================
#include "PixelIterator.h"
#include "PixRowRef.h"
#include "PixRowIterator.h"
#include "PixMapOrigin.h"
#include "PixPlane.h"
#include "PixMapSurface.h"
#include "PixMap.declare.h"
#include "PixMapRef.declare.h"
#include "../PixelConvert/PixelConverter.h"
#include "PixMapResolution.h"
#include "PixMapRef.h"
#include "PixMapManip.h"

//==============================================================================
// NAMESPACE ITL
//==============================================================================
namespace ITL {

//==============================================================================
// CLASS PixMapBase
// Used for members specific to the number of planes
//==============================================================================
template<typename DERIVED, typename PIXELPACKET, int PLANECOUNT=PIXELPACKET::PLANE_COUNT>
class PixMapBase;

//------------------------------------------------------------------------------
//
template<typename DERIVED, typename PIXELPACKET>
struct PixMapBase<DERIVED, PIXELPACKET, 1>
{
	typename PIXELPACKET::Plane0Storage::ComponentType* baseAddr()
	{	return static_cast<DERIVED*>(this)->begin()->baseAddr();	}

	const typename PIXELPACKET::Plane0Storage::ComponentType* baseAddr() const
	{	return static_cast<const DERIVED*>(this)->begin()->baseAddr();	}

	int rowBytes() const
	{	return static_cast<const DERIVED*>(this)->begin()->rowBytes();	}
};

//------------------------------------------------------------------------------
//
template<typename DERIVED, typename PIXELPACKET>
struct PixMapBase<DERIVED, PIXELPACKET, 2>
{
	typename PIXELPACKET::Plane0Storage::ComponentType* baseAddr0()
	{	return static_cast<DERIVED*>(this)->begin()->baseAddr0();	}

	const typename PIXELPACKET::Plane0Storage::ComponentType* baseAddr0() const
	{	return static_cast<const DERIVED*>(this)->begin()->baseAddr0();	}

	typename PIXELPACKET::Plane1Storage::ComponentType* baseAddr1()
	{	return static_cast<DERIVED*>(this)->begin()->baseAddr1();	}

	const typename PIXELPACKET::Plane1Storage::ComponentType* baseAddr1() const
	{	return static_cast<const DERIVED*>(this)->begin()->baseAddr1();	}

	int rowBytes0() const
	{	return static_cast<const DERIVED*>(this)->begin()->rowBytes0();	}

	int rowBytes1() const
	{	return static_cast<const DERIVED*>(this)->begin()->rowBytes1();	}
};

//------------------------------------------------------------------------------
//
template<typename DERIVED, typename PIXELPACKET>
struct PixMapBase<DERIVED, PIXELPACKET, 3>: public PixMapBase<DERIVED, PIXELPACKET, 2>
{
	typename PIXELPACKET::Plane2Storage::ComponentType* baseAddr2()
	{	return static_cast<DERIVED*>(this)->begin()->baseAddr2();	}

	const typename PIXELPACKET::Plane2Storage::ComponentType* baseAddr2() const
	{	return static_cast<const DERIVED*>(this)->begin()->baseAddr2();	}

	int rowBytes2() const
	{	return static_cast<const DERIVED*>(this)->begin()->rowBytes2();	}
};

//------------------------------------------------------------------------------
//
template<typename DERIVED, typename PIXELPACKET>
struct PixMapBase<DERIVED, PIXELPACKET, 4>: public PixMapBase<DERIVED, PIXELPACKET, 3>
{
	typename PIXELPACKET::Plane3Storage::ComponentType* baseAddr3()
	{	return static_cast<DERIVED*>(this)->begin()->baseAddr3();	}

	const typename PIXELPACKET::Plane3Storage::ComponentType* baseAddr3() const
	{	return static_cast<const DERIVED*>(this)->begin()->baseAddr3();	}

	int rowBytes3() const
	{	return static_cast<const DERIVED*>(this)->begin()->rowBytes3();	}
};

//------------------------------------------------------------------------------
//
template<typename DERIVED, typename PIXELPACKET>
struct PixMapBase<DERIVED, PIXELPACKET, 5>: public PixMapBase<DERIVED, PIXELPACKET, 4>
{
	typename PIXELPACKET::Plane4Storage::ComponentType* baseAddr4()
	{	return static_cast<DERIVED*>(this)->begin()->baseAddr4();	}

	const typename PIXELPACKET::Plane4Storage::ComponentType* baseAddr4() const
	{	return static_cast<const DERIVED*>(this)->begin()->baseAddr4();	}

	int rowBytes4() const
	{	return static_cast<const DERIVED*>(this)->begin()->rowBytes4();	}
};

//==============================================================================
// CLASS PixMap
//==============================================================================
template<typename PIXELPACKET, typename ORIGIN>
class PixMap: public PixMapBase<PixMap<PIXELPACKET, ORIGIN>,  PIXELPACKET>
{
public:
	typedef class Resolution Resolution;
	typedef class PixRowRef<const PIXELPACKET> ConstPixRowRef;
	typedef class PixRowRef<PIXELPACKET> PixRowRef;

	typedef typename PixMapOrigin<PIXELPACKET, ORIGIN>::RowIterator RowIterator;
	typedef typename PixMapOrigin<PIXELPACKET, ORIGIN>::ConstRowIterator ConstRowIterator;

	typedef typename PixMapOrigin<PIXELPACKET, ORIGIN>::ReverseRowIterator ReverseRowIterator;
	typedef typename PixMapOrigin<PIXELPACKET, ORIGIN>::ConstReverseRowIterator ConstReverseRowIterator;

	typedef typename PixMapOrigin<PIXELPACKET, ORIGIN>::TopToBottomIterator TopToBottomIterator;
	typedef typename PixMapOrigin<PIXELPACKET, ORIGIN>::ConstTopToBottomIterator ConstTopToBottomIterator;

	typedef typename PixMapOrigin<PIXELPACKET, ORIGIN>::BottomToTopIterator BottomToTopIterator;
	typedef typename PixMapOrigin<PIXELPACKET, ORIGIN>::ConstBottomToTopIterator ConstBottomToTopIterator;

	class PixMapRef
	{
	public:
		template<class, class> friend class PixMapRef;

		PixMapRef()
		:
			_firstRow(),
			_height(),
			_dpi()
		{}

		template<class RHS_PIXELPACKET>
		PixMapRef(const typename PixMap<RHS_PIXELPACKET, ORIGIN>::PixMapRef &rhs)
		:
			_firstRow(rhs._firstRow),
			_height(rhs._height),
			_dpi(rhs._dpi)
		{}

		PixMapRef(const PixRowRef &firstRow, int height)
		:
			_firstRow(firstRow),
			_height(height),
			_dpi(Resolution::defaultResolution())
		{}

		PixMapRef(const PixRowRef &firstRow, int height, const Resolution &dpi)
		:
			_height(height),
			_firstRow(firstRow),
			_dpi(dpi)
		{}

	public: // ACCESSORS
		int width() const { return _firstRow.width(); }
		int height() const { return _height; }
		int planes() const { return _firstRow.planes(); }
		float pixelRatio() const { return _dpi.x / _dpi.y; }
		const Resolution& resolution() const { return _dpi; }
		void setResolution(const Resolution &res) { _dpi = res; }

	public: // ITERATORS
		RowIterator begin() { return RowIterator(_firstRow); }
		ConstRowIterator begin() const { return ConstRowIterator(_firstRow); }

		RowIterator end() { return begin() + height(); }
		ConstRowIterator end() const { return begin() + height(); }

		ReverseRowIterator rbegin() { return rend() - height(); }
		ConstReverseRowIterator rbegin() const { rend() - height(); }

		ReverseRowIterator rend() { return ReverseRowIterator(_firstRow); }
		ConstReverseRowIterator rend() const { return ReverseRowIterator(_firstRow); }

		TopToBottomIterator beginFromTop() { return PixMapOrigin<PIXELPACKET, ORIGIN>::beginFromTop(_firstRow, _height); }
		ConstTopToBottomIterator beginFromTop() const 
		{ 
			PixMapOrigin<PIXELPACKET, ORIGIN>::TopToBottomIterator iter = PixMapOrigin<PIXELPACKET, ORIGIN>::beginFromTop(_firstRow, _height);
			PixMapOrigin<PIXELPACKET, ORIGIN>::ConstTopToBottomIterator iter2 = iter;
			return iter2;
		}

		TopToBottomIterator endFromTop() { return PixMapOrigin<PIXELPACKET, ORIGIN>::endFromTop(_firstRow, _height); }
		ConstTopToBottomIterator endFromTop() const { return PixMapOrigin<PIXELPACKET, ORIGIN>::endFromTop(_firstRow, _height); }

		BottomToTopIterator beginFromBottom() { return PixMapOrigin<PIXELPACKET, ORIGIN>::beginFromBottom(_firstRow, _height); }
		ConstBottomToTopIterator beginFromBottom() const { return PixMapOrigin<PIXELPACKET, ORIGIN>::beginFromBottom(_firstRow, _height); }

		BottomToTopIterator endFromBottom() { return PixMapOrigin<PIXELPACKET, ORIGIN>::endFromBottom(_firstRow, _height); }
		ConstBottomToTopIterator endFromBottom() const { return PixMapOrigin<PIXELPACKET, ORIGIN>::endFromBottom(_firstRow, _height); }

	public: // RANDOM ACCESS
		PixRowRef operator[](int y) { return *(begin() + y); }
		ConstPixRowRef operator[](int y) const { return *(begin() + y); }

	protected:
		template<typename FUNCT>
		class ForEachPixelInRowFunctor
		{
		public:
			ForEachPixelInRowFunctor(const FUNCT &funct) : _funct(funct) {}
			void operator()(PixRowRef &row) const
			{
				row.forEachPixel(_funct);
			}

		private:
			const FUNCT &_funct;
		};

		template<typename FUNCT>
		class ForEachPacketInRowFunctor
		{
		public:
			ForEachPacketInRowFunctor(const FUNCT &funct) : _funct(funct) {}
			void operator()(PixRowRef &row) const
			{
				row.forEachPacket(_funct);
			}

		private:
			const FUNCT &_funct;
		};

	public:
		template<typename FUNCT>
		void forEachPacket(const FUNCT &funct)
		{
			forEachRow(ForEachPacketInRowFunctor<FUNCT>(funct));
		}

		template<typename FUNCT>
		void forEachPixel(const FUNCT &funct)
		{
			forEachRow(ForEachPixelInRowFunctor<FUNCT>(funct));
		}

		template<typename FUNCT>
		void forEachRow(const FUNCT &funct)
		{
			for (RowIterator iter = begin(); iter != end(); ++iter)
				funct(*iter);
		}

	private:
		int _height;
		PixRowRef _firstRow;
		Resolution _dpi;
	};


public:
	typedef ORIGIN OriginType;
	typedef PIXELPACKET PixelType;
	typedef typename PixMap<const PIXELPACKET, ORIGIN>::PixMapRef ConstPixMapRef;

public:
	PixMap(int width, int height)
	:
		_surface(new PixMapSurface<PIXELPACKET>(width, height)),
		_pixMapRef(_surface->firstRow(), _surface->height(), Resolution::defaultResolution())
	{}

	PixMap(int width, int height, const Resolution &resolution)
	:
		_surface(new PixMapSurface<PIXELPACKET>(width, height)),
		_pixMapRef(_surface->firstRow(), _surface->height(), resolution)
	{}

	PixMap(int width, int height, const PixMapRowByteDescription<PIXELPACKET> &rowByteDescription)
	:
		_surface(new PixMapSurface<PIXELPACKET>(width, height, rowByteDescription)),
		_pixMapRef(_surface->firstRow(), _surface->height(), Resolution::defaultResolution())
	{}

	PixMap(int width, int height, int rowBytes, const Resolution &resolution)
	:
		_surface(new PixMapSurface<PIXELPACKET>(width, height)),
		_pixMapRef(_surface->firstRow(), _surface->height(), resolution)
	{}

	PixMap(const PixMapRef &pixMapRef)
	:
		_surface(NULL),
		_pixMapRef(pixMapRef)
	{}
	
	~PixMap()
	{
		delete _surface;
	}
	
	int width() const { return _pixMapRef.width(); }
	int height() const { return _pixMapRef.height(); }
	int planes() const { return _pixMapRef.planes(); }

	float pixelRatio() const { return _pixMapRef.pixelRatio(); }
	const Resolution& resolution() const { return _pixMapRef.resolution(); }
	void setResolution(const Resolution &res) { _pixMapRef.setResolution(res); }
	
	void resize(int width, int height)
	{
		_surface->resize(width, height);
		_pixMapRef = PixMapRef(_surface->firstRow(), _surface->height(), _pixMapRef.resolution());
	}

	void resize(int width, int height, int rowBytes)
	{
		_surface->resize(width, height, rowBytes);
		_pixMapRef = PixMapRef(_surface->firstRow(), _surface->height(), _pixMapRef.resolution());
	}

	PixMap<PIXELPACKET, ORIGIN>* duplicate() const
	{	return ConstPixMapRef(this).duplicate(); }

	template<class RHS_PIXELPACKET>
	PixMap<RHS_PIXELPACKET, ORIGIN>* convert() const
	{
		return convert<RHS_PIXELPACKET, ORIGIN>();
	}

	template<class RHS_PIXELPACKET, class RHS_ORIGIN>
	PixMap<RHS_PIXELPACKET, RHS_ORIGIN>* convert() const
	{
		PixMap<RHS_PIXELPACKET, RHS_ORIGIN> *dup = new PixMap<RHS_PIXELPACKET, RHS_ORIGIN>(width(), height(), resolution());
		PixMapManip::convert(*this, dup);
		return dup;
	}

	template<typename FUNCT>
	void forEachPacket(const FUNCT &funct)
	{
		_pixMapRef.forEachPacket(funct);
	}

	template<typename FUNCT>
	void forEachPixel(const FUNCT &funct)
	{
		_pixMapRef.forEachPixel(funct);
	}

	template<typename FUNCT>
	void forEachRow(const FUNCT &funct)
	{
		_pixMapRef.forEachRow(funct);
	}
	
	PixRowRef operator[](int y) { return _pixMapRef[y]; }
	ConstPixRowRef operator[](int y) const { return _pixMapRef[y]; }

	RowIterator begin() { return _pixMapRef.begin(); }
	ConstRowIterator begin() const { return _pixMapRef.begin(); }

	RowIterator end() { return _pixMapRef.end(); }
	ConstRowIterator end() const { return _pixMapRef.end(); }

	ReverseRowIterator rbegin() { return _pixMapRef.rbegin(); }
	ConstReverseRowIterator rbegin() const { _pixMapRef.rbegin(); }

	ReverseRowIterator rend() { return _pixMapRef.rend(); }
	ConstReverseRowIterator rend() const { return _pixMapRef.rend(); }

	TopToBottomIterator beginFromTop() { return _pixMapRef.beginFromTop(); }
	ConstTopToBottomIterator beginFromTop() const { return _pixMapRef.beginFromTop(); }

	TopToBottomIterator endFromTop() { return _pixMapRef.endFromTop(); }
	ConstTopToBottomIterator endFromTop() const { return _pixMapRef.endFromTop(); }

	BottomToTopIterator beginFromBottom() { return _pixMapRef.beginFromBottom(); }
	ConstBottomToTopIterator beginFromBottom() const { return _pixMapRef.beginFromBottom(); }

	BottomToTopIterator endFromBottom() { return _pixMapRef.endFromBottom(); }
	ConstBottomToTopIterator endFromBottom() const { return _pixMapRef.endFromBottom(); }

public:
	const PixMapSurface<PIXELPACKET>& surface() const { return *_surface; }
	PixMapSurface<PIXELPACKET>& surface() { return *_surface; }

private: // for now...
	PixMap(const PixMap &rhs);
	PixMap& operator=(const PixMap &rhs);

private:
	PixMapSurface<PIXELPACKET> *_surface;
	PixMapRef _pixMapRef;
};




}

#endif // __ITL_PIXMAP_H__
