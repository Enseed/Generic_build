#if 0
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
#ifndef __ITL_PIXELADAPTOR_H__
#define __ITL_PIXELADAPTOR_H__

//==============================================================================
//	FILE PixelAdaptor.h
//==============================================================================
// Allow the use of a pixel type as though it was another pixel type.
// This can be useful when an algorithm expects a certain type of pixel
// and that is now what you have.
//------------------------------------------------------------------------------

//==============================================================================
//	CLASS PixelAdator
//==============================================================================
template<typename ADAPTED_TYPE, typename ACTUAL_TYPE, typename ADAPTED_COLORSPACE=typename ADAPTED_TYPE::ColorSpace, typename ACTUAL_COLORSPACE=typename ACTUAL_TYPE::ColorSpace, int PLANECOUNT=ACTUAL_TYPE::PLANE_COUNT>
class PixelAdaptor;


#include "PixelAdaptor_RGB.h"

#endif // __ITL_PIXELADAPTOR_H__


#endif // 0
