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
#ifndef __ITL_PIXMAPMANIP_H__
#define __ITL_PIXMAPMANIP_H__

//==============================================================================
// FILE PixMapManip.h
//==============================================================================
// High level pixmap functions
//------------------------------------------------------------------------------

//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================
#include "PixRowRef.h"
#include "PixMapComposer.h"
#include "PixMapResolution.h"
#include "../PixelConvert/PixelConverter.h"
#include "../Algo/Scaling.h"

namespace ITL {

#ifdef WIN32
#ifdef ITL_EXPORTS
#define ITL_DLL_EXPORT __declspec(dllexport)
#else
#define ITL_DLL_EXPORT __declspec(dllimport)
#endif
#else
#define ITL_DLL_EXPORT
#endif

	
ITL_DLL_EXPORT void ITL_ScaleHQ_RGB24Pixel(const PixMap<RGB24Pixel> &input, PixMap<RGB24Pixel> *output);
ITL_DLL_EXPORT void ITL_ScaleHQ_RGB24Pixel(const PixMap<ConstRGB24Pixel> &input, PixMap<RGB24Pixel> *output);
ITL_DLL_EXPORT void ITL_ScaleHQ_RGB24Pixel(const PixMap<ConstRGB24Pixel, PixMapDrawsFromBottom> &input, PixMap<RGB24Pixel, PixMapDrawsFromBottom> *output);

ITL_DLL_EXPORT void ITL_ScaleHQ_BGR24Pixel(const PixMap<BGR24Pixel> &input, PixMap<BGR24Pixel> *output);
ITL_DLL_EXPORT void ITL_ScaleHQ_BGR24Pixel(const PixMap<ConstBGR24Pixel> &input, PixMap<BGR24Pixel> *output);
ITL_DLL_EXPORT void ITL_ScaleHQ_BGR24Pixel(const PixMap<ConstBGR24Pixel, PixMapDrawsFromBottom> &input, PixMap<BGR24Pixel, PixMapDrawsFromBottom> *output);

ITL_DLL_EXPORT void ITL_ScaleHQ_RGBA32Pixel(const PixMap<RGBA32Pixel> &input, PixMap<RGBA32Pixel> *output);
ITL_DLL_EXPORT void ITL_ScaleHQ_RGBA32Pixel(const PixMap<ConstRGBA32Pixel> &input, PixMap<RGBA32Pixel> *output);
ITL_DLL_EXPORT void ITL_ScaleHQ_RGBA32Pixel(const PixMap<ConstRGBA32Pixel, PixMapDrawsFromBottom> &input, PixMap<RGBA32Pixel, PixMapDrawsFromBottom> *output);

ITL_DLL_EXPORT void ITL_ScaleHQ_ABGR32Pixel(const PixMap<ABGR32Pixel> &input, PixMap<ABGR32Pixel> *output);
ITL_DLL_EXPORT void ITL_ScaleHQ_ABGR32Pixel(const PixMap<ConstABGR32Pixel> &input, PixMap<ABGR32Pixel> *output);
ITL_DLL_EXPORT void ITL_ScaleHQ_ABGR32Pixel(const PixMap<ConstABGR32Pixel, PixMapDrawsFromBottom> &input, PixMap<ABGR32Pixel, PixMapDrawsFromBottom> *output);

ITL_DLL_EXPORT void ITL_ScaleHQ_BGRA32Pixel(const PixMap<BGRA32Pixel> &input, PixMap<BGRA32Pixel> *output);
ITL_DLL_EXPORT void ITL_ScaleHQ_BGRA32Pixel(const PixMap<ConstBGRA32Pixel> &input, PixMap<BGRA32Pixel> *output);
ITL_DLL_EXPORT void ITL_ScaleHQ_BGRA32Pixel(const PixMap<ConstBGRA32Pixel, PixMapDrawsFromBottom> &input, PixMap<BGRA32Pixel, PixMapDrawsFromBottom> *output);

ITL_DLL_EXPORT void ITL_ScaleHQ_ARGB32Pixel(const PixMap<ARGB32Pixel> &input, PixMap<ARGB32Pixel> *output);
ITL_DLL_EXPORT void ITL_ScaleHQ_ARGB32Pixel(const PixMap<ConstARGB32Pixel> &input, PixMap<ARGB32Pixel> *output);
ITL_DLL_EXPORT void ITL_ScaleHQ_ARGB32Pixel(const PixMap<ConstARGB32Pixel, PixMapDrawsFromBottom> &input, PixMap<ARGB32Pixel, PixMapDrawsFromBottom> *output);


//==============================================================================
// CLASS PixMapManip
//==============================================================================
class PixMapManip
{
private:
	class PixMapConvertFunct
	{
	public:
		template<typename SRC_PIXELPACKET, typename DST_PIXELPACKET>
		void operator()(const SRC_PIXELPACKET &src, DST_PIXELPACKET *dst) const
		{
			PixelConvert(src, dst);
		}

		template<typename SRC_PIXELPACKET0, typename SRC_PIXELPACKET1, typename DST_PIXELPACKET>
		void operator()(const SRC_PIXELPACKET0 &src0, const SRC_PIXELPACKET1 &src1, DST_PIXELPACKET *dst) const
		{
			PixelConvert(src0, src1, dst);
		}

		template<typename SRC_PIXELPACKET0, typename SRC_PIXELPACKET1, typename SRC_PIXELPACKET2, typename SRC_PIXELPACKET3, typename SRC_PIXELPACKET4, typename SRC_PIXELPACKET5, typename SRC_PIXELPACKET6, typename SRC_PIXELPACKET7, typename DST_PIXELPACKET>
		void operator()(const SRC_PIXELPACKET0 &src0, const SRC_PIXELPACKET1 &src1, const SRC_PIXELPACKET2 &src2, const SRC_PIXELPACKET3 &src3, const SRC_PIXELPACKET4 &src4, const SRC_PIXELPACKET5 &src5, const SRC_PIXELPACKET6 &src6, const SRC_PIXELPACKET7 &src7, DST_PIXELPACKET *dst) const
		{
			PixelConvert(src0, src1, src2, src3, src4, src5, src6, src7, dst);
		}
	};

public:
	//--------------------------------------------------------------------------
	// convert
	template<typename SRC_PIXELPACKET, typename SRC_ORIENTATION, typename DST_PIXELPACKET, typename DST_ORIENTATION>
	static void convert(const PixMap<SRC_PIXELPACKET, SRC_ORIENTATION> &src, PixMap<DST_PIXELPACKET, DST_ORIENTATION> *dst)
	{
		PixMapComposer1In1Out::forEach(src, dst, PixMapConvertFunct());
	}

	//--------------------------------------------------------------------------
	// copy
	template<typename PIXELPACKET>
	static void copy(const PixMap<PIXELPACKET> &src, const PixMap<PIXELPACKET> &dst)
	{
		convert(src, dst);
	}

	template<typename SRC_PIXELPACKET, typename SRC_ORIENTATION, typename DST_PIXELPACKET, typename DST_ORIENTATION, int SRC_PIXEL_PER_PACKET=SRC_PIXELPACKET::PIXEL_PER_PACKET, int DST_PIXEL_PER_PACKET=DST_PIXELPACKET::PIXEL_PER_PACKET>
	class Resampler;

	template<typename SRC_PIXELPACKET, typename SRC_ORIENTATION, typename DST_PIXELPACKET, typename DST_ORIENTATION>
	struct Resampler<SRC_PIXELPACKET, SRC_ORIENTATION, DST_PIXELPACKET, DST_ORIENTATION, 1, 1>
	{
		static void resample(const PixMap<SRC_PIXELPACKET, SRC_ORIENTATION> &src, PixMap<DST_PIXELPACKET, DST_ORIENTATION> *dst)
		{
			ASSERT(dst->width() != 0);
			ASSERT(dst->height() != 0);
			ASSERT(src.width() != 0);
			ASSERT(src.height() != 0);

			for (int y = 0; y < dst->height(); ++y)
			{
				for (int x = 0; x < dst->width(); ++x)
				{
					int sx = x * src.width() / dst->width();
					int sy = y * src.height() / dst->height();
					(*dst)[y][x].convert(src[sy][sx]);
				}
			}
			dst->setResolution(Resolution(src.resolution().x * src.width() / dst->width(), src.resolution().y * src.height()/dst->height()));
			printf("resampling from %dx%d to %dx%d (ratio %f -> %f)\n", src.width(), src.height(), dst->width(), dst->height(), src.pixelRatio(), dst->pixelRatio());
		}
	};

	template<typename ORIENTATION> struct Resampler<BGR24Pixel, ORIENTATION, BGR24Pixel, ORIENTATION, 1, 1>
	{
		static void resample(const PixMap<BGR24Pixel, ORIENTATION> &src, PixMap<BGR24Pixel, ORIENTATION> *dst)
		{
			ITL_ScaleHQ_BGR24Pixel(src, dst);
		}
	};

	template<typename ORIENTATION> struct Resampler<ConstBGR24Pixel, ORIENTATION, BGR24Pixel, ORIENTATION, 1, 1>
	{
		static void resample(const PixMap<ConstBGR24Pixel, ORIENTATION> &src, PixMap<BGR24Pixel, ORIENTATION> *dst)
		{
			ITL_ScaleHQ_BGR24Pixel(src, dst);
		}
	};

	template<typename ORIENTATION> struct Resampler<RGB24Pixel, ORIENTATION, RGB24Pixel, ORIENTATION, 1, 1>
	{
		static void resample(const PixMap<RGB24Pixel, ORIENTATION> &src, PixMap<RGB24Pixel, ORIENTATION> *dst)
		{
			ITL_ScaleHQ_RGB24Pixel(src, dst);
		}
	};

	template<typename ORIENTATION> struct Resampler<ConstRGB24Pixel, ORIENTATION, RGB24Pixel, ORIENTATION, 1, 1>
	{
		static void resample(const PixMap<ConstRGB24Pixel, ORIENTATION> &src, PixMap<RGB24Pixel, ORIENTATION> *dst)
		{
			ITL_ScaleHQ_RGB24Pixel(src, dst);
		}
	};

	template<typename ORIENTATION> struct Resampler<ConstRGBA32Pixel, ORIENTATION, RGBA32Pixel, ORIENTATION, 1, 1>
	{
		static void resample(const PixMap<ConstRGBA32Pixel, ORIENTATION> &src, PixMap<RGBA32Pixel, ORIENTATION> *dst)
		{
			ITL_ScaleHQ_RGBA32Pixel(src, dst);
		}
	};

	template<typename ORIENTATION> struct Resampler<RGBA32Pixel, ORIENTATION, RGBA32Pixel, ORIENTATION, 1, 1>
	{
		static void resample(const PixMap<RGBA32Pixel, ORIENTATION> &src, PixMap<RGBA32Pixel, ORIENTATION> *dst)
		{
			ITL_ScaleHQ_RGBA32Pixel(src, dst);
		}
	};

	template<typename ORIENTATION> struct Resampler<ConstABGR32Pixel, ORIENTATION, ABGR32Pixel, ORIENTATION, 1, 1>
	{
		static void resample(const PixMap<ConstABGR32Pixel, ORIENTATION> &src, PixMap<ABGR32Pixel, ORIENTATION> *dst)
		{
			ITL_ScaleHQ_ABGR32Pixel(src, dst);
		}
	};

	template<typename ORIENTATION> struct Resampler<ABGR32Pixel, ORIENTATION, ABGR32Pixel, ORIENTATION, 1, 1>
	{
		static void resample(const PixMap<ABGR32Pixel, ORIENTATION> &src, PixMap<ABGR32Pixel, ORIENTATION> *dst)
		{
			ITL_ScaleHQ_ABGR32Pixel(src, dst);
		}
	};

	template<typename ORIENTATION> struct Resampler<ConstBGRA32Pixel, ORIENTATION, BGRA32Pixel, ORIENTATION, 1, 1>
	{
		static void resample(const PixMap<ConstBGRA32Pixel, ORIENTATION> &src, PixMap<BGRA32Pixel, ORIENTATION> *dst)
		{
			ITL_ScaleHQ_BGRA32Pixel(src, dst);
		}
	};

	template<typename ORIENTATION> struct Resampler<BGRA32Pixel, ORIENTATION, BGRA32Pixel, ORIENTATION, 1, 1>
	{
		static void resample(const PixMap<BGRA32Pixel, ORIENTATION> &src, PixMap<BGRA32Pixel, ORIENTATION> *dst)
		{
			ITL_ScaleHQ_BGRA32Pixel(src, dst);
		}
	};

	template<typename ORIENTATION> struct Resampler<ConstARGB32Pixel, ORIENTATION, ARGB32Pixel, ORIENTATION, 1, 1>
	{
		static void resample(const PixMap<ConstARGB32Pixel, ORIENTATION> &src, PixMap<ARGB32Pixel, ORIENTATION> *dst)
		{
			ITL_ScaleHQ_ARGB32Pixel(src, dst);
		}
	};

	template<typename ORIENTATION> struct Resampler<ARGB32Pixel, ORIENTATION, ARGB32Pixel, ORIENTATION, 1, 1>
	{
		static void resample(const PixMap<ARGB32Pixel, ORIENTATION> &src, PixMap<ARGB32Pixel, ORIENTATION> *dst)
		{
			ITL_ScaleHQ_ARGB32Pixel(src, dst);
		}
	};

	template<typename SRC_PIXELPACKET, typename SRC_ORIENTATION, typename DST_PIXELPACKET, typename DST_ORIENTATION>
	struct Resampler<SRC_PIXELPACKET, SRC_ORIENTATION, DST_PIXELPACKET, DST_ORIENTATION, 2, 2>
	{
		static void resample(const PixMap<SRC_PIXELPACKET, SRC_ORIENTATION> &src, PixMap<DST_PIXELPACKET, DST_ORIENTATION> *dst)
		{
			for (int y = 0; y < dst->height(); ++y)
			{
				for (int x = 0; x < dst->width()/2; ++x)
				{
					int sx = x * src.width() / dst->width();
					int sy = y * src.height() / dst->height();
					(*dst)[y][x].convert(src[sy][sx]);
				}
			}
		}
	};

	template<typename SRC_PIXELPACKET, typename SRC_ORIENTATION, typename DST_PIXELPACKET, typename DST_ORIENTATION>
	struct Resampler<SRC_PIXELPACKET, SRC_ORIENTATION, DST_PIXELPACKET, DST_ORIENTATION, 2, 1>
	{
		static void resample(const PixMap<SRC_PIXELPACKET, SRC_ORIENTATION> &src, PixMap<DST_PIXELPACKET, DST_ORIENTATION> *dst)
		{
			for (int y = 0; y < dst->height(); ++y)
			{
				for (int x = 0; x < dst->width()/2; ++x)
				{
					int sx = x * src.width() / dst->width();
					int sy = y * src.height() / dst->height();
					(*dst)[y][x*2+0].convert(src[sy][sx].pixel0());
					(*dst)[y][x*2+1].convert(src[sy][sx].pixel1());
				}
			}
		}
	};


	template<typename SRC_PIXELPACKET, typename SRC_ORIENTATION, typename DST_PIXELPACKET, typename DST_ORIENTATION>
	struct Resampler<SRC_PIXELPACKET, SRC_ORIENTATION, DST_PIXELPACKET, DST_ORIENTATION, 8, 1>
	{
		static void resample(const PixMap<SRC_PIXELPACKET, SRC_ORIENTATION> &src, PixMap<DST_PIXELPACKET, DST_ORIENTATION> *dst)
		{
			for (int y = 0; y < dst->height(); ++y)
			{
				for (int x = 0; x < dst->width()/8; ++x)
				{
					int sx = x * src.width() / dst->width();
					int sy = y * src.height() / dst->height();
					(*dst)[y][x*8+0].convert(src[sy][sx].pixel0());
					(*dst)[y][x*8+1].convert(src[sy][sx].pixel1());
					(*dst)[y][x*8+2].convert(src[sy][sx].pixel2());
					(*dst)[y][x*8+3].convert(src[sy][sx].pixel3());
					(*dst)[y][x*8+4].convert(src[sy][sx].pixel4());
					(*dst)[y][x*8+5].convert(src[sy][sx].pixel5());
					(*dst)[y][x*8+6].convert(src[sy][sx].pixel6());
					(*dst)[y][x*8+7].convert(src[sy][sx].pixel7());
				}
			}
		}
	};


	template<typename SRC_PIXELPACKET, typename SRC_ORIENTATION, typename DST_PIXELPACKET, typename DST_ORIENTATION>
	struct Resampler<SRC_PIXELPACKET, SRC_ORIENTATION, DST_PIXELPACKET, DST_ORIENTATION, 8, 2>
	{
		static void resample(const PixMap<SRC_PIXELPACKET, SRC_ORIENTATION> &src, PixMap<DST_PIXELPACKET, DST_ORIENTATION> *dst)
		{
			for (int y = 0; y < dst->height(); ++y)
			{
				for (int x = 0; x < dst->width()/8; ++x)
				{
					int sx = x * src.width() / dst->width();
					int sy = y * src.height() / dst->height();
					(*dst)[y][x*4+0].convert(src[sy][sx].pixel0(), src[sy][sx].pixel1());
					(*dst)[y][x*4+1].convert(src[sy][sx].pixel2(), src[sy][sx].pixel3());
					(*dst)[y][x*4+2].convert(src[sy][sx].pixel4(), src[sy][sx].pixel5());
					(*dst)[y][x*4+3].convert(src[sy][sx].pixel6(), src[sy][sx].pixel7());
				}
			}
		}
	};


	template<typename SRC_PIXELPACKET, typename SRC_ORIENTATION, typename DST_PIXELPACKET, typename DST_ORIENTATION>
	struct Resampler<SRC_PIXELPACKET, SRC_ORIENTATION, DST_PIXELPACKET, DST_ORIENTATION, 1, 2>
	{
		static void resample(const PixMap<SRC_PIXELPACKET, SRC_ORIENTATION> &src, PixMap<DST_PIXELPACKET, DST_ORIENTATION> *dst)
		{
			for (int y = 0; y < dst->height(); ++y)
			{
				for (int x = 0; x < dst->width()/2; ++x)
				{
					int sx = x * src.width() / dst->width();
					int sy = y * src.height() / dst->height();
					(*dst)[y][x].convert(src[sy][sx*2+0], src[sy][sx*2+1]);
				}
			}
		}
	};


	template<typename SRC_PIXELPACKET, typename DST_PIXELPACKET, typename ORIENTATION>
	struct Resampler<SRC_PIXELPACKET, ORIENTATION, DST_PIXELPACKET, ORIENTATION, 1, 8>
	{
		static void resample(const PixMap<SRC_PIXELPACKET, ORIENTATION> &src, PixMap<DST_PIXELPACKET, ORIENTATION> *dst)
		{
			for (int y = 0; y < dst->height(); ++y)
			{
				for (int x = 0; x < dst->width()/8; ++x)
				{
					int sx = x * src.width() / dst->width();
					int sy = y * src.height() / dst->height();
					(*dst)[y][x].convert(
						src[sy][sx*8+0], src[sy][sx*8+1], src[sy][sx*8+2], src[sy][sx*8+3],
						src[sy][sx*8+4], src[sy][sx*8+5], src[sy][sx*8+6], src[sy][sx*8+7]
					);
				}
			}
		}
	};


	template<typename SRC_PIXELPACKET, typename DST_PIXELPACKET, typename ORIENTATION>
	struct Resampler<SRC_PIXELPACKET, ORIENTATION, DST_PIXELPACKET, ORIENTATION, 8, 8>
	{
		static void resample(const PixMap<SRC_PIXELPACKET, ORIENTATION> &src, PixMap<DST_PIXELPACKET, ORIENTATION> *dst)
		{
			for (int y = 0; y < dst->height(); ++y)
			{
				for (int x = 0; x < dst->width()/8; ++x)
				{
					int sx = x * src.width() / dst->width();
					int sy = y * src.height() / dst->height();
					(*dst)[y][x].convert(
						src[sy][sx].pixel0(), src[sy][sx].pixel1(), 
						src[sy][sx].pixel2(), src[sy][sx].pixel3(), 
						src[sy][sx].pixel4(), src[sy][sx].pixel5(), 
						src[sy][sx].pixel6(), src[sy][sx].pixel7()
					);
				}
			}
		}
	};


	template<typename SRC_PIXELPACKET, typename DST_PIXELPACKET, typename ORIENTATION>
	struct Resampler<SRC_PIXELPACKET, ORIENTATION, DST_PIXELPACKET, ORIENTATION, 2, 8>
	{
		static void resample(const PixMap<SRC_PIXELPACKET, ORIENTATION> &src, PixMap<DST_PIXELPACKET, ORIENTATION> *dst)
		{
			for (int y = 0; y < dst->height(); ++y)
			{
				for (int x = 0; x < dst->width()/8; ++x)
				{
					int sx = x * src.width() / dst->width();
					int sy = y * src.height() / dst->height();
					(*dst)[y][x].convert(
						src[sy][sx*4+0].pixel0(), src[sy][sx*4+0].pixel1(),
						src[sy][sx*4+1].pixel0(), src[sy][sx*4+1].pixel1(),
						src[sy][sx*4+2].pixel0(), src[sy][sx*4+2].pixel1(),
						src[sy][sx*4+3].pixel0(), src[sy][sx*4+3].pixel1()
					);
				}
			}
		}
	};




	template<typename SRC_PIXELPACKET, typename SRC_ORIENTATION, typename DST_PIXELPACKET, typename DST_ORIENTATION>
	static void resample(const PixMap<SRC_PIXELPACKET, SRC_ORIENTATION> &src, PixMap<DST_PIXELPACKET, DST_ORIENTATION> *dst)
	{
		Resampler<SRC_PIXELPACKET, SRC_ORIENTATION, DST_PIXELPACKET, DST_ORIENTATION>::resample(src, dst);
	}
};


}

#endif // __ITL_PIXMAPMANIP_H__


