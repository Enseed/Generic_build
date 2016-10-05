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
#ifndef __ITL_XYZPIXEL_H__
#define __ITL_XYZPIXEL_H__

//==============================================================================
// FILE XYZPixel.h
//==============================================================================
// XYZ pixel definitions
//------------------------------------------------------------------------------

//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================
#include "../RGB/RGBPixelDefinition.h"
#include "../Storage/PixelManipulation.h"
#include "ComponentArray.h"
#include "ColorSpace.h"
#include "ComponentRange.h"

//==============================================================================
// PACKED TYPES
//==============================================================================

		// FIXME:
		// For now, I am actually refering to the RGB class just to get things
		// working.

struct ComponentOrderingXYZ { public: enum { RED, GREEN, BLUE, COMPONENT_COUNT }; };

#define DECLARE_XYZ_PIXEL(_type, _ordering, _name)\
typedef RGBPixelFamily<ComponentArray<_type, _ordering, ColorSpace_XYZ, DefaultRange<_type> >, PixelManipulation> _name; \
typedef ConstRGBPixelFamily<ComponentArray<_type, _ordering, ColorSpace_XYZ, DefaultRange<_type> >, PixelManipulation> Const##_name;

DECLARE_XYZ_PIXEL(float, ComponentOrderingXYZ,			XYZf32Pixel);

#undef DECLARE_XYZ_PIXEL


#endif // __ITL_XYZPIXEL_H__


