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
#ifndef __ITL_PIXMAPCOMPOSER2IN1OUT_H__
#define __ITL_PIXMAPCOMPOSER2IN1OUT_H__

//==============================================================================
// FILE PixMapComposer2In1Out.h
//==============================================================================
// Implements the Composer for 1 pixel in, 1 pixel out.  This can be used for
// example to copy, convert, apply pixel transformation (E.g. gamma, brightness)
//
// USAGE:
//		class BlendRGB {
//			float _weight;
//		public:
//			BlendRGB(float v) : _weight(v) {}
//			void operator()(const RGB24Pixel &src0, const RGB24Pixel &src1, RGB24Pixel *dst) {	
//				dst->setRGB(
//					src0.red() * _weight + src1.red() * (1 - _weight),
//					src0.green() * _weight + src1.green() * (1 - _weight),
//					src0.blue() * _weight + src1.blue() * (1 - _weight) );
//			}
//		};
// 
//		PixMap<RGB24Pixel> original0(512, 512);
//		PixMap<RGB24Pixel> original1(512, 512);
//		PixMap<RGB24Pixel> blent(512, 512);
//		PixMapComposer2In1Out::forEach(original0.ref(), original1.ref(), blent.ref(), BlendRGB(0.5));
//------------------------------------------------------------------------------

//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================
#include "PixMapRef.declare.h"
#include "PixRowRef.h"

namespace ITL {

//==============================================================================
// CLASS PixMapComposer2In1OutImp
//==============================================================================
template<typename IN_PIXELPACKET, typename OUT_PIXELPACKET>
class PixMapComposer2In1OutImp
{
public:
	template<typename FUNCT>
	static void forEach(const PixMapRef<IN_PIXELPACKET> &inPixMap0, const PixMapRef<IN_PIXELPACKET> &inPixMap1, const PixMapRef<OUT_PIXELPACKET> &outPixMap, const FUNCT &funct)
	{
		forEachRow(inPixMap0, inPixMap1, outPixMap, ForEachPixelInRowFunctor<FUNCT>(funct));
	}

	template<typename FUNCT>
	static void forEachRow(const PixMapRef<IN_PIXELPACKET> &inPixMap0, const PixMapRef<IN_PIXELPACKET> &inPixMap1, const PixMapRef<OUT_PIXELPACKET> &outPixMap, const FUNCT &funct)
	{
		// make sure we iterate in the same direction. If both are upside down, we might want
		// to specialize this template later...
		typename PixMapRef<IN_PIXELPACKET>::ConstTopToBottomIterator srcIter0 = inPixMap0.beginFromTop();
		typename PixMapRef<IN_PIXELPACKET>::ConstTopToBottomIterator srcIter1 = inPixMap1.beginFromTop();
		typename PixMapRef<OUT_PIXELPACKET>::TopToBottomIterator dstIter = outPixMap.beginFromTop();

		for (; srcIter0 != inPixMap0.end(); ++srcIter0, ++srcIter1, ++dstIter)
			funct(*srcIter0, *srcIter1, *dstIter);
	}

private:
	template<typename FUNCT>
	class ForEachPixelInRowFunctor
	{
	public:
		ForEachPixelInRowFunctor(const FUNCT &funct) : _funct(funct) {}

		void operator()(const PixRowRef<IN_PIXELPACKET> &inRow0, const PixRowRef<IN_PIXELPACKET> &inRow1, PixRowRef<OUT_PIXELPACKET> outRow) const
		{
			typename PixRowRef<IN_PIXELPACKET>::ConstIterator srcIter0 = inRow0.begin();
			typename PixRowRef<IN_PIXELPACKET>::ConstIterator srcIter1 = inRow1.begin();
			typename PixRowRef<OUT_PIXELPACKET>::Iterator dstIter = outRow.begin();

			for (; srcIter0 != inRow0.end(); ++srcIter0, ++srcIter1, ++dstIter)
				_funct(*srcIter0, *srcIter1, &*dstIter);
		}
	private:
		FUNCT _funct;
	};
};

//==============================================================================
// CLASS PixMapComposer2In1Out
//==============================================================================
class PixMapComposer2In1Out
{
public:
	template<typename IN_PIXELPACKET, typename OUT_PIXELPACKET, typename FUNCT>
	static void forEach(const PixMapRef<IN_PIXELPACKET> &inPixMap0, const PixMapRef<IN_PIXELPACKET> &inPixMap1, PixMapRef<OUT_PIXELPACKET> outPixMap, const FUNCT &funct)
	{
		PixMapComposer2In1OutImp<IN_PIXELPACKET, OUT_PIXELPACKET>::forEach(inPixMap0, inPixMap1, outPixMap, funct);
	}

};


}

#endif // __ITL_PIXMAPMANIP_H__


