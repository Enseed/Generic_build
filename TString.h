/*******************************************************************************
 Copyright 2010 Enseed inc.
 
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
#ifndef __GENERIC_BASE_TSTRING__
#define __GENERIC_BASE_TSTRING__

#include <string>
#include <Enseed/Generic/Base/Types.h>


static inline std::string StringFromWString(const std::wstring &aWideString)
{
	char *ascii = new char[aWideString.length()+1];
	wcstombs(ascii, aWideString.c_str(), aWideString.length()+1);
	std::string str(ascii);
	delete [] ascii;
	return str;
}

static inline std::wstring WStringFromString(const std::string &aString)
{
	wchar *unicode = new wchar[aString.length()+1];
	mbtowc(unicode, aString.c_str(), aString.length()+1);
	std::wstring str(unicode);
	delete [] unicode;
	return str;
}

#ifdef UNICODE

namespace std { typedef std::wstring tstring; }
#define WStringFromTString(str) (str)
#define StringFromTString(str) StringFromWString(str)

#else

namespace std { typedef std::string tstring; }
#define WStringFromTString(str) WStringFromString(str)
#define StringFromTString(str) str

#endif




#endif // __GENERIC_BASE_PATH__
