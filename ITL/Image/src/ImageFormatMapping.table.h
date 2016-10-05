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

#define ITL_DECLARE_RGB
#define ITL_DECLARE_RGBA
#define ITL_DECLARE_LUM
//#define ITL_DECLARE_BLACK
#define ITL_DECLARE_YCBCR
#define ITL_DECLARE_YCBCRA
#define ITL_DECLARE_CMYK
#define ITL_DECLARE_YCBCR422

#ifdef ITL_DECLARE_RGB
ITL_FORMAT_DECLARE(FORMAT_BGR8_UD,	BGR24Pixel,		PixMapDrawsFromBottom	)
ITL_FORMAT_DECLARE(FORMAT_BGR8,		BGR24Pixel,		PixMapDrawsFromTop	)
ITL_FORMAT_DECLARE(FORMAT_RGB8,		RGB24Pixel,		PixMapDrawsFromTop	)
ITL_FORMAT_DECLARE(FORMAT_RGB8_UD,	RGB24Pixel,		PixMapDrawsFromBottom	)
ITL_FORMAT_DECLARE(FORMAT_RGB16,	RGB48Pixel,		PixMapDrawsFromTop	)
ITL_FORMAT_DECLARE(FORMAT_RGB64fPLANAR,	RGB64fPlanarPixel,	PixMapDrawsFromTop	)
ITL_FORMAT_DECLARE(FORMAT_RGB8PLANAR,	RGB24PlanarPixel,	PixMapDrawsFromTop	)
ITL_FORMAT_DECLARE(FORMAT_RGB64f,	RGB64fPixel,	PixMapDrawsFromTop	)
#endif

#ifdef ITL_DECLARE_RGBA
ITL_FORMAT_DECLARE(FORMAT_RGBA8,	RGBA32Pixel,	PixMapDrawsFromTop	)
ITL_FORMAT_DECLARE(FORMAT_RGBA8_UD,	RGBA32Pixel,	PixMapDrawsFromBottom	)
//ITL_FORMAT_DECLARE(FORMAT_RGBAPLANAR8,	RGBA32PlanarPixel,	PixMapDrawsFromTop	)
ITL_FORMAT_DECLARE(FORMAT_ARGB8,	ARGB32Pixel,	PixMapDrawsFromTop	)
ITL_FORMAT_DECLARE(FORMAT_ARGB8_UD,	ARGB32Pixel,	PixMapDrawsFromBottom	)
ITL_FORMAT_DECLARE(FORMAT_BGRA8,	BGRA32Pixel,	PixMapDrawsFromTop	)
ITL_FORMAT_DECLARE(FORMAT_BGRA8_UD,	BGRA32Pixel,	PixMapDrawsFromBottom	)
ITL_FORMAT_DECLARE(FORMAT_BGRX8_UD,	BGRX32Pixel,	PixMapDrawsFromBottom	)
ITL_FORMAT_DECLARE(FORMAT_ABGR8,	ABGR32Pixel,	PixMapDrawsFromTop	)
ITL_FORMAT_DECLARE(FORMAT_ABGR8_UD,	ABGR32Pixel,	PixMapDrawsFromBottom	)
ITL_FORMAT_DECLARE(FORMAT_ARGB16,	ARGB64Pixel,	PixMapDrawsFromTop	)
ITL_FORMAT_DECLARE(FORMAT_RGBA16,	RGBA64Pixel,	PixMapDrawsFromTop	)
#endif

#ifdef ITL_DECLARE_LUM
ITL_FORMAT_DECLARE(FORMAT_L8,		Lum8Pixel,		PixMapDrawsFromTop	)
ITL_FORMAT_DECLARE(FORMAT_L16,		Lum16Pixel,		PixMapDrawsFromTop	)
ITL_FORMAT_DECLARE(FORMAT_L64f,		Lum64fPixel,	PixMapDrawsFromTop	)

ITL_FORMAT_DECLARE(FORMAT_LA8,		LA8Pixel,		PixMapDrawsFromTop	)
ITL_FORMAT_DECLARE(FORMAT_LA16,		LA16Pixel,		PixMapDrawsFromTop	)
ITL_FORMAT_DECLARE(FORMAT_LA64f,	LA64fPixel,		PixMapDrawsFromTop	)
#endif

#ifdef ITL_DECLARE_BLACK
ITL_FORMAT_DECLARE(FORMAT_K8,		Black8Pixel,		PixMapDrawsFromTop	)
ITL_FORMAT_DECLARE(FORMAT_K4,		Black4Pixel,		PixMapDrawsFromTop	)
ITL_FORMAT_DECLARE(FORMAT_K1,		Black1Pixel,		PixMapDrawsFromTop	)
ITL_FORMAT_DECLARE(FORMAT_K16,		Black16Pixel,		PixMapDrawsFromTop	)
ITL_FORMAT_DECLARE(FORMAT_K64f,		Black64fPixel,	PixMapDrawsFromTop	)
#endif

#ifdef ITL_DECLARE_YCBCR
ITL_FORMAT_DECLARE(FORMAT_YCBCR8,	YCbCr24Pixel,	PixMapDrawsFromTop	)
ITL_FORMAT_DECLARE(FORMAT_YCBCR64f,	YCbCr64fPixel,	PixMapDrawsFromTop	)
ITL_FORMAT_DECLARE(FORMAT_YCBCR64fPLANAR,	YCbCr64fPlanarPixel,	PixMapDrawsFromTop	)
ITL_FORMAT_DECLARE(FORMAT_YCBCR8PLANAR,	YCbCr24PlanarPixel,	PixMapDrawsFromTop	)
#endif

#ifdef ITL_DECLARE_YCBCRA
ITL_FORMAT_DECLARE(FORMAT_CBYCRA8,	CbYCrA32Pixel,	PixMapDrawsFromTop	)
ITL_FORMAT_DECLARE(FORMAT_AYCBCR8,	AYCbCr32Pixel,	PixMapDrawsFromTop	)
#endif

#ifdef ITL_DECLARE_CMYK
ITL_FORMAT_DECLARE(FORMAT_CMYK8,	CMYK32Pixel,	PixMapDrawsFromTop	)
#endif

#ifdef ITL_DECLARE_YCBCR422
ITL_FORMAT_DECLARE(FORMAT_YYCBCR8,	YYCbCr32Pixel,	PixMapDrawsFromTop	)
ITL_FORMAT_DECLARE(FORMAT_YCBYCR8,	YCbYCr32Pixel,	PixMapDrawsFromTop	)
ITL_FORMAT_DECLARE(FORMAT_CBYCRY8,	CbYCrY32Pixel,	PixMapDrawsFromTop	)
//ITL_FORMAT_DECLARE(FORMAT_CBYCRYHD8,CbYCrYHD32Pixel,	PixMapDrawsFromTop	)
ITL_FORMAT_DECLARE(FORMAT_CRYCBY8,	YCbYCrRev32Pixel,	PixMapDrawsFromTop	)
ITL_FORMAT_DECLARE(FORMAT_YYCBCR64f,	YYCbCr64fPixel,	PixMapDrawsFromTop	)
#endif

//ITL_FORMAT_DECLARE(FORMAT_YCBYCR64fPLANAR,	YCbYCr64fPlanarPixel,	PixMapDrawsFromTop	)
//ITL_FORMAT_DECLARE(FORMAT_YCBYCR8PLANAR,	YCbYCr32PlanarPixel,	PixMapDrawsFromTop	)
