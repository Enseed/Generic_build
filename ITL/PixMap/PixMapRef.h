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
#ifndef __ITL_PIXMAPREF_H__
#define __ITL_PIXMAPREF_H__

//==============================================================================
// CLASS PixMapRef
//==============================================================================
// A PixMapRef is a reference to a PixMap storage.  This is the most important
// class in this library (along with the various pixel types).
// 
// A PixMapRef can be iterated (begin(), end()) or randomly accessed ([y][x])
// NOTE: There is no direct access to the base address of the data from the
// PixMapRef because the implementation supports N-planar representations.
//
// If you have a single plane PixMapRef, you may access the base address of the
// data using 
//		PixMapRef<RGB24Pixel> ref
//		RGB24Pixel* baseAddr = &ref[0][0];
//
// But remember that this will fail for multi-planar pixels. Instead, you would
// use:
//
//		PixMapRef<RGB24PlanarPixel> ref
//		unsigned char* baseAddr = ref[0][0].plane0Ptr();
//
//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================
#include "PixelIterator.h"
#include "PixMapResolution.h"
#include "PixRowRef.h"
#include "PixRowIterator.h"
#include "PixMapOrigin.h"
#include "PixPlane.h"
#include "PixMapSurface.h"
#include "PixMap.declare.h"
#include "PixMap.h"
#include "PixMapManip.h"
#include "../PixelConvert/PixelConverter.h"

//==============================================================================
// ITL NAMESPACE
//==============================================================================
namespace ITL {


}

#endif // __ITL_PIXMAPREF_H__
