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
#ifndef __ITL_PIXMAPRESOLUTION_H__
#define __ITL_PIXMAPRESOLUTION_H__

//==============================================================================
// FILE PixMapResolution.h
//==============================================================================
// Defines the resolution field for the pixmap.  
//------------------------------------------------------------------------------

#ifdef ITL_NAMESPACE
namespace ITL_NAMESPACE {
#endif


//==============================================================================
// CLASS Resolution (in DPI)
//==============================================================================
class Resolution
{
public:
	static Resolution defaultResolution() { return Resolution(72, 72); }
	Resolution(float inX, float inY) : x(inX), y(inY) {}
	Resolution() : x(), y() {}

public:
	float x, y;
};


#ifdef ITL_NAMESPACE
}
#endif

#endif // __ITL_PIXMAPRESOLUTION_H__
