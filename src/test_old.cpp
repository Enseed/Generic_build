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
#include <cstdlib>
#include <cstdio>

#include "../RGB/RGBPixel.h"
#include "../XYZ/XYZPixel.h"
#include "../YCbCr/YCbCr422Pixel.h"
#include "../PixelConvert/PixelConverter.h"
#include "../PixMap/PixMap.h"
#include "test.h"
//#include "PixelAdaptor.h"

#include <iostream>
using namespace std;

#define TESTALL 1

template<int NB, class PIXELPACKET, int ISLAST=PixelTest<NB, PIXELPACKET>::END>
class Test
{
public:
	static TestResult perform(const char *name)
	{
		printf(" - Performing test #%d (%s)\n", (int)NB, PixelTest<NB, PIXELPACKET>::name());
		TestResult result = PixelTest<NB, PIXELPACKET>()(name);
		switch(result)
		{
		case(PASSED): printf("PASSED\n"); break;
		case(FAILED): printf("FAILED\n"); break;
		case(SKIPPED):printf("SKIPPED\n"); break;
		}

		if (result == PASSED)
		{
			result = Test<NB+1, PIXELPACKET>::perform(name);
		}
		return result;
	}
};

template<int NB, class PIXELPACKET>
class Test<NB, PIXELPACKET, true>
{
public:
	static TestResult perform(const char *name)
	{
		printf(" - All tests have been performed\n");
		return PASSED;
	}
};

class PrintYUV
{
public:
	template<class YUVPIXEL>
	void operator()(const YUVPIXEL &pel)
	{
		printf(".");
	}
};

template<class PIXELPACKET>
bool TestPixel(const char *name)
{
	printf("Testing pixel packet type: %s\n", name);

	TestResult result = Test<0, PIXELPACKET>::perform(name);
	return result == PASSED;
}

class PrintAsRGBf
{
public:
	template<class PIXELPACKET>
	void operator()(const PIXELPACKET &pixel)
	{
		PixelAdaptor<RGBf32Pixel, PIXELPACKET> rgb32f;
		printf("%f, %f, %f\n", rgb32f.red(), rgb32f.green(), rgb32f.blue());
	};
};

int main(int arg, const char *argv[])
{
#define TESTPIXEL(_PIXELPACKET)\
	{\
		bool passed = TestPixel<_PIXELPACKET>(#_PIXELPACKET);\
		if (!passed)\
		{\
			printf("### Test failed with pixel type %s\n", #_PIXELPACKET);\
			return 0;\
		}\
		printf("\n\n");\
	}

	PixMap<RGB24Pixel> pm(10, 10);
	PixMapRef<RGB24Pixel> pmr = pm.ref();
	RGB24Pixel* baseAddr = &pmr[0][0];
	baseAddr;

	PixMap<RGB24PlanarPixel> pm2(10, 10);
	PixMapRef<RGB24PlanarPixel> pmr2 = pm2.ref();
	unsigned char* baseAddr2 = pmr2[0][0].plane0Ptr();
	baseAddr2;

	TESTPIXEL(RGB24Pixel);

//	PixMap<YCbYCr32Pixel> pm422(2, 2);
//	pm422.ref().forEachPixel(PrintYUV());
//	pm422.ref().convert<RGB24Pixel>()->ref().forEachPixel(PrintRGB<RGB24Pixel>());
//	pm.ref().convert<YCbCr24Pixel>()->ref().forEachPixel(PrintRGB<YCbCr24Pixel>());

	{
		PixMap<RGB24Pixel> pm(2, 2);
		pm.ref().forEachPixel(ClearPixel<RGB24Pixel>());
		pm.ref().forEachPixel(PrintRGB<RGB24Pixel>());
		printf("\n");
		pm.ref().convert<YCbCr24Pixel>()->ref().forEachPixel(PrintRGB<YCbCr24Pixel>());
		pm.ref().convert<YCbCr24Pixel>()->ref().convert<RGB24Pixel>()->ref().forEachPixel(PrintRGB<RGB24Pixel>());
	}

	Lum8Pixel lum8;
	

//	PixMap<RGB24Pixel> *pm24 = pm422.ref().convert<RGB24Pixel>();

	RGB24Pixel pixel(10, 20, 30);
	PrintAsRGBf()(pixel);
	
	
#if TESTALL && 0
	TESTPIXEL(RGB48Pixel);
	TESTPIXEL(RGBf32Pixel);
	TESTPIXEL(RGBf64Pixel);

	TESTPIXEL(BGR24Pixel);
	TESTPIXEL(BGR48Pixel);
	TESTPIXEL(BGRf32Pixel);
	TESTPIXEL(BGRf64Pixel);

	TESTPIXEL(RGBA32Pixel);
	TESTPIXEL(RGBA64Pixel);
	TESTPIXEL(RGBAf32Pixel);
	TESTPIXEL(RGBAf64Pixel);

	TESTPIXEL(BGRA32Pixel);
	TESTPIXEL(BGRA64Pixel);
	TESTPIXEL(BGRAf32Pixel);
	TESTPIXEL(BGRAf64Pixel);

	TESTPIXEL(ARGB32Pixel);
	TESTPIXEL(ARGB64Pixel);
	TESTPIXEL(ARGBf32Pixel);
	TESTPIXEL(ARGBf64Pixel);

	TESTPIXEL(ABGR32Pixel);
	TESTPIXEL(ABGR64Pixel);
	TESTPIXEL(ABGRf32Pixel);
	TESTPIXEL(ABGRf64Pixel);

	TESTPIXEL(RGB24PlanarPixel);
	TESTPIXEL(RGB48PlanarPixel);
	TESTPIXEL(RGBf32PlanarPixel);
	TESTPIXEL(RGBf64PlanarPixel);

	TESTPIXEL(RGBA32PlanarPixel);
	TESTPIXEL(RGBA64PlanarPixel);
	TESTPIXEL(RGBAf32PlanarPixel);
	TESTPIXEL(RGBAf64PlanarPixel);

	TESTPIXEL(RGB565Pixel);
	TESTPIXEL(RGB5551Pixel);
	TESTPIXEL(RGB1555Pixel);
	TESTPIXEL(RGBA5551Pixel);

	TESTPIXEL(BGR565Pixel);
	TESTPIXEL(BGR5551Pixel);
	TESTPIXEL(BGR1555Pixel);
	TESTPIXEL(BGRA5551Pixel);

	TESTPIXEL(ARGB1555Pixel);
	TESTPIXEL(ABGR1555Pixel);

	TESTPIXEL(RGB332Pixel);
	TESTPIXEL(BGR332Pixel);

// YUV

	TESTPIXEL(YCbCr24Pixel);
	TESTPIXEL(CrCbY24Pixel);

	TESTPIXEL(YCbCr48Pixel);
	TESTPIXEL(CrCbY48Pixel);

	TESTPIXEL(YCbCrf32Pixel);
	TESTPIXEL(CrCbYf32Pixel);

	TESTPIXEL(YCbCrf64Pixel);
	TESTPIXEL(YCbCrf64Pixel);

	TESTPIXEL(YCbCr24PlanarPixel);
	TESTPIXEL(YCbCr48PlanarPixel);
	TESTPIXEL(YCbCrf32PlanarPixel);
	TESTPIXEL(YCbCrf64PlanarPixel);
#endif // TESTALL
	return 0;
}
