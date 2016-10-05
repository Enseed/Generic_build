/*******************************************************************************
 Copyright 2008 Enseed inc.
 
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

 Author: Gaspard Petit
*******************************************************************************/
#ifndef __GENERIC_IMAGING_IMAGE__
#define __GENERIC_IMAGING_IMAGE__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "PixMap.declare.h"
#include "Pixel.declare.h"
#include "../Base/Types.h"

#ifdef GENERIC_NAMESPACE
namespace GENERIC_NAMESPACE {
#endif
//==============================================================================
//	CLASS Image
//==============================================================================
class Image
{
public:
	typedef enum
	{
		FORMAT_ARGB8 ,
		FORMAT_RGBA8 ,
		FORMAT_RGB8  ,
		FORMAT_L8    ,
		FORMAT_ARGB16,
		FORMAT_RGBA16,
		FORMAT_RGB16 ,
		FORMAT_L16   ,
		FORMAT_YCbCr8,
		FORMAT_BGRA8 ,
		FORMAT_BGR8  ,
		FORMAT_ABGR8 
	} Format;
	
public:
	inline PixMap<ARGBPixel<uint8> >*	argb8PixMap();
	inline PixMap<RGBAPixel<uint8> >*	rgba8PixMap();
	inline PixMap<RGBPixel<uint8> >*	rgb8PixMap();
	inline PixMap<LPixel<uint8> >*		l8PixMap();
	inline PixMap<ARGBPixel<uint16> >*	argb16PixMap();
	inline PixMap<RGBAPixel<uint16> >*	rgba16PixMap();
	inline PixMap<RGBPixel<uint16> >*	rgb16PixMap();
	inline PixMap<LPixel<uint16> >*	l16PixMap();
	inline PixMap<YCbCrPixel<uint8> >*	yCbCr8PixMap();
	inline PixMap<BGRAPixel<uint8> >*	bgra8PixMap();
	inline PixMap<BGRPixel<uint8> >*	bgr8PixMap();
	inline PixMap<ABGRPixel<uint8> >*	abgr8PixMap();

	inline int width();
	inline int height();
	inline int rowLength();
	inline void* baseAddr();

	inline Format format();
	
	inline Image* convert(Format format);

	inline ~Image();

	inline Image(Format format, int width, int height);
	inline Image(Format format, int width, int height, int rowLength);


	inline Image* duplicate() const;

private:
	Image(const Image&);
	Image& operator=(const Image&);

private:
	class ImageImp;
	ImageImp* mImp;
};

#ifdef GENERIC_NAMESPACE
}
#endif

#include "src/Image.inline.h"


#endif // __MK_IMAGE_PUBLICIMAGE__
