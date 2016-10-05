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
#ifndef __ITL_BITIO_H__
#define __ITL_BITIO_H__

//==============================================================================
//	FILE BitIO.h
//==============================================================================
// Quick and dirty implementation for accessing bits. This is used with packed
// storage (e.g. 16 bit rgb packed as 5:6:5 bits).
//
// USAGE:
//     // read 7 bits at offset 3 from a short and return the result as a char
//     BitIO::readBits<short, char, 3, 7>(ptr);
//   
//     // write 7 bits from this char at offset 3 of this short
//     BitIO::writeBits<short, char, 3, 7>(ptr, c);
//------------------------------------------------------------------------------

//==============================================================================
//	CLASS BitReader
//==============================================================================
template<typename STORAGE_TYPE, typename COMPONENT_TYPE, int OFFSET, int SIZE>
class BitReader
{
public:
	static COMPONENT_TYPE read(const STORAGE_TYPE *storage)
	{ return ((*storage) >> OFFSET) & (STORAGE_TYPE(-1) >> (8*sizeof(STORAGE_TYPE)-SIZE)); }
};

//------------------------------------------------------------------------------
// Special case
template<typename STORAGE_TYPE, typename COMPONENT_TYPE, int OFFSET>
class BitReader<STORAGE_TYPE, COMPONENT_TYPE, OFFSET, 0>
{
public:
	static COMPONENT_TYPE read(const STORAGE_TYPE *storage) { return 0; }
};

//==============================================================================
//	CLASS BitWriter
//==============================================================================
template<typename STORAGE_TYPE, typename COMPONENT_TYPE, int OFFSET, int SIZE>
class BitWriter
{
public:
	static void write(STORAGE_TYPE *storage, const COMPONENT_TYPE &val)
	{
		// FIXME, there's got to be a faster way to do this...
		STORAGE_TYPE left = BitReader<STORAGE_TYPE, STORAGE_TYPE, OFFSET+SIZE, 8*sizeof(STORAGE_TYPE)-(OFFSET+SIZE)>::read(storage);
		STORAGE_TYPE right = BitReader<STORAGE_TYPE, STORAGE_TYPE, 0, OFFSET>::read(storage);
		*storage = (left << (OFFSET + SIZE)) | (val << OFFSET) | right;
	}
};

//==============================================================================
//	CLASS BitIO
//==============================================================================
class BitIO
{
public:
	//--------------------------------------------------------------------------
	//
	template<typename STORAGE_TYPE, typename COMPONENT_TYPE, int OFFSET, int SIZE>
	static void writeBits(STORAGE_TYPE *storage, const COMPONENT_TYPE &val)
	{ BitWriter<STORAGE_TYPE, COMPONENT_TYPE, OFFSET, SIZE>::write(storage, val); }

	//--------------------------------------------------------------------------
	//
	template<typename STORAGE_TYPE, typename COMPONENT_TYPE, int OFFSET, int SIZE>
	static COMPONENT_TYPE readBits(const STORAGE_TYPE *storage)
	{ return BitReader<STORAGE_TYPE, COMPONENT_TYPE, OFFSET, SIZE>::read(storage); }
};


#endif // __ITL_BITIO_H__
