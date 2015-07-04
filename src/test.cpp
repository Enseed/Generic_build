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

#include "Image.h"
#include "../../Wrapper/QuickTime/QTImageReader2.h"
#include "../../Wrapper/QuickTime/QTImageWrapper2.h"

using namespace std;
using namespace ITL;

class PixelToPPMWrite
{
public:
	PixelToPPMWrite(FILE *f) : _f(f) {}
	void operator()(const RGB24Pixel &pixel) const
	{
		fwrite(&pixel, 3, 1, _f);
	}
private:
	FILE *_f;
};

void SaveAsPPM(Image *img, const char *path)
{
	FILE *f = fopen(path, "wb");
	fprintf(f, "P6\n%d %d 255\n", img->width(), img->height());
	img->forEachPixel<RGB24Pixel, PixelToPPMWrite>(PixelToPPMWrite(f));
	fclose(f);
}

int main(int arg, const char *argv[])
{
	Image* image = QTImageReader::readFile("/Users/petit/Desktop/test/img.jpg");
	Image* resamp = image->resample(512, 512);
	delete image;
	
	
	SaveAsPPM(resamp, "foo.ppm");
	system("open foo.ppm");
	delete resamp;
	
	return 0;
}
