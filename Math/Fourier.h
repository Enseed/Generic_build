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
#ifndef __GENERIC_MATH_FOURIER__
#define __GENERIC_MATH_FOURIER__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include <complex>

namespace seed {

//==============================================================================
//	CLASS Fourier
//==============================================================================
class Fourier
{
public:
	enum
	{
		FORWARD = -1,
		REVERSE = 1
	};

public: // normalized, size is known at compile time
	template<class T, int WIDTH, int HEIGHT>
	static void normalizedForwardTransform2D(std::complex<T> *data);

	template<class T, int WIDTH, int HEIGHT>
	static void normalizedReverseTransform2D(std::complex<T> *data);

	template<class T, int SIZE>
	static void normalizedForwardTransform(std::complex<T> *data);

	template<class T, int SIZE>
	static void normalizedReverseTransform(std::complex<T> *data);

	template<class T, int TYPE, int SIZE, int INCREMENT>
	static void normalizedFastTransform(std::complex<T> *data);

public: // not-normalized, size is known at compile time
	template<class T, int WIDTH, int HEIGHT>
	static void forwardTransform2D(std::complex<T> *data);

	template<class T, int WIDTH, int HEIGHT>
	static void reverseTransform2D(std::complex<T> *data);

	template<class T, int SIZE>
	static void forwardTransform(std::complex<T> *data);

	template<class T, int SIZE>
	static void reverseTransform(std::complex<T> *data);

	template<class T, int TYPE, int SIZE, int INCREMENT>
	static void fastTransform(std::complex<T> *data);

public: // normalized, size is known at run time
	template<class T>
	static void normalizedForwardTransform2D(std::complex<T> *data, int width, int height);

	template<class T>
	static void normalizedReverseTransform2D(std::complex<T> *data, int width, int height);

	template<class T>
	static void normalizedForwardTransform(std::complex<T> *data, unsigned int size);

	template<class T>
	static void normalizedReverseTransform(std::complex<T> *data, unsigned int size);

	template<class T, int TYPE>
	static void normalizedFastTransform(std::complex<T> *data, unsigned int size, int increment);

public: // not-normalized, size is known at run time
	template<class T>
	static void forwardTransform2D(std::complex<T> *data, int width, int height);

	template<class T>
	static void reverseTransform2D(std::complex<T> *data, int width, int height);

	template<class T>
	static void forwardTransform(std::complex<T> *data, unsigned int size);

	template<class T>
	static void reverseTransform(std::complex<T> *data, unsigned int size);

	template<class T, int TYPE>
	static void fastTransform(std::complex<T> *data, unsigned int size, int increment);
	
private:
	//==========================================================================
	// CLASS Fourier::Internal
	//==========================================================================
	template<class T, int SIZE, int LEVEL, int INCREMENT>
	class Internal
	{
	public:
		static void transform(std::complex<T> *data);
	};

	template<class T, int SIZE, int INCREMENT>
	class Internal<T, SIZE, 8, INCREMENT>
	{
	public:
		static void transform(std::complex<T> *data);
	};

	template<class T, int SIZE, int INCREMENT>
	class Internal4
	{
	public:
		static void transform(std::complex<T> *data);
	};

	template<class T, int SIZE, int INCREMENT>
	class Internal<T, SIZE, 4, INCREMENT>
	{
	public:
		static void transform(std::complex<T> *data);
	};

	template<class T, int SIZE, int INCREMENT>
	class Internal2
	{
	public:
		static void transform(std::complex<T> *data);
	};

	template<class T, int SIZE, int INCREMENT>
	class Internal<T, SIZE, 2, INCREMENT>
	{
	public:
		static void transform(std::complex<T> *data);
	};

	template<class T, int SIZE, int INCREMENT>
	class Internal<T, SIZE, 1, INCREMENT>
	{
	public:
		static void transform(std::complex<T> *data);
	};

public:
	static bool isPow2(unsigned int val);
	static int log2(unsigned int value);

private:
	Fourier();

};

} // namespace seed


//==============================================================================
//	INLINED CODE
//==============================================================================
#include "src/Fourier.inline.h"


#endif // __GENERIC_MATH_FOURIER__
