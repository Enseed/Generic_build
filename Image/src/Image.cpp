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
#include "../Image.h"
#include "ImageProxy.h"

#include "../../../Generic/Devel/Debug.h"
#include "../../RGB/RGBPixel.h"
#include "../../YCbCr/YCbCrPixel.h"
#include "../../PixMap/PixMap.h"
#include "../../PixMap/PixRowRef.h"
#include "ImageFormatMapping.h"
#include "ImageFormatSwitch.h"

namespace ITL {

ImageRef::~ImageRef()
{
	delete _image;
	_image = NULL;
}

Image::Image(Format format, int w, int h)
:
	ImageRef(ImageProxy::create(format, w, h))
{
	printf("created an image with width: %d height: %d, baseAddr0: %p\n", width(), height(), baseAddr(0));
}


Image::Image(Format format, int width, int height, float pixelRatio)
:
	ImageRef(ImageProxy::create(format, width, height, pixelRatio))
{}

ImageRef::ImageRef()
:
	_image(NULL)
{}

ImageRef::ImageRef(ImageProxy *proxy)
:
	_image(proxy)
{}

ImageRef::ImageRef(Format format, int width, int height, float pixelRatio, int expectedNbPlanes, void **baseAddrForEachPlane, int *rowBytesForEachPlane)
:
	_image(ImageProxy::createReference(format, width, height, pixelRatio, expectedNbPlanes, baseAddrForEachPlane, rowBytesForEachPlane))
{}

Image::Image(Format format, int width, int height, float pixelRatio, int expectedNbPlanes, int *rowBytesForEachPlanes)
:
	ImageRef(ImageProxy::create(format, width, height, pixelRatio, expectedNbPlanes, rowBytesForEachPlanes))
{}

Image::Image(Format format, int width, int height, int expectedNbPlanes, int *rowBytesForEachPlanes)
:
	ImageRef(ImageProxy::create(format, width, height, expectedNbPlanes, rowBytesForEachPlanes))
{}

ImageRef::Direction ImageRef::direction() const
{
	return _image->direction();
}

int ImageRef::planes() const
{
	return ImageFormat::planes(format());
}

float ImageRef::horizontalResolution() const
{
	return _image->horizontalResolution();
}

float ImageRef::verticalResolution() const
{
	return _image->verticalResolution();
}

void ImageRef::setHorizontalResolution(float hRes)
{
	return _image->setHorizontalResolution(hRes);
}

void ImageRef::setVerticalResolution(float vRes)
{
	return _image->setVerticalResolution(vRes);
}

int ImageRef::width() const { return _image->width(); }
int ImageRef::height() const { return _image->height(); }
ImageRef::Format ImageRef::format() const { return _image->format(); }
int ImageRef::rowBytes(int planeIndex) const { return _image->rowBytes(planeIndex); }
void* ImageRef::baseAddr(int planeIndex) const { return _image->baseAddr(planeIndex); }

int ImageRef::horizontalSampling(int planeIndex) const { return _image->horizontalSampling(planeIndex); }
int ImageRef::verticalSampling(int planeIndex) const { return _image->verticalSampling(planeIndex); }


template<typename DST_PIXMAP>
class PixMapConvert2
{
public:
	PixMapConvert2(DST_PIXMAP *dst) : _dst(dst) {}
	
	template<typename SRC_PIXMAP>
	void operator()(const SRC_PIXMAP *src)
	{
		PixMapManip::convert(*src, _dst);
	}

private:
	DST_PIXMAP *_dst;
};

template<typename DST_PIXMAP>
class PixMapResample2
{
public:
	PixMapResample2(DST_PIXMAP *dst) : _dst(dst) {}

	template<typename SRC_PIXMAP>
	void operator()(const SRC_PIXMAP *src)
	{
		PixMapManip::resample(*src, _dst);
	}
private:
	DST_PIXMAP *_dst;
};


class PixMapConvert
{
public:
	PixMapConvert(const ImageRef *src) : _src(src) {}
	
	template<typename DST_PIXMAP>
	void operator()(DST_PIXMAP *dst)
	{
		PixMapConvert2<DST_PIXMAP> functor(dst);
		TCallWithFormat(_src->format(), _src, functor);
	}

private:
	const ImageRef *_src;
};

class PixMapResample
{
public:
	 PixMapResample(const ImageRef *src) : _src(src) {}

	template<typename DST_PIXMAP>
	void operator()(DST_PIXMAP *dst)
	{
		PixMapResample2<DST_PIXMAP> functor(dst);
		TCallWithFormat(_src->format(), _src, functor);
	}

private:
	const ImageRef *_src;
};

Image* ImageRef::convert(Format toFormat) const
{
	Image *conv = new Image(toFormat, width(), height());
	PixMapConvert functor(this);
	TCallWithFormat(toFormat, conv, functor);
	return conv;
}

void ImageRef::copy(const ImageRef &rhs)
{
	resample(rhs);
}

void ImageRef::resample(const ImageRef &rhs)
{
	PixMapResample functor(&rhs);
	TCallWithFormat(format(), this, functor);
}

Image* ImageRef::resample(int width, int height) const
{
	Image *conv = new Image(format(), width, height);
	conv->resample(*this);
	return conv;
}

} // namespace ITL
