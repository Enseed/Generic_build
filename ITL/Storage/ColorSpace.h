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
#ifndef __ITL_COLORSPACE_H__
#define __ITL_COLORSPACE_H__

//==============================================================================
//	FILE ColorSpace.h
//==============================================================================
// Defines the valid color space tags.  These are used to specialize the pixel
// types.  Pixels from the same colorspace are expected to have the same
// kinds of components. For example, pixels from the sRGB color space will have
// the .red(), .green() and .blue() getter and setters, while pixels from the
// YCbCr color space will have the luminance(), chromaBlue() and chromaRed()
// getters and setters.
//
// These tags are required to define a pixel type and are used by the
// PixelConverter to convert from one color space to another.
//------------------------------------------------------------------------------

class ColorSpace_XYZ;			// not implemented
class ColorSpace_LUV;			// not implemented
class ColorSpace_UVW;			// not implemented
class ColorSpace_LAB;			// not implemented
class ColorSpace_sRGB;			// fully implemented
class ColorSpace_AdobeRGB;		// not implemented
class ColorSpace_AdobeWideRGB;	// not implemented
class ColorSpace_CMY;			// not implemented
class ColorSpace_CMYK;			// not implemented
class ColorSpace_xvYCC;			// not implemented
class ColorSpace_HSV;			// not implemented
class ColorSpace_HSL;			// not implemented
class ColorSpace_YCbCr_ITU601;	// partially implemented
class ColorSpace_YCbCr_ITU709;	// not implemented
class ColorSpace_None;

#endif // __ITL_COLORPROFILE_H__
