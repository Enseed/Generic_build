/*******************************************************************************
 Copyright 2007 Enseed inc.
 
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
#ifndef __GENERIC_IMAGE_PIXEL_DECLARE__
#define __GENERIC_IMAGE_PIXEL_DECLARE__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================

namespace seed {

//==============================================================================
//	FORWARD DECLARATIONS
//==============================================================================
template<class T> class ConstARGBPixel;
template<class T> class ARGBPixel;

template<class T> class ConstRGBAPixel;
template<class T> class RGBAPixel;

template<class T> class ConstRGBPixel;
template<class T> class RGBPixel;

template<class T> class ConstBGRPixel;
template<class T> class BGRPixel;

template<class T> class ConstBGRAPixel;
template<class T> class BGRAPixel;

template<class T> class ConstABGRPixel;
template<class T> class ABGRPixel;

template<class T> class ConstLPixel;
template<class T> class LPixel;

template<class T> class ConstLAPixel;
template<class T> class LAPixel;

template<class T> class ConstYCbCrPixel;
template<class T> class YCbCrPixel;

}

#endif // __GENERIC_IMAGE_PIXEL_DECLARE__
