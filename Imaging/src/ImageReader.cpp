/*******************************************************************************
 Copyright 2008 Enseed inc.
 
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

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "../ImageReader.h"
#include "../IImageFormatReader.h"
//#include "../Image.h"
#include "../../Time/Time.h"
#include <map> // for multimap
#include <algorithm>

USING_GENERIC_NAMESPACE


//==============================================================================
//	FORWARD DECLARATIONS
//==============================================================================
namespace {

static std::string ExtractExtensionFromPath(const std::string &name)
{
	// find a . 3 or 4 positions from the end
	std::string::size_type dotPos = name.rfind(".");
	if (dotPos != std::string::npos && dotPos >= name.length()-5)
		return name.substr(dotPos+1);

	return name;
}

static int BenchmarkImageLoaders_LoadWithLoader(const char *path, IImageFormatReader *loader)
{
	ITL::Image *img = loader->readFile(path);
	if (!img)	return -1;
	delete img;
	return 0;
}

template<class TIMER>
static IImageFormatReader* BenchmarkImageLoaders(const char *path, int iterations)
{
	printf("\nbenchmarking %s\n", path);
	std::vector<IImageFormatReader*> loaders;
	ImageReader::instance().getReaders(path, &loaders);

	IImageFormatReader *fastest = NULL;
	Time bestTime;

	if (loaders.size() == 0)
	{
		printf("no image loader for %s\n", path);
		return NULL;
	}
//	else if (loaders.size() == 1)
//	{
//		printf("only one loader (%s) available, not benchmarking %s\n", loaders[0]->name(), path);
//		return loaders[0];
//	}

	for (int i = 0; i < loaders.size(); ++i)
	{
		printf("%32s", loaders[i]->name()); fflush(stdout);

		int err = BenchmarkImageLoaders_LoadWithLoader(path, loaders[i]); // first time does not count
		if (err) continue;

		typename TIMER::TimeStamp astamp = TIMER::stamp(); // start timer
		{
			for (int j = 0; j < iterations; ++j)
			{
				Time time = TIMER::elapsed(astamp, TIMER::stamp());
//				if (fastest && time >= bestTime)
//				{
//					printf(" spent more time than best - skipping\n");
//					break;
//				}

				BenchmarkImageLoaders_LoadWithLoader(path, loaders[i]);
			}
		} // stop timer

		Time time = TIMER::getTime(astamp, TIMER::stamp());

		printf(" %f ms\n", time.inSeconds()*1000/iterations);

		if (!fastest || time < bestTime)
		{
			bestTime = time;
			fastest = loaders[i];
		}
	}

	if (fastest)
		printf("Fastest loader is %s at %f ms\n", fastest->name(), bestTime.inSeconds()*1000/iterations);
	else
		printf("no loader worked on this image\n");

	return fastest;
}

template<class T>
int ImageReaderGetImageProcessor(const std::string &format, const std::multimap<std::string, T*> &processors, std::vector<T*> *outImageProcessor)
{
	outImageProcessor->clear();

	std::string formatStr = ::ExtractExtensionFromPath(format);
	std::transform(formatStr.begin(), formatStr.end(), formatStr.begin(), tolower);

	typename std::multimap<std::string, T*>::const_iterator iter = processors.lower_bound(formatStr);
	typename std::multimap<std::string, T*>::const_iterator upperBound = processors.upper_bound(formatStr);
	if (iter == upperBound)	return -1; // NotFoundErr;
	
	for (; iter != upperBound; ++iter)
		outImageProcessor->push_back(iter->second);

	return 0; // no err
}

}


template<class TIMER>
void ImageReader::benchmark(const std::string &file, bool setDefault, IImageFormatReader **outBestImageReader)
{
	IImageFormatReader *best = BenchmarkImageLoaders<TIMER>(file, 20);
	if (outBestImageReader)	*outBestImageReader = best;
	if (setDefault && best)
	{
		std::string ext = ExtractExtensionFromPath(file);
		setDefaultReader(ext, best);
	}
}

int ImageReader::setDefaultReader(const std::string &fileType, const std::string &imageLoaderName)
{
	std::multimap<std::string, IImageFormatReader*>::iterator iter = mLoaders.lower_bound(fileType);
	std::multimap<std::string, IImageFormatReader*>::iterator end = mLoaders.upper_bound(fileType);

	for (; iter != end; ++iter)
	{
		if (std::string(iter->second->name()) == imageLoaderName)
		{
			setDefaultReader(fileType, iter->second);
			return 0;
		}
	}

	printf("Could not find the %s image loader for file type '%s'\n", imageLoaderName.c_str(), fileType.c_str());
	return -1;
}

int ImageReader::setDefaultReader(const std::string &fileType, IImageFormatReader *imageReader)
{
	mDefaultLoader[fileType] = imageReader;
	return 0;
}


//------------------------------------------------------------------------------
//
ImageReader& ImageReader::instance()
{
	static ImageReader sInstance;
	return sInstance;
}


//------------------------------------------------------------------------------
//
void ImageReader::getReaders(const std::string &format, std::vector<IImageFormatReader*> *outImageLoaders)
{
	ImageReaderGetImageProcessor(format, mLoaders, outImageLoaders);
}

//------------------------------------------------------------------------------
//
IImageFormatReader* ImageReader::defaultReader(const std::string &format)
{
	std::string ext = ExtractExtensionFromPath(format);
	std::map<std::string, IImageFormatReader*>::iterator iter = mDefaultLoader.find(ext);
	if (iter != mDefaultLoader.end())
	{
		return iter->second;
	}

	std::vector<IImageFormatReader*> loaders;
	getReaders(format, &loaders);
	return loaders.empty() ? NULL : *loaders.begin();
}


//------------------------------------------------------------------------------
//
bool ImageReader::registerFormatReader(IImageFormatReader *imageLoader)
{
	std::vector<std::string> formats;
	imageLoader->supportedFormats(&formats);
	std::string name = imageLoader->name();
	for (uint i = 0; i < formats.size(); ++i)
	{
		std::transform(formats[i].begin(), formats[i].end(), formats[i].begin(), tolower);
		mLoaders.insert(std::pair<std::string, IImageFormatReader*>(formats[i], imageLoader));
		TRACEF(" - %s files supported by %s\n", formats[i].c_str(), name.c_str());
	}
	return true;
}


//------------------------------------------------------------------------------
//
ITL::Image* ImageReader::read(const std::string &fileName)
{
	IImageFormatReader *reader = defaultReader(ExtractExtensionFromPath(fileName));
	if (!reader)	return NULL;
	return reader->readFile(fileName.c_str());
}

//------------------------------------------------------------------------------
//
ImageReader::ImageReader()
:
	mDefaultLoader(),
	mLoaders()
{}

//------------------------------------------------------------------------------
//
ImageReader::~ImageReader()
{}



