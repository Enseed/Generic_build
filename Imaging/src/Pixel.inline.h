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
#ifndef __GENERIC_IMAGE_PIXEL_INLINE__
#define __GENERIC_IMAGE_PIXEL_INLINE__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "../Pixel.deprecated.h"
#include "../../Base/Types.h"

namespace seed {

/*template <>
inline const uint8 ConstARGBPixel<uint8>::alpha(const uint8* pixel)
{	return *(uint32*)pixel >> MK_32BIT_BYTE0_OFFSET;	}

template <>
inline const uint8 ConstARGBPixel<uint8>::red(const uint8* pixel)
{	return *(uint32*)pixel >> MK_32BIT_BYTE1_OFFSET;	}

template <>
inline const uint8 ConstARGBPixel<uint8>::green(const uint8* pixel)
{	return *(uint32*)pixel >> MK_32BIT_BYTE2_OFFSET;	}

template <>
inline const uint8 ConstARGBPixel<uint8>::blue(const uint8* pixel)
{	return *(uint32*)pixel >> MK_32BIT_BYTE3_OFFSET;	}

template <>
inline void ARGBPixel<uint8>::setRGBA(uint8* pixel, uint8 r, uint8 g, uint8 b, uint8 a)
{
  *(uint32*)pixel =	a << MK_32BIT_BYTE0_OFFSET |
					r << MK_32BIT_BYTE1_OFFSET |
					g << MK_32BIT_BYTE2_OFFSET |
					b << MK_32BIT_BYTE3_OFFSET;
 
}

template <>
inline const uint8 ConstRGBAPixel<uint8>::red(const uint8* pixel)
{	return *(uint32*)pixel >> MK_32BIT_BYTE0_OFFSET;	}

template <>
inline const uint8 ConstRGBAPixel<uint8>::green(const uint8* pixel)
{	return *(uint32*)pixel >> MK_32BIT_BYTE1_OFFSET;	}

template <>
inline const uint8 ConstRGBAPixel<uint8>::blue(const uint8* pixel)
{	return *(uint32*)pixel >> MK_32BIT_BYTE2_OFFSET;	}

template <>
inline const uint8 ConstRGBAPixel<uint8>::alpha(const uint8* pixel)
{	return *(uint32*)pixel >> MK_32BIT_BYTE3_OFFSET;	}

template <>
inline void RGBAPixel<uint8>::setRGBA(uint8* pixel, uint8 r, uint8 g, uint8 b, uint8 a)
{
	*(uint32*)pixel = r << MK_32BIT_BYTE0_OFFSET |
					  g << MK_32BIT_BYTE1_OFFSET |
					  b << MK_32BIT_BYTE2_OFFSET |
					  a << MK_32BIT_BYTE3_OFFSET;
}
*/

} // namespace seed

#endif // __GENERIC_IMAGE_PIXEL_INLINE__
