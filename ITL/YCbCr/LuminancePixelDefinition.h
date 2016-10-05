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
#ifndef __ITL_LUMINANCEPIXELDEFINITION_H__
#define __ITL_LUMINANCEPIXELDEFINITION_H__

#include "../PixelBase.h"
#include "../PixelConvert/Luminance.declare.h"

//==============================================================================
// FILE LuminancePixelDefinition.h
//==============================================================================
// Various definitions to create Luminance packed pixels (see RGBPixel.h)
//------------------------------------------------------------------------------
ITL_DECLARE_SIMPLE_PIXEL_FAMILY(Luminance, luminance);
ITL_DECLARE_SIMPLE_PIXEL_FAMILY(Luminance0, luminance0);
ITL_DECLARE_SIMPLE_PIXEL_FAMILY(Luminance1, luminance1);

#endif // __ITL_LUMINANCEPIXELDEFINITION_H__
