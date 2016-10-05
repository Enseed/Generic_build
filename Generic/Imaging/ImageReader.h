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
#ifndef __GENERIC_IMAGING_IMAGEREADER__
#define __GENERIC_IMAGING_IMAGEREADER__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include <vector>
#include <string>
#include <map>
#include <ITL/Image/Image.h>

#ifdef WIN32
#ifdef GENERIC_EXPORTS
#define GENERIC_DLL_EXPORT __declspec(dllexport)
#else
#define GENERIC_DLL_EXPORT __declspec(dllimport)
#endif
#else // !defined(WIN32)
#define GENERIC_DLL_EXPORT
#endif // ] WIN32


//==============================================================================
//	FORWARD DECLARATIONS
//==============================================================================
#ifdef GENERIC_NAMESPACE
namespace GENERIC_NAMESPACE {
#endif
class IImageFormatReader;

//==============================================================================
//	INTERFACE ImageReader
//==============================================================================
class ImageReader
{
public:
	GENERIC_DLL_EXPORT static ImageReader& instance();
	~ImageReader();

public:
    GENERIC_DLL_EXPORT IImageFormatReader* defaultReader(const std::string &format);
    GENERIC_DLL_EXPORT void getReaders(const std::string &format, std::vector<IImageFormatReader*> *outImageLoaders);
	GENERIC_DLL_EXPORT bool registerFormatReader(IImageFormatReader *imageReader);
	GENERIC_DLL_EXPORT ITL::Image* read(const std::string &fileName);

	GENERIC_DLL_EXPORT int setDefaultReader(const std::string &fileType, const std::string &imageReaderName);
	GENERIC_DLL_EXPORT int setDefaultReader(const std::string &fileType, IImageFormatReader *imageReader);

private:
	template<class TIMER>
	void benchmark(const std::string &file, bool setDefault, IImageFormatReader **outBestImageLoader);

	ImageReader();

	std::map<std::string, IImageFormatReader*>				mDefaultLoader;
	std::multimap<std::string, IImageFormatReader*>			mLoaders;
};

#ifdef GENERIC_NAMESPACE
}
#endif

#endif // __GENERIC_IMAGING_IMAGEREADER__
