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
#ifndef __ITL_YCBCR422PIXELREFDEFINITION_H__
#define __ITL_YCBCR422PIXELREFDEFINITION_H__

//==============================================================================
// CLASS ConstYCbCr422PixelPlanarFamily
//==============================================================================
template<typename Y_STORAGE, typename CB_STORAGE, typename CR_STORAGE, typename PIXEL_MANIPULATOR, typename LUMINANCE_SELECTOR>
class ConstYCbCr422PixelPlanarFamily
{
public:
	typedef Y_STORAGE YStorageType;
	typedef CB_STORAGE CbStorageType;
	typedef CR_STORAGE CrStorageType;

	typedef typename YStorageType::ComponentType YComponentType, Y0ComponentType, Y1ComponentType;
	typedef typename CbStorageType::ComponentType CbComponentType;
	typedef typename CrStorageType::ComponentType CrComponentType;

	typedef PIXEL_MANIPULATOR PixelManipulatorType;

private:
	ConstYCbCr422PixelPlanarFamily();
	ConstYCbCr422PixelPlanarFamily(const ConstYCbCr422PixelPlanarFamily &rhs);
	ConstYCbCr422PixelPlanarFamily& operator=(const ConstYCbCr422PixelPlanarFamily &rhs);

public:
	static YComponentType luminance(const YStorageType &storage)	{ return LUMINANCE_SELECTOR::luminance(storage);   }
	static CbComponentType chromaBlue(const CbStorageType &storage)	{ return PixelManipulatorType::template chromaBlue<CbStorageType>(storage);   }
	static CrComponentType chromaRed(const CrStorageType &storage)	{ return PixelManipulatorType::template chromaRed<CrStorageType>(storage);   }

	YComponentType luminance() const	{ return luminance(_yy);   }
	CbComponentType chromaBlue() const	{ return chromaBlue(_cb); }
	CrComponentType chromaRed()  const	{ return chromaRed(_cr);  }

	YComponentType& yStorage() { return _yy; }
	CbStorageType& cbStorage() { return _cb; }
	CrStorageType& crStorage() { return _cr; }
	
private:
	YStorageType _yy;
	CbStorageType _cb;
	CrStorageType _cr;
};

//==============================================================================
// CLASS ConstYCbCr422PixelPlanarPacket
//==============================================================================
template<typename PIXEL_TYPE0, typename PIXEL_TYPE1>
class ConstYCbCr422PixelPlanarPacket
{
public:
	typedef typename PIXEL_TYPE0::YStorageType YStorageType;
	typedef typename PIXEL_TYPE0::CbStorageType CbStorageType;
	typedef typename PIXEL_TYPE0::CrStorageType CrStorageType;

	typedef PIXEL_TYPE0 PixelType0;
	typedef PIXEL_TYPE1 PixelType1;
	typedef typename PixelType0::Y0ComponentType YComponentType, Y0ComponentType;
	typedef typename PixelType0::CbComponentType CbComponentType;
	typedef typename PixelType0::Y1ComponentType Y1ComponentType;
	typedef typename PixelType1::CrComponentType CrComponentType;
	typedef typename PixelType0::PixelManipulatorType PixelManipulatorType;
	enum { PIXEL_PER_PACKET = 2 };

	typedef YStorageType Plane0Storage;
	typedef CbStorageType Plane1Storage;
	typedef CrStorageType Plane2Storage;
	enum { PLANE_COUNT = 3 };

	typedef typename Plane0Storage::ColorSpace ColorSpace;

public:
	ConstYCbCr422PixelPlanarPacket() : _yy(), _cb(), _cr() {}
	ConstYCbCr422PixelPlanarPacket(const ConstYCbCr422PixelPlanarPacket &rhs) : _yy(rhs._yy), _cb(rhs._cb), _cr(rhs._cr) {}
	ConstYCbCr422PixelPlanarPacket(const YStorageType &yy, const CbStorageType &cb, const CrStorageType &cr) : _yy(yy), _cb(cb), _cr(cr) {}
	ConstYCbCr422PixelPlanarPacket& operator=(const ConstYCbCr422PixelPlanarPacket &rhs) { _yy = rhs.yy, _cb = rhs._cb; _cr = rhs._cr; return *this; }
public:
	Y0ComponentType luminance0() const	{ return _yy.luminance0(); }
	CbComponentType chromaBlue() const	{ return _cb.chromaBlue(); }
	Y1ComponentType luminance1() const	{ return _yy.luminance1(); }
	CrComponentType chromaRed() const	{ return _cr.chromaRed(); }

	const PixelType0& pixel0() const 	{ return reinterpret_cast<const PixelType0&>(*this); }
	PixelType0& pixel0() { return reinterpret_cast<PixelType0&>(*this); }

	const PixelType1& pixel1() const 	{ return reinterpret_cast<const PixelType1&>(*this); }
	PixelType1& pixel1() { return reinterpret_cast<PixelType1&>(*this); }

	typename Plane0Storage::ComponentType* plane0Ptr() { return _yy.ptr(); }
	const typename Plane0Storage::ComponentType* plane0Ptr() const { return _yy.ptr(); }

	typename Plane1Storage::ComponentType* plane1Ptr() { return _cb.ptr(); }
	const typename Plane1Storage::ComponentType* plane1Ptr() const { return _cb.ptr(); }

	typename Plane2Storage::ComponentType* plane2Ptr() { return _cr.ptr(); }
	const typename Plane2Storage::ComponentType* plane2Ptr() const { return _cr.ptr(); }

protected:
	YStorageType _yy;
	CbStorageType _cb;
	CrStorageType _cr;
};

//==============================================================================
// CLASS YCbCr422PixelPlanarPacket
//==============================================================================
template<typename PIXEL_TYPE0, typename PIXEL_TYPE1>
class YCbCr422PixelPlanarPacket: public ConstYCbCr422PixelPlanarPacket<PIXEL_TYPE0, PIXEL_TYPE1>
{
private:
	typedef ConstYCbCr422PixelPlanarPacket<PIXEL_TYPE0, PIXEL_TYPE1> _Super;

public:
	typedef typename PIXEL_TYPE0::YStorageType YStorageType;
	typedef typename PIXEL_TYPE0::CbStorageType CbStorageType;
	typedef typename PIXEL_TYPE0::CrStorageType CrStorageType;

	typedef PIXEL_TYPE0 PixelType0;
	typedef PIXEL_TYPE1 PixelType1;
	typedef typename PixelType0::Y0ComponentType YComponentType, Y0ComponentType;
	typedef typename PixelType0::CbComponentType CbComponentType;
	typedef typename PixelType0::Y1ComponentType Y1ComponentType;
	typedef typename PixelType1::CrComponentType CrComponentType;
	typedef typename PixelType0::PixelManipulatorType PixelManipulatorType;
	enum { NB_PIXEL = 2 };

public:
	YCbCr422PixelPlanarPacket(YComponentType *yy, CbComponentType *cb, CrComponentType *cr) : _Super(yy, cb, cr) {}
	YCbCr422PixelPlanarPacket& operator=(const YCbCr422PixelPlanarPacket &rhs)
	{
		setYCbYCr(rhs.luminance0(), rhs.chromaBlue(), rhs.luminance1(), rhs.chromaRed());
		return *this;
	}

public:
	void setYCbYCr(const Y0ComponentType &y0, const CbComponentType &cb, const Y1ComponentType &y1, const CrComponentType &cr)
	{
		PixelManipulatorType::setLuminance0(_Super::_yy, y0);
		PixelManipulatorType::setChromaBlue(_Super::_cb, cb);
		PixelManipulatorType::setLuminance1(_Super::_yy, y1);
		PixelManipulatorType::setChromaRed (_Super::_cr, cr);
	}
};


#endif // __ITL_YCBCR422PIXELREFDEFINITION_H__


