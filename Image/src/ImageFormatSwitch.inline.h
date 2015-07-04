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
#ifndef __ITL_IMAGE_IMAGEFORMATSWITCH_INLINE_H__
#define __ITL_IMAGE_IMAGEFORMATSWITCH_INLINE_H__

#include "../ImageFormat.h"
#include "../Image.h"
#include "ImageFormatMapping.h"

namespace ITL {

//------------------------------------------------------------------------------
// Use the ImageFormatMapping.table.h to generate a switch case function that
// will call a template functor instantiated with the actual format.
// For instance, calling 
//
//		TCallWithFormat(format, x)
//
// will call
//
// 		x.call<format>()
//
// This is the actual glue between the virtual and the template layers.
//------------------------------------------------------------------------------
template<typename FUNCTOR>
void TCallWithFormat(ImageFormat::Format format, FUNCTOR &functor)
{
	switch(format)
	{
#define ITL_FORMAT_DECLARE(FORMAT, TYPE, DIRECTION) case(ImageFormat::FORMAT): functor. template call<ImageFormat::FORMAT>(); break;
#include "ImageFormatMapping.table.h"
#undef ITL_FORMAT_DECLARE
	}
}

#undef ITL_FORMAT_DECLARE

//------------------------------------------------------------------------------
// Same as above, except we call the operator() with the actual pixmap from
// the ImageRef.  For instance, calling:
//
//		TCallWithPixMap(image, x)
//
// will result in a call to 
//
//		x(image->pixMap<image->format()>())
//------------------------------------------------------------------------------
template<typename FUNCTOR>
class TCallWithPixMap
{
public:
	TCallWithPixMap(ImageRef *image, FUNCTOR &functor) : _image(image), _functor(functor) {}
	template<int FORMAT>
	void call() 
	{ 
		typename ImageTypeToPixMapTypeMapping<FORMAT>::PixMapType *pixMap = _image->pixMap<FORMAT>();
		_functor(pixMap); 
	}

private:
	ImageRef *_image;
	FUNCTOR &_functor;
};

//------------------------------------------------------------------------------
//
template<typename FUNCTOR>
void TCallWithFormat(ImageFormat::Format format, ImageRef *image, FUNCTOR &functor)
{
	TCallWithPixMap<FUNCTOR> pixmapFunctor(image, functor);
	TCallWithFormat(format, pixmapFunctor);
}


//------------------------------------------------------------------------------
// Const version of the above (when ImageRef is const)
//------------------------------------------------------------------------------
template<typename FUNCTOR>
class TCallWithConstPixMap
{
public:
	TCallWithConstPixMap(const ImageRef *image, FUNCTOR &functor) : _image(image), _functor(functor) {}
	template<int FORMAT>
	void call() { _functor(_image->pixMap<FORMAT>()); }

private:
	const ImageRef *_image;
	FUNCTOR &_functor;
};

//------------------------------------------------------------------------------
//
template<typename FUNCTOR>
void TCallWithFormat(ImageFormat::Format format, const ImageRef *image, FUNCTOR &functor)
{
	TCallWithConstPixMap<FUNCTOR> pixmapFunctor(image, functor);
	TCallWithFormat(format, pixmapFunctor);
}

} // namespace ITL

#endif // __ITL_IMAGE_IMAGEFORMATSWITCH_INLINE_H__
