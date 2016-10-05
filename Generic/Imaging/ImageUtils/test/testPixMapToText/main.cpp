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
#include "Generic/Imaging/ImageUtils/PixMapToText.h"
#include "Wrapper/QuickTime/QTImageWrapper.h"
#include "ITL/PixMap/PixMap.h"
#include "ITL/PixMap/PixMapManip.h"

#ifdef GENERIC_LAYER_NAMESPACE
using namespace GENERIC_LAYER_NAMESPACE;
#endif // WRAPPER_LAYER_NAMESPACE

#ifdef WRAPPER_LAYER_NAMESPACE
using namespace WRAPPER_LAYER_NAMESPACE;
#endif // WRAPPER_LAYER_NAMESPACE

int main(int argc, char **argv)
{
	const char *file = "test.png";
	printf("opening %s\n", file);
	QTImageWrapper import(file);
	if (!import)	
		DIEF("failed to open %s\n", file);

	int width, height;
	import.getNativeSize(&width, &height);
	printf("file opened: %d x %d\n", width, height);
	
	ITL::PixMap< Lum8Pixel > pm(width, height);
	printf("Instantiated a grayscale pixmap\n");
	memset(pm.begin()->plane0()->storage().ptr(), 0, width*height);
	printf("Zeroed buffer\n");
	
	import.draw(pm.baseAddr(), QTImageWrapper::FORMAT_L8);
	printf("Image drawn into the pixmap\n");

	ITL::PixMap< Lum8Pixel > screen(120, 40);
	ITL::PixMapManip::resample(pm, &screen);
	std::string str = PixMapToText::toString(screen);
	printf("%s\n", str.c_str());
	
/*	int maxW = 0;
	int maxH = 0;
	
	for (int i = 33; i < 128; ++i)
	{
		face[face.glyphIndex(i)];
		int width = face.glyphWidth();
		if (width > maxW)	maxW = width;
		int height = face.glyphHeight();
		if (height > maxH)	maxH = height;
	}
	
	std::map<double, char> m;
	double maxScore = 0;
	for (int i = 32; i < 127; ++i)
	{
		face[face.glyphIndex(i)].glyphRender();
		FTFace::PixMap *pm = face.glyphPixMap();
		unsigned char *row = pm->baseAddr();
		int width = pm->width();
		int height = pm->height();
		int rb = pm->rowLength();
		
		double total = 0;
		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x)
				total += row[x];
			row += rb;
		}

		double score = total/(maxW*maxH);
		m[score] = i;
		if (score > maxScore)
			maxScore = score;
		
		GNX::PixMap< GNX::LPixel<uint8> > screen(80, 24, GNX::Rational(1, 1), 0);
		if (width*height != 0)
		{
			screen.resample(*pm);
			std::string str = GNX::PixMapToText::toString(screen);
			printf("%s\n", str.c_str());
		}
		else
		{
			std::string str = GNX::PixMapToText::toString(*pm);
			printf("%s\n", str.c_str());
		}

	}
	
	std::map<double, char>::iterator iter;
	printf("{");
	
	for (iter = m.begin(); iter != m.end(); ++iter)
		printf("'%c', ", iter->second);
	printf("};");
	printf("\n");
*/
	return 0;
}
