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
#include "ImageProxy.h"

#include "../Image.h" // FIXME

#include <Enseed/Generic/Devel/Debug.h>
#include "ImageFormatMapping.h"
#include "ImageFormatSwitch.h"


namespace ITL {

template<class PIXMAP, typename PIXELPACKET=typename PIXMAP::PixelType, typename ORIGIN=typename PIXMAP::OriginType>
class ImagePixMapInspector;

template<class PIXMAP, typename PIXELPACKET>
struct ImagePixMapInspector<PIXMAP, PIXELPACKET, PixMapDrawsFromBottom>
{
	static ImageRef::Direction direction() { return ImageRef::DIRECTION_FROM_BOTTOM; }
};

template<class PIXMAP, typename PIXELPACKET>
struct ImagePixMapInspector<PIXMAP, PIXELPACKET, PixMapDrawsFromTop>
{
	static ImageRef::Direction direction() { return ImageRef::DIRECTION_FROM_TOP; }
};



template<class PIXELPACKET, class ORIENTATION, int PLANECOUNT=PIXELPACKET::PLANE_COUNT>
class ImagePlaneInspector;

template<class PIXELPACKET, class ORIENTATION>
class ImagePlaneInspector<PIXELPACKET, ORIENTATION, 1>
{
public:
	static const void* baseAddr(const PixMap<PIXELPACKET, ORIENTATION> *pm, int index)
	{
		switch(index)
		{
		case(0): return pm->baseAddr();
		}

		return NULL;
	}

	static void* baseAddr(PixMap<PIXELPACKET, ORIENTATION> *pm, int index)
	{
		switch(index)
		{
		case(0): return pm->baseAddr();
		}
		
		return NULL;
	}
	
	static int rowBytes(const PixMap<PIXELPACKET, ORIENTATION> *pm, int index)
	{
		switch(index)
		{
		case(0): return pm->rowBytes();
		}
		
		return 0;
	}
	
	static int verticalSampling(int index)
	{
		switch(index)
		{
		case(0): return 1; // FIXME
		}

		return 0;
	}

	static int horizontalSampling(int index)
	{
		switch(index)
		{
		case(0): return PIXELPACKET::PIXEL_PER_PACKET;
		}

		return 0;
	}
};



template<class PIXELPACKET, class ORIENTATION>
class ImagePlaneInspector<PIXELPACKET, ORIENTATION, 3>
{
public:
	static const void* baseAddr(const PixMap<PIXELPACKET, ORIENTATION> *pm, int index)
	{
		switch(index)
		{
		case(0): return pm->baseAddr0();
		case(1): return pm->baseAddr1();
		case(2): return pm->baseAddr2();
		}
		
		return NULL;
	}

	static void* baseAddr(PixMap<PIXELPACKET, ORIENTATION> *pm, int index)
	{
		switch(index)
		{
		case(0): return pm->baseAddr0();
		case(1): return pm->baseAddr1();
		case(2): return pm->baseAddr2();
		}
		
		return NULL;
	}
	
	static int rowBytes(const PixMap<PIXELPACKET, ORIENTATION> *pm, int index)
	{
		switch(index)
		{
		case(0): return pm->rowBytes0();
		case(1): return pm->rowBytes1();
		case(2): return pm->rowBytes2();
		}
		
		return 0;
	}
	
	static int verticalSampling(int index)
	{
		switch(index)
		{
		case(0): return 1; // FIXME
		case(1): return 1; // FIXME
		case(2): return 1; // FIXME
		}

		return 0;
	}

	static int horizontalSampling(int index)
	{
		switch(index)
		{
		case(0): return PIXELPACKET::PIXEL_PER_PACKET; // FIXME
		case(1): return PIXELPACKET::PIXEL_PER_PACKET; // FIXME
		case(2): return PIXELPACKET::PIXEL_PER_PACKET; // FIXME
		}

		return 0;
	}
};


template<typename PIXMAPTYPE>
class TImageProxyCommon: public ImageProxy
{
public:
	typedef typename PIXMAPTYPE::PixelType PixelType;
	typedef typename PIXMAPTYPE::OriginType OriginType;

	TImageProxyCommon(PIXMAPTYPE *pixMap)
	:
		_pixMap(pixMap)
	{}

	TImageProxyCommon(const PixMap<PixelType, OriginType> *pixMap)
	:
		_pixMap(pixMap)
	{}
	
	virtual ~TImageProxyCommon() { delete _pixMap; }

	virtual int width() const 
	{
		return _pixMap->width();
	}
	virtual int height() const 
	{ 
		return _pixMap->height(); 
	}

	virtual Format format() const { return PixelTypeToImageTypeMapping<PixelType, OriginType>::Format; }

	virtual void* pixMap()
	{
		return _pixMap;
	};
	virtual const void* pixMap() const 
	{
		return _pixMap;
	};

	virtual void* baseAddr(int planeIndex) { return ImagePlaneInspector<PixelType, OriginType>::baseAddr(_pixMap, planeIndex); }
	virtual const void* baseAddr(int planeIndex) const { return ImagePlaneInspector<PixelType, OriginType>::baseAddr(_pixMap, planeIndex); }
	virtual int rowBytes(int planeIndex) { return ImagePlaneInspector<PixelType, OriginType>::rowBytes(_pixMap, planeIndex); }

	virtual int horizontalSampling(int planeIndex) const { return ImagePlaneInspector<PixelType, OriginType>::horizontalSampling(planeIndex); }
	virtual int verticalSampling(int planeIndex) const { return ImagePlaneInspector<PixelType, OriginType>::verticalSampling(planeIndex); }
	virtual ImageFormat::Direction direction() const { return ImagePixMapInspector<PIXMAPTYPE>::direction(); }

	virtual float horizontalResolution() const { return _pixMap->resolution().x; }
	virtual float verticalResolution() const { return _pixMap->resolution().y; }

	virtual void setHorizontalResolution(float hRes) { _pixMap->setResolution(Resolution(hRes, verticalResolution())); }
	virtual void setVerticalResolution(float vRes) { _pixMap->setResolution(Resolution(horizontalResolution(), vRes)); }


protected:
	PIXMAPTYPE *_pixMap;
};

template<typename PIXMAPTYPE, int PLANE_COUNT=PIXMAPTYPE::PixelType::PLANE_COUNT>
class TImageProxyBase;


template<typename PIXMAPTYPE>
class TImageProxyBase<PIXMAPTYPE, 1>: public TImageProxyCommon<PIXMAPTYPE>
{
private:
	typedef TImageProxyCommon<PIXMAPTYPE> _Super;

public:
	typedef typename _Super::PixelType PixelType;
	typedef typename _Super::OriginType OriginType;

public:
	TImageProxyBase(int width, int height)
	:
		_Super(new PIXMAPTYPE(width, height))
	{}

	TImageProxyBase(int width, int height, float pixelRatio)
	:
		_Super(new PIXMAPTYPE(width, height, Resolution(pixelRatio*72, 72)))
	{}

	TImageProxyBase(int width, int height, float pixelRatio, int expectedNbPlanes, int *rowBytesForEachPlanes)
	:
		_Super(new PIXMAPTYPE(width, height, rowBytesForEachPlanes[0], Resolution(pixelRatio*72, 72)))
	{}

	TImageProxyBase(int width, int height, int expectedNbPlanes, int *rowBytesForEachPlanes)
	:
		_Super(new PIXMAPTYPE(width, height, rowBytesForEachPlanes[0]))
	{}

	TImageProxyBase(int width, int height, float pixelRatio, int expectedNbPlanes, void **baseAddrForEachPlane, int *rowBytesForEachPlane)
	:
		_Super(
			new PIXMAPTYPE(typename PixMap<PixelType, OriginType>::PixMapRef(PixRowRef<PixelType>( PixelRef<PixelType>((typename PixelType::ComponentType*)baseAddrForEachPlane[0]), width, rowBytesForEachPlane[0]), height, Resolution(72*pixelRatio, 72)))
		)
	{}
};

template<typename PIXMAPTYPE>
class TImageProxyBase<PIXMAPTYPE, 3>: public TImageProxyCommon<PIXMAPTYPE>
{
private:
	typedef TImageProxyCommon<PIXMAPTYPE> _Super;

public:
	typedef typename _Super::PixelType PixelType;
	typedef typename _Super::OriginType OriginType;

public:
	TImageProxyBase(int width, int height)
	:
		_Super(new PIXMAPTYPE(width, height))
	{}

	TImageProxyBase(int width, int height, float pixelRatio)
	:
		_Super(new PIXMAPTYPE(width, height, Resolution(pixelRatio*72, 72)))
	{}

	TImageProxyBase(int width, int height, float pixelRatio, int expectedNbPlanes, int *rowBytesForEachPlanes)
	:
		_Super(new PIXMAPTYPE(width, height, rowBytesForEachPlanes[0], Resolution(pixelRatio*72, 72)))
	{}

	TImageProxyBase(int width, int height, int expectedNbPlanes, int *rowBytesForEachPlanes)
	:
		_Super(new PIXMAPTYPE(width, height, PixMapRowByteDescription<PixelType>(rowBytesForEachPlanes[0], rowBytesForEachPlanes[1], rowBytesForEachPlanes[2])))
	{}

	TImageProxyBase(int width, int height, float pixelRatio, int expectedNbPlanes, void **baseAddrForEachPlane, int *rowBytesForEachPlane)
	:
		_Super(new PIXMAPTYPE(typename PixMap<PixelType, OriginType>::PixMapRef(PixRowRef<PixelType>( PixelRef<PixelType>((typename PixelType::Plane0Storage::ComponentType*)baseAddrForEachPlane[0], (typename PixelType::Plane1Storage::ComponentType*)baseAddrForEachPlane[1], (typename PixelType::Plane2Storage::ComponentType*)baseAddrForEachPlane[2]), width, rowBytesForEachPlane[0], rowBytesForEachPlane[1], rowBytesForEachPlane[2]), height, Resolution(72*pixelRatio, 72))))
	{}
};


template<typename PIXMAPTYPE>
class TImageProxy: public TImageProxyBase<PIXMAPTYPE>
{
private:
	typedef TImageProxyBase<PIXMAPTYPE> _Super;
public:
	typedef typename PIXMAPTYPE::PixelType PixelType;
	typedef typename PIXMAPTYPE::OriginType OriginType;
	typedef typename _Super::Format Format;
	
public:
	TImageProxy(int w, int h)
	:
		_Super(w, h)
	{}

	TImageProxy(int width, int height, float pixelRatio)
	:
		_Super(width, height, pixelRatio)
	{}

	TImageProxy(int width, int height, float pixelRatio, int expectedNbPlanes, int *rowBytesForEachPlanes)
	:
		_Super(width, height, pixelRatio, expectedNbPlanes, rowBytesForEachPlanes)
	{}

	TImageProxy(int width, int height, int expectedNbPlanes, int *rowBytesForEachPlanes)
	:
		_Super(width, height, expectedNbPlanes, rowBytesForEachPlanes)
	{}

	TImageProxy(int width, int height, float pixelRatio, int expectedNbPlanes, void **baseAddrForEachPlane, int *rowBytesForEachPlane)
	:
		_Super(width, height, pixelRatio, expectedNbPlanes, baseAddrForEachPlane, rowBytesForEachPlane)
	{}
};


class TImageProxyCreateRef
{
public:
	TImageProxyCreateRef(int width, int height, float pixelRatio, int expectedNbPlanes, void **baseAddrForEachPlane, int *rowBytesForEachPlane)
	: 
		_width(width), _height(height), _pixelRatio(pixelRatio), _expectedNbPlanes(expectedNbPlanes), _baseAddrForEachPlane(baseAddrForEachPlane), _rowBytesForEachPlane(rowBytesForEachPlane), _proxy(NULL)
	{}
	
	template<int FORMAT>
	void call()
	{
		typedef typename ImageTypeToPixMapTypeMapping<FORMAT>::PixMapType PIXMAPTYPE;
		_proxy = new TImageProxy<PIXMAPTYPE>(_width, _height, _pixelRatio, _expectedNbPlanes, _baseAddrForEachPlane, _rowBytesForEachPlane);
	}
	
	ImageProxy* proxy() { return _proxy; }

private:
	int _width;
	int _height;
	float _pixelRatio;
	int _expectedNbPlanes;
	void **_baseAddrForEachPlane;
	int *_rowBytesForEachPlane;
	ImageProxy *_proxy;
};

class TImageProxyCreateWithWidthAndHeight
{
public:
	TImageProxyCreateWithWidthAndHeight(int width, int height)
	:
		_width(width),
		_height(height),
		_proxy(NULL)
	{}

	template<int FORMAT>
	void call()
	{
		typedef typename ImageTypeToPixMapTypeMapping<FORMAT>::PixMapType PIXMAPTYPE;
		_proxy = new TImageProxy<PIXMAPTYPE>(_width, _height);
	}

	ImageProxy* proxy() { return _proxy; }
private:
	int _width;
	int _height;
	ImageProxy *_proxy;
};

class TImageProxyCreateWithWidthHeightAndPixelRatio
{
public:
	TImageProxyCreateWithWidthHeightAndPixelRatio(int width, int height, float pixelRatio)
	:
		_width(width), _height(height), _pixelRatio(pixelRatio), _proxy(NULL)
	{}
	
	template<int FORMAT>
	void call()
	{
		typedef typename ImageTypeToPixMapTypeMapping<FORMAT>::PixMapType PIXMAPTYPE;
		_proxy = new TImageProxy<PIXMAPTYPE>(_width, _height, _pixelRatio);
	}
	ImageProxy* proxy() { return _proxy; }

private:
	int _width;
	int _height;
	float _pixelRatio;
	ImageProxy *_proxy;
};

class TImageProxyCreateWidthWidthHeightPixelRatioAndRowBytes
{
public:

	TImageProxyCreateWidthWidthHeightPixelRatioAndRowBytes(int width, int height, float pixelRatio, int expectedNbPlanes, int *rowBytesForEachPlanes)
	:
		_width(width), _height(height), _pixelRatio(pixelRatio), _expectedNbPlanes(expectedNbPlanes), _rowBytesForEachPlanes(rowBytesForEachPlanes), _proxy(NULL)
	{}

	template<int FORMAT>
	void call()
	{
		typedef typename ImageTypeToPixMapTypeMapping<FORMAT>::PixMapType PIXMAPTYPE;
		_proxy = new TImageProxy<PIXMAPTYPE>(_width, _height, _pixelRatio, _expectedNbPlanes, _rowBytesForEachPlanes);
	}
	ImageProxy* proxy() { return _proxy; }

private:
	int _width;
	int _height;
	float _pixelRatio;
	int _expectedNbPlanes;
	int *_rowBytesForEachPlanes;
	ImageProxy *_proxy;
};

class TImageProxyCreateWithWidthHeightAndRowBytes
{
public:
	TImageProxyCreateWithWidthHeightAndRowBytes(int width, int height, int expectedNbPlanes, int *rowBytesForEachPlanes)
	:
		_width(width), _height(height), _expectedNbPlanes(expectedNbPlanes), _rowBytesForEachPlanes(rowBytesForEachPlanes), _proxy(NULL)
	{}
	
	template<int FORMAT>
	void call()
	{
		typedef typename ImageTypeToPixMapTypeMapping<FORMAT>::PixMapType PIXMAPTYPE;
		_proxy = new TImageProxy<PIXMAPTYPE>(_width, _height, _expectedNbPlanes, _rowBytesForEachPlanes);
	}
	ImageProxy* proxy() { return _proxy; }
private:
	int _width;
	int _height;
	int _expectedNbPlanes;
	int *_rowBytesForEachPlanes;
	ImageProxy *_proxy;
};

ImageProxy* ImageProxy::createReference(Format format, int width, int height, float pixelRatio, int expectedNbPlanes, void **baseAddrForEachPlane, int *rowBytesForEachPlane)
{
	if (rowBytesForEachPlane[0] < 0)
		FIXME("Support BGR upside down");

	TImageProxyCreateRef functor(width, height, pixelRatio, expectedNbPlanes, baseAddrForEachPlane, rowBytesForEachPlane);
	TCallWithFormat(format, functor);
	return functor.proxy();
}

ImageProxy* ImageProxy::create(Format format, int width, int height)
{
	TImageProxyCreateWithWidthAndHeight functor(width, height);
	TCallWithFormat(format, functor);
	return functor.proxy();
}

ImageProxy* ImageProxy::create(Format format, int width, int height, float pixelRatio, int expectedNbPlanes, int *rowBytesForEachPlanes)
{
	if (rowBytesForEachPlanes[0] < 0)
		FIXME("Support BGR upside down");

	TImageProxyCreateWidthWidthHeightPixelRatioAndRowBytes functor(width, height, pixelRatio, expectedNbPlanes, rowBytesForEachPlanes);
	TCallWithFormat(format, functor);
	return functor.proxy();
}

ImageProxy* ImageProxy::create(Format format, int width, int height, int expectedNbPlanes, int *rowBytesForEachPlanes)
{
	if (rowBytesForEachPlanes[0] < 0)
		FIXME("Support BGR upside down");

	TImageProxyCreateWithWidthHeightAndRowBytes functor(width, height, expectedNbPlanes, rowBytesForEachPlanes);
	TCallWithFormat(format, functor);
	return functor.proxy();
}

ImageProxy* ImageProxy::create(Format format, int width, int height, float pixelRatio)
{
	TImageProxyCreateWithWidthHeightAndPixelRatio functor(width, height, pixelRatio);
	TCallWithFormat(format, functor);
	return functor.proxy();
}

} // namespace ITL
