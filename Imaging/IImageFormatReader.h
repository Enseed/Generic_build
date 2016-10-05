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
#ifndef __IMAGING_IIMAGEFORMATREADER__
#define __IMAGING_IIMAGEFORMATREADER__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
namespace ITL { class Image; }

#ifdef GENERIC_NAMESPACE
namespace GENERIC_NAMESPACE {
#endif

//==============================================================================
//	INTERFACE IImageFormatReader
//==============================================================================
class IImageFormatReader
{
public:
	virtual ~IImageFormatReader(){}
	virtual ITL::Image* readFile(const char *file) const = 0;
	virtual void supportedFormats(std::vector<std::string> *outFormats) const = 0;
	virtual const char *name() const = 0;
};

template<class PARSER>
class TImageFormatReader: public IImageFormatReader
{
public:
	virtual ITL::Image* readFile(const char *file) const { return PARSER::readFile(file); }
	virtual void supportedFormats(std::vector<std::string> *outFormat) const { return PARSER::supportedFormats(outFormat); }
	virtual const char *name() const { return PARSER::name(); }
};

#ifdef GENERIC_NAMESPACE
}
#endif

#endif // __IMAGING_IIMAGEFORMATREADER__
