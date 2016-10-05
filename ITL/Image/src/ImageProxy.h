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
#ifndef __ITL_IMAGE_IMAGEPROXY_H__
#define __ITL_IMAGE_IMAGEPROXY_H__

#include "../ImageFormat.h"

#ifdef WIN32
#ifdef ITL_EXPORTS
#define ITL_DLL_EXPORT __declspec(dllexport)
#else
#define ITL_DLL_EXPORT __declspec(dllimport)
#endif
#endif
namespace ITL {

class ImageProxy
{
public:
	typedef ImageFormat::Format Format;

public:
	ITL_DLL_EXPORT static ImageProxy* create(Format format, int width, int height);
	ITL_DLL_EXPORT static ImageProxy* create(Format format, int width, int height, float pixelRatio);
	ITL_DLL_EXPORT static ImageProxy* create(Format format, int width, int height, float pixelRatio, int expectedNbPlanes, int *rowBytesForEachPlanes);
	ITL_DLL_EXPORT static ImageProxy* create(Format format, int width, int height, int expectedNbPlanes, int *rowBytesForEachPlanes);
	ITL_DLL_EXPORT static ImageProxy* createReference(Format format, int width, int height, float pixelRatio, int expectedNbPlanes, void **baseAddrForEachPlane, int *rowBytesForEachPlane);

public:
	virtual ~ImageProxy() {}

	ITL_DLL_EXPORT virtual int width() const = 0;
	ITL_DLL_EXPORT virtual int height() const = 0;
	ITL_DLL_EXPORT virtual Format format() const = 0;
	ITL_DLL_EXPORT virtual void* pixMap() = 0;
	ITL_DLL_EXPORT virtual const void* pixMap() const = 0;
	ITL_DLL_EXPORT virtual void* baseAddr(int planeIndex) = 0;
	ITL_DLL_EXPORT virtual const void* baseAddr(int planeIndex) const = 0;
	ITL_DLL_EXPORT virtual int rowBytes(int planeIndex) = 0;
	 
	ITL_DLL_EXPORT virtual int horizontalSampling(int planeIndex) const = 0;
	ITL_DLL_EXPORT virtual int verticalSampling(int planeIndex) const = 0;

	ITL_DLL_EXPORT virtual float horizontalResolution() const = 0;
	ITL_DLL_EXPORT virtual float verticalResolution() const = 0;

	ITL_DLL_EXPORT virtual void setHorizontalResolution(float hRes) = 0;
	ITL_DLL_EXPORT virtual void setVerticalResolution(float vRes) = 0;

	ITL_DLL_EXPORT virtual ImageFormat::Direction direction() const = 0;
};

} // namespace ITL
#endif // __ITL_IMAGE_IMAGEPROXY_H__
