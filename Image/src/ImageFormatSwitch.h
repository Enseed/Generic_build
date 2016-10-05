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
#ifndef __ITL_IMAGE_IMAGEFORMATSWITCH_H__
#define __ITL_IMAGE_IMAGEFORMATSWITCH_H__

//==============================================================================
// FILE: ImageFormatSwitch.h
//==============================================================================
//	These functions are used to switch/case over the various image format
//  enum and perform an action on the typed object
//------------------------------------------------------------------------------

//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================
#include "../ImageFormat.h"

namespace ITL {

//==============================================================================
// FORWARD DECLARATIONS
//==============================================================================
class ImageRef;

//==============================================================================
// Expects functor.call<FORMAT>();
//==============================================================================
template<typename FUNCTOR>
void TCallWithFormat(ImageFormat::Format format, FUNCTOR &functor);

//==============================================================================
// Expects functor( PIXMAPREF &pm );
//==============================================================================
template<typename FUNCTOR>
void TCallWithFormat(ImageFormat::Format format, ImageRef *image, FUNCTOR &functor);

//==============================================================================
// Expects functor( CONSTPIXMAPREF &pm );
//==============================================================================
template<typename FUNCTOR>
void TCallWithFormat(ImageFormat::Format format, const ImageRef *image, FUNCTOR &functor);


} // namespace ITL

#include "ImageFormatSwitch.inline.h"

#endif // __ITL_IMAGE_IMAGEFORMATSWITCH_H__
