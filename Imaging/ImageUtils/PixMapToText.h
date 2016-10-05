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
#ifndef __GENERIC_IMAGING_IMAGEUTILS__PIXMAPTOTEXT__
#define __GENERIC_IMAGING_IMAGEUTILS__PIXMAPTOTEXT__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "../../Math/Rational.h"
#include <ITL/PixMap/PixMap.h>
#include <vector>
#include <string>

namespace seed {

namespace {

const std::vector<char>& FullANSIDensityTable()
{
	static const char sCharTable[] = {' ', '`', '\'', '.', '~', '^', '-', '"', ',', '_', ':', '\\', '/', '!', ';', ')', '(', '*', '7', '>', '<', '=', '?', '+', ']', 'i', '1', '|', '{', 'v', '}', 'c', 't', 'r', 'l', 'I', 'j', '3', 'z', 'J', 'C', '5', 'V', 'u', 'Y', 'o', '2', '6', '9', 'x', '&', '0', 'f', 'n', 'L', '4', '$', 's', 'w', 'O', 'y', 'a', 'e', 'S', 'T', 'X', 'U', 'A', 'F', '8', 'k', 'h', 'D', 'P', 'R', '%', 'G', 'Z', 'K', 'b', 'd', 'Q', '@', 'g', 'B', 'H', 'W', 'p', 'q', '#', 'm', 'E', 'N', 'M'};
	const int sCharTableSize = sizeof(sCharTable)/sizeof(sCharTable[0]);
	static std::vector<char> sTable(sCharTable, sCharTable+sCharTableSize);
	return sTable;
}

const std::vector<char>& PoundTable()
{
	static const char sCharTable[] = {' ', '#'};
	const int sCharTableSize = sizeof(sCharTable)/sizeof(sCharTable[0]);
	static std::vector<char> sTable(sCharTable, sCharTable+sCharTableSize);
	return sTable;
}


const std::vector<char>& SmallTable()
{
	static const char sCharTable[] = {' ', '.', '~', ':', '*', 'o', '0', 'O', 'X', '@', '#'};
	const int sCharTableSize = sizeof(sCharTable)/sizeof(sCharTable[0]);
	static std::vector<char> sTable(sCharTable, sCharTable+sCharTableSize);
	return sTable;
}
	
}

//==============================================================================
//	CLASS PixMapToText
//==============================================================================
class PixMapToText
{
private:
	PixMapToText();

public:

	template<class PIX_T>
	static std::string toString(const ITL::PixMap< PIX_T > &pixMap)
	{
		return toString(pixMap, SmallTable());
	}
	
	template<class PIX_T>
	static std::string toString(const ITL::PixMap< PIX_T > &pixMap, const std::vector<char> &table)
	{
		std::string str;
		typedef ITL::PixMap< PIX_T > PM_T;
		for (typename PM_T::ConstTopToBottomIterator r = pixMap.beginFromTop(); r != pixMap.endFromTop(); ++r)
		{
			for (typename PM_T::ConstRow::ConstIterator p = r->begin(); p != r->end(); ++p)
			{
				int l = (p->luminance() * table.size() + table.size()/2) / 256;
				str += table[l];
			}
			str += '\n';
		}

		return str;
	}
};

} // namespace seed

#endif // __GENERIC_IMAGING_IMAGEUTILS_RESAMPLE__
