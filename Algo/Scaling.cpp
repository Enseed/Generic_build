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

#include "Scaling.h"

namespace ITL {

	
template<class PIXELTYPE>
class AccumPixelType;

template<> struct AccumPixelType<RGB24Pixel> { typedef RGB96Pixel Type; };
template<> struct AccumPixelType<ConstRGB24Pixel> { typedef RGB96Pixel Type; };
template<> struct AccumPixelType<BGR24Pixel> { typedef BGR96Pixel Type; };
template<> struct AccumPixelType<ConstBGR24Pixel> { typedef BGR96Pixel Type; };

template<> struct AccumPixelType<RGBA32Pixel> { typedef RGBA128Pixel Type; };
template<> struct AccumPixelType<ConstRGBA32Pixel> { typedef RGBA128Pixel Type; };

template<> struct AccumPixelType<ARGB32Pixel> { typedef ARGB128Pixel Type; };
template<> struct AccumPixelType<ConstARGB32Pixel> { typedef ARGB128Pixel Type; };

template<> struct AccumPixelType<BGRA32Pixel> { typedef BGRA128Pixel Type; };
template<> struct AccumPixelType<ConstBGRA32Pixel> { typedef BGRA128Pixel Type; };

template<> struct AccumPixelType<ABGR32Pixel> { typedef ABGR128Pixel Type; };
template<> struct AccumPixelType<ConstABGR32Pixel> { typedef ABGR128Pixel Type; };

// I'm bringing back some old HQ scaler that I wrote years ago just to get
// some decent downsampling in ITL. This is horribly slow btw.
template<class SRC_RBGPIXMAP, class DST_RBGPIXMAP>
void ITL_ScaleHQ(const SRC_RBGPIXMAP &input, DST_RBGPIXMAP *output)
{
	int srcWidth = input.width();
	int srcHeight = input.height();

	int dstWidth = output->width();
	int dstHeight = output->height();
	
	int srcWidthModDstWidth = srcWidth % dstWidth;
	int srcHeightModDstHeight = srcHeight % dstHeight;
	
	for (int y = 0; (y < dstHeight); y++)
	{
		for (int x = 0; (x < dstWidth); x++)
		{
			int sx, sy;

			int startx = x * srcWidth / dstWidth;
			int endx = ((x+1) * srcWidth + (dstWidth - 1)) / dstWidth;
			
			int starty = y * srcHeight / dstHeight;
			int endy = ((y+1) * srcHeight + (dstHeight - 1)) / dstHeight;

			//	Top Left Pixel
			long weight = (dstWidth  - ((x * (srcWidthModDstWidth))   % dstWidth)) *
						  (dstHeight - ((y * (srcHeightModDstHeight)) % dstHeight));

			typedef typename AccumPixelType<SRC_RBGPIXMAP::PixelType>::Type AccumPixelType;
			AccumPixelType sumPixel = AccumPixelType(input[starty][startx]) * weight;
			long wSum = weight;

			//	Top Row
			if (endx > startx + 1)
			{
				weight = (dstWidth) *
						 (dstHeight - ((y * (srcHeightModDstHeight)) % dstHeight));

				for (sx = startx + 1; sx < endx - 1; sx++)
				{
					sumPixel += AccumPixelType(input[starty][sx]) * weight;
					wSum += weight;
				}			

				weight = ( (((x+1) * (srcWidthModDstWidth) - 1) % dstWidth) + 1) *
						 (dstHeight - ((y * (srcHeightModDstHeight)) % dstHeight));

				sumPixel += AccumPixelType(input[starty][sx]) * weight;
				wSum += weight;
			}


			//	Top Row

			if (endy > starty + 1)
			{
				for (sy = starty + 1; sy < endy - 1; sy++)
				{
					weight = (dstWidth  - ((x * (srcWidthModDstWidth )) % dstWidth )) *
							 (dstHeight);
							 
					sumPixel += AccumPixelType(input[sy][startx]) * weight;
					wSum += weight;

					if (endx > startx + 1)
					{
						weight = (dstWidth) * (dstHeight);

						for (sx = startx + 1; sx < endx - 1; sx++)
						{
							sumPixel += AccumPixelType(input[sy][sx]) * weight;
							wSum += weight;
						}			

						weight = ( (((x+1) * (srcWidthModDstWidth) - 1) % dstWidth) + 1) *
								 (dstHeight);

						sumPixel += AccumPixelType(input[sy][sx]) * weight;
						wSum += weight;
					}

				}			

				weight = (dstWidth  - ((x * (srcWidthModDstWidth )) % dstWidth )) *
						 ( (((y+1) * (srcHeightModDstHeight) - 1) % dstHeight) + 1);

				sumPixel += AccumPixelType(input[sy][startx]) * weight;
				wSum += weight;

				if (endx > startx + 1)
				{
					weight = (dstWidth) *
							 ( (((y+1) * (srcHeightModDstHeight) - 1) % dstHeight) + 1);

					for (sx = startx + 1; sx < endx - 1; sx++)
					{
						sumPixel += AccumPixelType(input[sy][sx]) * weight;
						wSum += weight;
					}			

					weight = ( (((x+1) * (srcWidthModDstWidth ) - 1) % dstWidth ) + 1) *
							 ( (((y+1) * (srcHeightModDstHeight) - 1) % dstHeight) + 1);


					sumPixel += AccumPixelType(input[sy][sx]) * weight;
					wSum += weight;
				}
			}
			(*output)[y][x] = (sumPixel + wSum/2) / wSum;
		}
	}
	output->setResolution(Resolution(input.resolution().x * input.width() / output->width(), input.resolution().y * input.height()/output->height()));
}

ITL_DLL_EXPORT void ITL_ScaleHQ_BGR24Pixel(const PixMap<BGR24Pixel> &input, PixMap<BGR24Pixel> *output)
{	ITL_ScaleHQ(input, output);	}

ITL_DLL_EXPORT void ITL_ScaleHQ_BGR24Pixel(const PixMap<ConstBGR24Pixel> &input, PixMap<BGR24Pixel> *output)
{	ITL_ScaleHQ(input, output);	}

ITL_DLL_EXPORT void ITL_ScaleHQ_BGR24Pixel(const PixMap<ConstBGR24Pixel, PixMapDrawsFromBottom> &input, PixMap<BGR24Pixel, PixMapDrawsFromBottom> *output)
{	ITL_ScaleHQ(input, output);	}

ITL_DLL_EXPORT void ITL_ScaleHQ_RGB24Pixel(const PixMap<RGB24Pixel> &input, PixMap<RGB24Pixel> *output)
{	ITL_ScaleHQ(input, output);	}

ITL_DLL_EXPORT void ITL_ScaleHQ_RGB24Pixel(const PixMap<ConstRGB24Pixel> &input, PixMap<RGB24Pixel> *output)
{	ITL_ScaleHQ(input, output);	}

ITL_DLL_EXPORT void ITL_ScaleHQ_RGB24Pixel(const PixMap<ConstRGB24Pixel, PixMapDrawsFromBottom> &input, PixMap<RGB24Pixel, PixMapDrawsFromBottom> *output)
{	ITL_ScaleHQ(input, output);	}

ITL_DLL_EXPORT void ITL_ScaleHQ_RGBA32Pixel(const PixMap<RGBA32Pixel> &input, PixMap<RGBA32Pixel> *output)
{	ITL_ScaleHQ(input, output);	}

ITL_DLL_EXPORT void ITL_ScaleHQ_RGBA32Pixel(const PixMap<ConstRGBA32Pixel> &input, PixMap<RGBA32Pixel> *output)
{	ITL_ScaleHQ(input, output);	}

ITL_DLL_EXPORT void ITL_ScaleHQ_RGBA32Pixel(const PixMap<ConstRGBA32Pixel, PixMapDrawsFromBottom> &input, PixMap<RGBA32Pixel, PixMapDrawsFromBottom> *output)
{	ITL_ScaleHQ(input, output);	}

ITL_DLL_EXPORT void ITL_ScaleHQ_ABGR32Pixel(const PixMap<ABGR32Pixel> &input, PixMap<ABGR32Pixel> *output)
{	ITL_ScaleHQ(input, output);	}

ITL_DLL_EXPORT void ITL_ScaleHQ_ABGR32Pixel(const PixMap<ConstABGR32Pixel> &input, PixMap<ABGR32Pixel> *output)
{	ITL_ScaleHQ(input, output);	}

ITL_DLL_EXPORT void ITL_ScaleHQ_ABGR32Pixel(const PixMap<ConstABGR32Pixel, PixMapDrawsFromBottom> &input, PixMap<ABGR32Pixel, PixMapDrawsFromBottom> *output)
{	ITL_ScaleHQ(input, output);	}

ITL_DLL_EXPORT void ITL_ScaleHQ_BGRA32Pixel(const PixMap<BGRA32Pixel> &input, PixMap<BGRA32Pixel> *output)
{	ITL_ScaleHQ(input, output);	}

ITL_DLL_EXPORT void ITL_ScaleHQ_BGRA32Pixel(const PixMap<ConstBGRA32Pixel> &input, PixMap<BGRA32Pixel> *output)
{	ITL_ScaleHQ(input, output);	}

ITL_DLL_EXPORT void ITL_ScaleHQ_BGRA32Pixel(const PixMap<ConstBGRA32Pixel, PixMapDrawsFromBottom> &input, PixMap<BGRA32Pixel, PixMapDrawsFromBottom> *output)
{	ITL_ScaleHQ(input, output);	}

ITL_DLL_EXPORT void ITL_ScaleHQ_ARGB32Pixel(const PixMap<ARGB32Pixel> &input, PixMap<ARGB32Pixel> *output)
{	ITL_ScaleHQ(input, output);	}

ITL_DLL_EXPORT void ITL_ScaleHQ_ARGB32Pixel(const PixMap<ConstARGB32Pixel> &input, PixMap<ARGB32Pixel> *output)
{	ITL_ScaleHQ(input, output);	}

ITL_DLL_EXPORT void ITL_ScaleHQ_ARGB32Pixel(const PixMap<ConstARGB32Pixel, PixMapDrawsFromBottom> &input, PixMap<ARGB32Pixel, PixMapDrawsFromBottom> *output)
{	ITL_ScaleHQ(input, output);	}



}

