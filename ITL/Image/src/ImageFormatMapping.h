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
#ifndef __ITL_IMAGE_IMAGEFORMATMAPPING_H__
#define __ITL_IMAGE_IMAGEFORMATMAPPING_H__

//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================
#include "../ImageFormat.h"
#include "../../PixMap/PixMap.declare.h"
#include "../../PixMap/PixMap.h"
#include "../../RGB/RGBPixel.h"
#include "../../YCbCr/YCbCrPixel.h"
#include "../../YCbCr/YCbCr422Pixel.h"

//==============================================================================
// NAMESPACE ITL
//==============================================================================
namespace ITL {

//==============================================================================
// CLASS ImageTypeToPixMapTypeMapping
//==============================================================================
// Obtain the PixMap type associated with the FORMAT enum
template<int FORMAT>
class ImageTypeToPixMapTypeMapping;

//==============================================================================
// CLASS PixelTypeToImageTypeMapping
//==============================================================================
// Obtain the FORMAT enum based on the PixMap type
template<typename PIXELTYPE, typename DIRECTION>
class PixelTypeToImageTypeMapping;

template<typename OriginType>
class OriginTypeToDirectionEnumMapping;

template<> struct OriginTypeToDirectionEnumMapping<PixMapDrawsFromBottom>{ static const ImageFormat::Direction Direction = ImageFormat::DIRECTION_FROM_BOTTOM; };
template<> struct OriginTypeToDirectionEnumMapping<PixMapDrawsFromTop>{ static const ImageFormat::Direction Direction = ImageFormat::DIRECTION_FROM_TOP; };


#define ITL_FORMAT_DECLARE(FORMAT, TYPE, DIRECTION)\
template<> struct ImageTypeToPixMapTypeMapping<ImageFormat::FORMAT> { 	\
	typedef PixMap<TYPE, DIRECTION> PixMapType; 							\
	typedef PixMap<TYPE::ConstType, DIRECTION> ConstPixMapType; 			\
};\
template<> struct PixelTypeToImageTypeMapping<TYPE, DIRECTION> {		\
	static const ImageFormat::Format Format = ImageFormat::FORMAT;		\
};

#include "ImageFormatMapping.table.h"

#undef ITL_FORMAT_DECLARE


} // namespace ITL

#endif // __ITL_IMAGE_IMAGEFORMATMAPPING_H__
