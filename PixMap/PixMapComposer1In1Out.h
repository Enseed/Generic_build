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
#ifndef __ITL_PIXMAPCOMPOSER1IN1OUT_H__
#define __ITL_PIXMAPCOMPOSER1IN1OUT_H__

#define UNIMPLEMENTED assert(0);

//==============================================================================
// FILE PixMapComposer1In1Out.h
//==============================================================================
// Implements the Composer for 1 pixel in, 1 pixel out.  This can be used for
// example to copy, convert, apply pixel transformation (E.g. gamma, brightness)
//
// USAGE:
//    class AddGain {
//        int _gain; 
//    public:
//        AddGain(int gain) : _gain(gain) {}
//        void operator()(const RGB24Pixel &src, RGB24Pixel *dst) const
//        { dst->setRGB(src.red()+gain, src.green()+gain, src.blue()+gain); }
//    };
// 
//    PixMap<RGB24Pixel> original(512, 512);
//    PixMap<RGB24Pixel> transformed(512, 512);
//    PixMapComposer1In1Out::forEach(original.ref(), transformed.ref(), AddGain(10));
//------------------------------------------------------------------------------

//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================
#include "PixRowRef.h"
#include <cassert>

namespace ITL {

//==============================================================================
// CLASS PixMapComposer1In1OutImp
//==============================================================================

template<typename PIXELTYPE, int PLANECOUNT=PIXELTYPE::PLANE_COUNT>
struct PixelPacketReference
{	typedef PIXELTYPE Type;  };

template<typename PIXELTYPE>
struct PixelPacketReference<PIXELTYPE, 1>
{	typedef PIXELTYPE &Type;  };


template<typename IN_PIXELPACKET, typename IN_ORIENTATION, typename OUT_PIXELPACKET, typename OUT_ORIENTATION>
class PixMapComposer1In1OutImp
{
public:
	template<typename FUNCT>
	static void forEach(const PixMap<IN_PIXELPACKET, IN_ORIENTATION> &inPixMap, PixMap<OUT_PIXELPACKET, OUT_ORIENTATION> *outPixMap, const FUNCT &funct)
	{
		forEachRow(inPixMap, outPixMap, ForEachPixelInRowFunctor< FUNCT >(funct));
	}

	template<typename FUNCT>
	static void forEachRow(const PixMap<IN_PIXELPACKET, IN_ORIENTATION> &inPixMap, PixMap<OUT_PIXELPACKET, OUT_ORIENTATION> *outPixMap, const FUNCT &funct)
	{
		// make sure we iterate in the same direction. If both are upside down, we might want
		// to specialize this template later...
		typename PixMap<IN_PIXELPACKET, IN_ORIENTATION>::ConstTopToBottomIterator srcIter = inPixMap.beginFromTop();
		typename PixMap<OUT_PIXELPACKET, OUT_ORIENTATION>::TopToBottomIterator dstIter = outPixMap->beginFromTop();

		int y = 0;
		int height = inPixMap.height();
		for (; srcIter != inPixMap.endFromTop(); ++srcIter, ++dstIter)
		{
			funct(*srcIter, *dstIter);
			++y;
		}
	}

private:
	template<typename FUNCT, int IN_PIXELPERPACKET=IN_PIXELPACKET::PIXEL_PER_PACKET, int OUT_PIXELPERPACKET=OUT_PIXELPACKET::PIXEL_PER_PACKET>
	class ForEachPixelInRowFunctor {};

	template<typename FUNCT, int PIXEL_PER_PACKET>
	class ForEachPixelInRowFunctor<FUNCT, PIXEL_PER_PACKET, PIXEL_PER_PACKET>
	{
		const FUNCT &_funct;
	public:
		ForEachPixelInRowFunctor(const FUNCT &funct) : _funct(funct) {}

		void operator()(const PixRowRef<IN_PIXELPACKET> &inRow, PixRowRef<OUT_PIXELPACKET> &outRow) const
		{
 			// N Pixel per packet in, N pixel per packet out (easy case)
			typename PixRowRef<IN_PIXELPACKET>::ConstIterator srcIter = inRow.begin();
			typename PixRowRef<OUT_PIXELPACKET>::Iterator dstIter = outRow.begin();
			int i = 0;
			for (; dstIter != outRow.end(); ++srcIter, ++dstIter)
			{
				// if there is only 1 plane, we have to take a reference
				// if there is > 1 plane, we have to take an instance
				typename PixelPacketReference<OUT_PIXELPACKET>::Type dstPixRef = *dstIter;
				_funct(*srcIter, &dstPixRef);
				++i;
			}
		}
	};

	template<typename FUNCT>
	class ForEachPixelInRowFunctor<FUNCT, 2, 1>
	{
		const FUNCT &_funct;
	public:
		ForEachPixelInRowFunctor(const FUNCT &funct) : _funct(funct) {}

		void operator()(const PixRowRef<IN_PIXELPACKET> &inRow, PixRowRef<OUT_PIXELPACKET> &outRow) const
		{
 			// 2 Pixel per packet in, 1 pixel per packet out (e.g. 422 -> 444)
			typename PixRowRef<IN_PIXELPACKET>::ConstIterator srcIter = inRow.begin();
			typename PixRowRef<OUT_PIXELPACKET>::Iterator dstIter = outRow.begin();

			// In this case, it's safer to iterate over the input since
			// we are 100% we cannot miss the end()
			for (; srcIter != inRow.end(); ++srcIter, ++dstIter)
			{
				typename PixelPacketReference<OUT_PIXELPACKET>::Type outRef1 = *dstIter++;
				_funct(srcIter->pixel0(), &outRef1);

				typename PixelPacketReference<OUT_PIXELPACKET>::Type outRef2 = *dstIter;
				_funct(srcIter->pixel1(), &outRef2);
			}
		}
	};

	template<typename FUNCT>
	class ForEachPixelInRowFunctor<FUNCT, 1, 2>
	{
		const FUNCT &_funct;
	public:
		ForEachPixelInRowFunctor(const FUNCT &funct) : _funct(funct) {}

		void operator()(const PixRowRef<IN_PIXELPACKET> &inRow, PixRowRef<OUT_PIXELPACKET> &outRow) const
		{
 			// 1 Pixel per packet in, 2 pixel per packet out (e.g. 444 -> 422)
			typename PixRowRef<IN_PIXELPACKET>::ConstIterator srcIter = inRow.begin();
			typename PixRowRef<OUT_PIXELPACKET>::Iterator dstIter = outRow.begin();

			// In this case, it's probably safer to iterate over the output since
			// we are 100% we cannot miss the end()
			for (; dstIter != outRow.end(); ++srcIter, ++dstIter)
			{
				typename PixRowRef<IN_PIXELPACKET>::ConstIterator srcIter0  = srcIter++;
				typename PixRowRef<IN_PIXELPACKET>::ConstIterator srcIter1  = srcIter;
				_funct(*srcIter0, *srcIter1, &*dstIter);
			}
		}
	};

	template<typename FUNCT>
	class ForEachPixelInRowFunctor<FUNCT, 8, 1>
	{
		const FUNCT &_funct;
	public:
		ForEachPixelInRowFunctor(const FUNCT &funct) : _funct(funct) {}

		void operator()(const PixRowRef<IN_PIXELPACKET> &inRow, PixRowRef<OUT_PIXELPACKET> &outRow) const
		{
 			// 2 Pixel per packet in, 1 pixel per packet out (e.g. 422 -> 444)
			typename PixRowRef<IN_PIXELPACKET>::ConstIterator srcIter = inRow.begin();
			typename PixRowRef<OUT_PIXELPACKET>::Iterator dstIter = outRow.begin();

			// In this case, it's safer to iterate over the input since
			// we are 100% we cannot miss the end()
			for (; srcIter != inRow.end(); ++srcIter, ++dstIter)
			{
				UNIMPLEMENTED;
			}
		}
	};

	template<typename FUNCT>
	class ForEachPixelInRowFunctor<FUNCT, 8, 2>
	{
		const FUNCT &_funct;
	public:
		ForEachPixelInRowFunctor(const FUNCT &funct) : _funct(funct) {}

		void operator()(const PixRowRef<IN_PIXELPACKET> &inRow, PixRowRef<OUT_PIXELPACKET> &outRow) const
		{
 			// 2 Pixel per packet in, 1 pixel per packet out (e.g. 422 -> 444)
			typename PixRowRef<IN_PIXELPACKET>::ConstIterator srcIter = inRow.begin();
			typename PixRowRef<OUT_PIXELPACKET>::Iterator dstIter = outRow.begin();

			// In this case, it's safer to iterate over the input since
			// we are 100% we cannot miss the end()
			for (; srcIter != inRow.end(); ++srcIter, ++dstIter)
			{
				UNIMPLEMENTED;
			}
		}
	};


	template<typename FUNCT>
	class ForEachPixelInRowFunctor<FUNCT, 2, 8>
	{
		const FUNCT &_funct;
	public:
		ForEachPixelInRowFunctor(const FUNCT &funct) : _funct(funct) {}

		void operator()(const PixRowRef<IN_PIXELPACKET> &inRow, PixRowRef<OUT_PIXELPACKET> &outRow) const
		{
 			// 2 Pixel per packet in, 1 pixel per packet out (e.g. 422 -> 444)
			typename PixRowRef<IN_PIXELPACKET>::ConstIterator srcIter = inRow.begin();
			typename PixRowRef<OUT_PIXELPACKET>::Iterator dstIter = outRow.begin();

			// In this case, it's safer to iterate over the input since
			// we are 100% we cannot miss the end()
			for (; srcIter != inRow.end(); ++srcIter, ++dstIter)
			{
				UNIMPLEMENTED;
			}
		}
	};


	template<typename FUNCT>
	class ForEachPixelInRowFunctor<FUNCT, 1, 8>
	{
		const FUNCT &_funct;
	public:
		ForEachPixelInRowFunctor(const FUNCT &funct) : _funct(funct) {}

		void operator()(const PixRowRef<IN_PIXELPACKET> &inRow, PixRowRef<OUT_PIXELPACKET> &outRow) const
		{
 			// 2 Pixel per packet in, 1 pixel per packet out (e.g. 422 -> 444)
			typename PixRowRef<IN_PIXELPACKET>::ConstIterator srcIter = inRow.begin();
			typename PixRowRef<OUT_PIXELPACKET>::Iterator dstIter = outRow.begin();

			// In this case, it's safer to iterate over the input since
			// we are 100% we cannot miss the end()
			for (; srcIter != inRow.end(); ++srcIter, ++dstIter)
			{
				typename PixRowRef<IN_PIXELPACKET>::ConstIterator srcIter0 = srcIter++;
				typename PixRowRef<IN_PIXELPACKET>::ConstIterator srcIter1 = srcIter++;
				typename PixRowRef<IN_PIXELPACKET>::ConstIterator srcIter2 = srcIter++;
				typename PixRowRef<IN_PIXELPACKET>::ConstIterator srcIter3 = srcIter++;
				typename PixRowRef<IN_PIXELPACKET>::ConstIterator srcIter4 = srcIter++;
				typename PixRowRef<IN_PIXELPACKET>::ConstIterator srcIter5 = srcIter++;
				typename PixRowRef<IN_PIXELPACKET>::ConstIterator srcIter6 = srcIter++;
				typename PixRowRef<IN_PIXELPACKET>::ConstIterator srcIter7 = srcIter;

				_funct(*srcIter0, *srcIter1, *srcIter2, *srcIter3, *srcIter4, *srcIter5, *srcIter6, *srcIter7, &*dstIter);
			}
		}
	};



	template<typename FUNCT>
	class ForEachPixelInRowFunctor<FUNCT, 8, 8>
	{
		const FUNCT &_funct;
	public:
		ForEachPixelInRowFunctor(const FUNCT &funct) : _funct(funct) {}

		void operator()(const PixRowRef<IN_PIXELPACKET> &inRow, PixRowRef<OUT_PIXELPACKET> &outRow) const
		{
 			// 2 Pixel per packet in, 1 pixel per packet out (e.g. 422 -> 444)
			typename PixRowRef<IN_PIXELPACKET>::ConstIterator srcIter = inRow.begin();
			typename PixRowRef<OUT_PIXELPACKET>::Iterator dstIter = outRow.begin();

			// In this case, it's safer to iterate over the input since
			// we are 100% we cannot miss the end()
			for (; srcIter != inRow.end(); ++srcIter, ++dstIter)
			{
				_funct(srcIter->pixel0(), &dstIter->pixel0());
				_funct(srcIter->pixel1(), &dstIter->pixel1());
				_funct(srcIter->pixel2(), &dstIter->pixel2());
				_funct(srcIter->pixel3(), &dstIter->pixel3());
				_funct(srcIter->pixel4(), &dstIter->pixel4());
				_funct(srcIter->pixel5(), &dstIter->pixel5());
				_funct(srcIter->pixel6(), &dstIter->pixel6());
				_funct(srcIter->pixel7(), &dstIter->pixel7());
			}
		}
	};


};

//==============================================================================
// CLASS PixMapComposer1In1Out
//==============================================================================
class PixMapComposer1In1Out
{
public:
	template<typename IN_PIXELPACKET, typename IN_ORIENTATION, typename OUT_PIXELPACKET, typename OUT_ORIENTATION, typename FUNCT>
	static void forEach(const PixMap<IN_PIXELPACKET, IN_ORIENTATION> &inPixMap, PixMap<OUT_PIXELPACKET, OUT_ORIENTATION> *outPixMap, const FUNCT &funct)
	{
		PixMapComposer1In1OutImp<IN_PIXELPACKET, IN_ORIENTATION, OUT_PIXELPACKET, OUT_ORIENTATION>::forEach(inPixMap, outPixMap, funct);
	}

};


}

#endif // __ITL_PIXMAPMANIP_H__


