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
#ifndef __ITL_IMAGE_INLINE_H__
#define __ITL_IMAGE_INLINE_H__

#include "../Image.h"
#include "ImageProxy.h"

#include <Generic/Devel/Debug.h>
#include "../../PixMap/PixRowRef.h"
#include "ImageFormatSwitch.h"
namespace ITL {


//==============================================================================
// CLASS Image
//==============================================================================
template<int FORMAT>
typename ImageTypeToPixMapTypeMapping<FORMAT>::PixMapType* ImageRef::pixMap()
{
	// Make sure you request the correct pixmap format
	if (FORMAT != _image->format())
	{
		FIXME("something's wrong...");
//		throw std::exception();
	}

	return static_cast<typename ImageTypeToPixMapTypeMapping<FORMAT>::PixMapType*>(_image->pixMap());
}

template<int FORMAT>
typename ImageTypeToPixMapTypeMapping<FORMAT>::ConstPixMapType* ImageRef::pixMap() const
{
	// Make sure you request the correct pixmap format
	if (FORMAT != _image->format())
	{
		FIXME("something's wrong...");
//		throw std::exception();
	}

	return static_cast<typename ImageTypeToPixMapTypeMapping<FORMAT>::ConstPixMapType*>(_image->pixMap());
}



template<class DST_PIXELTYPE, typename FUNCTOR>
class ImageForEachPixelConvert
{
public:
	ImageForEachPixelConvert(const FUNCTOR &func) : _func(func) {}

public:
	template<typename SRC_PIXELTYPE>
	void operator()(const SRC_PIXELTYPE &pixel) const
	{
		DST_PIXELTYPE dstPixel;
		dstPixel.convert(pixel);
		_func(dstPixel);
	}

private:
	FUNCTOR _func;
};

template<typename DST_PIXELTYPE, typename FUNCTOR>
class ImageForEachPixel
{
public:
	ImageForEachPixel(const FUNCTOR &func) : _func(func) {}

	template<typename SRC_PIXELPACKET>
	void operator()(PixMap<SRC_PIXELPACKET> *pm) const
	{
		ImageForEachPixelConvert<DST_PIXELTYPE, FUNCTOR> convFunc(_func);
		pm->forEachPixel(convFunc);
	}
private:
	const FUNCTOR &_func;
};




template<typename PIXELTYPE, typename FUNCTOR>
inline void ImageRef::forEachPixel(const FUNCTOR &func)
{
	ImageForEachPixel<PIXELTYPE, FUNCTOR> callObject(func);
	TCallWithFormat(format(), this, callObject);
}



} // namespace ITL
#endif // __ITL_IMAGE_INLINE_H__
