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
#ifndef __ITL_IMAGE_H__
#define __ITL_IMAGE_H__

#include "../PixMap/PixMap.h"
#include "../RGB/RGBPixel.h"
#include "../CMY/CMYKPixel.h"
#include "../YCbCr/YCbCrPixel.h"
#include "../YCbCr/YCbCr422Pixel.h"
#include "ImageFormat.h"
#include "src/ImageFormatMapping.h"

//==============================================================================
// CLASS Image
//==============================================================================

#ifdef WIN32
#ifdef ITL_EXPORTS
#define ITL_DLL_EXPORT __declspec(dllexport)
#else
#define ITL_DLL_EXPORT __declspec(dllimport)
#endif
#endif



namespace ITL {

// FORWARD
class Image;
class ImageProxy;

class ImageRef: public ImageFormat
{
public:
	typedef ImageFormat::Format Format;
	
	template<int FORMAT>
	typename ImageTypeToPixMapTypeMapping<FORMAT>::PixMapType* pixMap();

	template<int FORMAT>
	typename ImageTypeToPixMapTypeMapping<FORMAT>::ConstPixMapType* pixMap() const;

	// for convenience and auto complete...
#ifdef ITL_DECLARE_RGBA
	PixMap<ARGB32Pixel>* argb32PixMap() { return pixMap<FORMAT_ARGB8>(); }
	PixMap<ARGB64Pixel>* argb64PixMap() { return pixMap<FORMAT_ARGB16>(); }
	PixMap<RGBA32Pixel>* rgba32PixMap() { return pixMap<FORMAT_RGBA8>(); }
	PixMap<RGBA64Pixel>* rgba64PixMap() { return pixMap<FORMAT_RGBA16>(); }
	PixMap<ABGR32Pixel>* abgr32PixMap() { return pixMap<FORMAT_ABGR8>(); }
	PixMap<BGRA32Pixel>* bgra32PixMap() { return pixMap<FORMAT_BGRA8>(); }
#endif

#ifdef ITL_DECLARE_RGB
	PixMap<BGR24Pixel>* bgr24PixMap() { return pixMap<FORMAT_BGR8>(); }
	PixMap<RGB24Pixel>* rgb24PixMap() { return pixMap<FORMAT_RGB8>(); }
	PixMap<RGB48Pixel>* rgb48PixMap() { return pixMap<FORMAT_RGB16>(); }
#endif

#ifdef ITL_DECLARE_LUM
	PixMap<Lum8Pixel>* lum8PixMap() { return pixMap<FORMAT_L8>(); }
	PixMap<Lum16Pixel>* lum16PixMap() { return pixMap<FORMAT_L16>(); }

	PixMap<LA8Pixel>* la8PixMap() { return pixMap<FORMAT_LA8>(); }
	PixMap<LA16Pixel>* la16PixMap() { return pixMap<FORMAT_LA16>(); }
#endif

#ifdef ITL_DECLARE_YCBCR
	PixMap<YCbCr24Pixel>* yCbCr24PixMap() { return pixMap<FORMAT_YCBCR8>(); }
	PixMap<CbYCrY32Pixel>* cbYCrY32PixMap() { return pixMap<FORMAT_CBYCRY8>(); }
#endif
	
	template<typename PIXELTYPE, typename FUNCTOR>
	inline void forEachPixel(const FUNCTOR &op);

public:
	ITL_DLL_EXPORT int width() const;
	ITL_DLL_EXPORT int height() const;
	ITL_DLL_EXPORT int planes() const;
	ITL_DLL_EXPORT Format format() const;

	ITL_DLL_EXPORT int rowBytes(int planeIndex) const;
	ITL_DLL_EXPORT void* baseAddr(int planeIndex) const;
	
	ITL_DLL_EXPORT int horizontalSampling(int planeIndex) const;
	ITL_DLL_EXPORT int verticalSampling(int planeIndex) const;
	ITL_DLL_EXPORT Direction direction() const;
	
	ITL_DLL_EXPORT Image* convert(Format format) const;
	ITL_DLL_EXPORT Image* resample(int width, int height) const;

	ITL_DLL_EXPORT ImageRef();
	ITL_DLL_EXPORT ImageRef(Format format, int width, int height, float pixelRatio, int expectedNbPlanes, void **baseAddrForEachPlane, int *rowBytesForEachPlane);
	ITL_DLL_EXPORT ~ImageRef();

	ITL_DLL_EXPORT float horizontalResolution() const;
	ITL_DLL_EXPORT float verticalResolution() const;

	ITL_DLL_EXPORT void setHorizontalResolution(float hRes);
	ITL_DLL_EXPORT void setVerticalResolution(float vRes);

	ITL_DLL_EXPORT void setPixelRatio(float ratio) { setHorizontalResolution(verticalResolution()*ratio); }
	ITL_DLL_EXPORT float pixelRatio() const { return horizontalResolution() / verticalResolution(); }

	ITL_DLL_EXPORT void copy(const ImageRef &rhs);
	ITL_DLL_EXPORT void resample(const ImageRef &rhs);

protected:
	ImageRef(ImageProxy *proxy);
	ImageProxy *_image;

private:
	ImageRef(const ImageRef&);
	ImageRef& operator=(const ImageRef&);
};

class Image: public ImageRef
{
public:
	ITL_DLL_EXPORT Image(Format format, int width, int height);
	ITL_DLL_EXPORT Image(Format format, int width, int height, float pixelRatio);
	ITL_DLL_EXPORT Image(Format format, int width, int height, float pixelRatio, int expectedNbPlanes, int *rowBytesForEachPlanes);
	ITL_DLL_EXPORT Image(Format format, int width, int height, int expectedNbPlanes, int *rowBytesForEachPlanes);

private:
	Image(const Image&);
	Image& operator=(const Image&);
};

} // namespace ITL

#include "src/Image.inline.h"


#endif // __ITL_IMAGE_H__
