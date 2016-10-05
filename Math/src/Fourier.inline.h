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
#ifndef __GENERIC_MATH_FOURIER_INLINE__
#define __GENERIC_MATH_FOURIER_INLINE__

//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================
#include "../Fourier.h"
#include <complex>
#include <cmath>

//==============================================================================
// MACRO DEFINITIONS
//==============================================================================

#ifndef M_PI
#define M_PI			3.14159265358979323846
#endif // M_PI

#ifndef M_SQRT1_2
#define M_SQRT1_2		0.70710678118654752440
#endif // M_SQRT1_2

namespace seed {

//==============================================================================
// CLASS Fourier
//==============================================================================

//------------------------------------------------------------------------------
//
template<class T, int WIDTH, int HEIGHT>
void Fourier::normalizedForwardTransform2D(std::complex<T> *data)
{
	int rowLength = WIDTH;
	
	for (int i = 0; i < HEIGHT; ++i)
		normalizedFastTransform<T, FORWARD>(&data[i*rowLength], WIDTH, 1);

	for (int i = 0; i < WIDTH; ++i)
		normalizedFastTransform<T, FORWARD>(&data[i], HEIGHT, rowLength);
}

//------------------------------------------------------------------------------
//
template<class T, int WIDTH, int HEIGHT>
void Fourier::forwardTransform2D(std::complex<T> *data)
{
	int rowLength = WIDTH;
	
	for (int i = 0; i < HEIGHT; ++i)
		fastTransform<T, FORWARD>(&data[i*rowLength], WIDTH, 1);

	for (int i = 0; i < WIDTH; ++i)
		fastTransform<T, FORWARD>(&data[i], HEIGHT, rowLength);
}

//------------------------------------------------------------------------------
//
template<class T>
void Fourier::normalizedForwardTransform2D(std::complex<T> *data, int width, int height)
{
	int rowLength = width;
	
	for (int i = 0; i < height; ++i)
		normalizedFastTransform<T, FORWARD>(&data[i*rowLength], width, 1);

	for (int i = 0; i < width; ++i)
		normalizedFastTransform<T, FORWARD>(&data[i], height, rowLength);
}

//------------------------------------------------------------------------------
//
template<class T>
void Fourier::forwardTransform2D(std::complex<T> *data, int width, int height)
{
	int rowLength = width;
	
	for (int i = 0; i < height; ++i)
		fastTransform<T, FORWARD>(&data[i*rowLength], width, 1);

	for (int i = 0; i < width; ++i)
		fastTransform<T, FORWARD>(&data[i], height, rowLength);
}

//------------------------------------------------------------------------------
//
template<class T, int WIDTH, int HEIGHT>
void Fourier::normalizedReverseTransform2D(std::complex<T> *data)
{
	int rowLength = WIDTH;
	
	for (int i = 0; i < WIDTH; ++i)
		normalizedFastTransform<T, REVERSE>(&data[i], HEIGHT, rowLength);

	for (int i = 0; i < HEIGHT; ++i)
		normalizedFastTransform<T, REVERSE>(&data[i*rowLength], WIDTH, 1);
}

//------------------------------------------------------------------------------
//
template<class T, int WIDTH, int HEIGHT>
void Fourier::reverseTransform2D(std::complex<T> *data)
{
	int rowLength = WIDTH;
	
	for (int i = 0; i < WIDTH; ++i)
		fastTransform<T, REVERSE>(&data[i], HEIGHT, rowLength);

	for (int i = 0; i < HEIGHT; ++i)
		fastTransform<T, REVERSE>(&data[i*rowLength], WIDTH, 1);
}

//------------------------------------------------------------------------------
//
template<class T>
void Fourier::reverseTransform2D(std::complex<T> *data, int width, int height)
{
	int rowLength = width;
	
	for (int i = 0; i < width; ++i)
		fastTransform<T, REVERSE>(&data[i], height, rowLength);

	for (int i = 0; i < height; ++i)
		fastTransform<T, REVERSE>(&data[i*rowLength], width, 1);
}

//------------------------------------------------------------------------------
//
template<class T>
void Fourier::normalizedReverseTransform2D(std::complex<T> *data, int width, int height)
{
	int rowLength = width;
	
	for (int i = 0; i < width; ++i)
		normalizedFastTransform<T, REVERSE>(&data[i], height, rowLength);

	for (int i = 0; i < height; ++i)
		normalizedFastTransform<T, REVERSE>(&data[i*rowLength], width, 1);
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
void Fourier::forwardTransform(std::complex<T> *data)
{
	fastTransform<T, FORWARD, SIZE, 1>(data);
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
void Fourier::normalizedForwardTransform(std::complex<T> *data)
{
	normalizedFastTransform<T, FORWARD, SIZE, 1>(data);
}

//------------------------------------------------------------------------------
//
template<class T>
void Fourier::forwardTransform(std::complex<T> *data, unsigned int size)
{
	fastTransform<T, FORWARD>(data, size, 1);
}

//------------------------------------------------------------------------------
//
template<class T>
void Fourier::normalizedForwardTransform(std::complex<T> *data, unsigned int size)
{
	normalizedFastTransform<T, FORWARD>(data, size, 1);
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
void Fourier::reverseTransform(std::complex<T> *data)
{
	fastTransform<T, REVERSE, SIZE, 1>(data);
}


//------------------------------------------------------------------------------
//
template<class T, int SIZE>
void Fourier::normalizedReverseTransform(std::complex<T> *data)
{
	normalizedFastTransform<T, REVERSE, SIZE, 1>(data);
}

//------------------------------------------------------------------------------
//
template<class T>
void Fourier::reverseTransform(std::complex<T> *data, unsigned int size)
{
	fastTransform<T, REVERSE>(data, size, 1);
}

//------------------------------------------------------------------------------
//
template<class T>
void Fourier::normalizedReverseTransform(std::complex<T> *data, unsigned int size)
{
	normalizedFastTransform<T, REVERSE>(data, size, 1);
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE, int LEVEL, int INCREMENT>
void Fourier::Internal<T, SIZE, LEVEL, INCREMENT>::transform(std::complex<T> *data)
{
	static const unsigned int mask = SIZE-1;
	static T sin_t[SIZE];
	static T cos_t[SIZE];
	static const T twoPi = 2*T(M_PI);
	static const T twoPiOverN = twoPi / static_cast<T>(SIZE);
	static bool inited = false;
	if (!inited)
	{
		for (int i = 0; i < SIZE; ++i)
		{
			cos_t[i] = cos(i*twoPiOverN);
			sin_t[i] = sin(i*twoPiOverN);
		}
		inited = true;
	}

	const int ie = SIZE / LEVEL;
	int ia = 0;

	for (unsigned int j = 0; j < LEVEL/2; j++)
	{
		T cosA = cos_t[ia & mask];
		T sinA = sin_t[ia & mask];
		ia += ie;
		
		for (unsigned int i = j*INCREMENT; i < SIZE*INCREMENT; i += LEVEL*INCREMENT)
		{
			int i2 = i + LEVEL*INCREMENT/2;
			
			std::complex<T> temp = data[i] - data[i2];
			data[i] += data[i2];
			data[i2] = std::complex<T>(cosA, -sinA)*temp;
		 }
	}

	Fourier::Internal<T, SIZE, LEVEL/2, INCREMENT>::transform(data);
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE, int INCREMENT>
void Fourier::Internal<T, SIZE, 8, INCREMENT>::transform(std::complex<T> *data)
{
	static T sin_t[SIZE];
	static T cos_t[SIZE];
	static const T twoPi = 2*T(M_PI);
	static const T twoPiOverN = twoPi / static_cast<T>(SIZE);
	static bool inited = false;
	if (!inited)
	{
		for (int i = 0; i < SIZE; ++i)
		{
			cos_t[i] = cos(i*twoPiOverN);
			sin_t[i] = sin(i*twoPiOverN);
		}
		inited = true;
	}

	Internal2<T, SIZE/4, INCREMENT*4>::transform(data);

	for (unsigned int i = 1*INCREMENT; i < SIZE*INCREMENT; i += 8*INCREMENT)
	{
//		T cosA = M_SQRT1_2 = cos(twoPi / 8);
//		T sinA = M_SQRT1_2 = sin(twoPi / 8);
		int i2 = i + 8*INCREMENT/2;
		
		std::complex<T> temp = data[i] - data[i2];
		data[i] += data[i2];
		data[i2] = std::complex<T>(T(M_SQRT1_2), -T(M_SQRT1_2))*temp;
	}

	Internal4<T, SIZE/2, INCREMENT*2>::transform(data);

	for (unsigned int i = 3*INCREMENT; i < SIZE*INCREMENT; i += 8*INCREMENT)
	{
//		T cosA = -M_SQRT1_2;//cos(3 * twoPi / 8);
//		T sinA = M_SQRT1_2;//sin(3 * twoPi / 8);
		int i2 = i + 8*INCREMENT/2;
		
		std::complex<T> temp = data[i] - data[i2];
		data[i] += data[i2];
		data[i2] = std::complex<T>(-T(M_SQRT1_2), -T(M_SQRT1_2))*temp;
	}

	Internal<T, SIZE, 4, INCREMENT>::transform(data);
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE, int INCREMENT>
void Fourier::Internal4<T, SIZE, INCREMENT>::transform(std::complex<T> *data)
{
	for (unsigned int i = INCREMENT; i < SIZE*INCREMENT; i += 4*INCREMENT)
	{
		int i2 = i + 2*INCREMENT;
		
		std::complex<T> temp = data[i] - data[i2];
		data[i] =  data[i] + data[i2];
		data[i2] = std::complex<T>(temp.imag(), -temp.real());
	}
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE, int INCREMENT>
void Fourier::Internal<T, SIZE, 4, INCREMENT>::transform(std::complex<T> *data)
{
	Internal2<T, SIZE/2, INCREMENT*2>::transform(data);
	Internal4<T, SIZE, INCREMENT>::transform(data);
	Internal<T, SIZE, 2, INCREMENT>::transform(data);
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE, int INCREMENT>
void Fourier::Internal2<T, SIZE, INCREMENT>::transform(std::complex<T> *data)
{
	for (unsigned int i = 0; i < SIZE*INCREMENT; i += 2*INCREMENT)
	{
		std::complex<T> 	temp = data[i];
		data[i] 		  = data[i] + data[i+INCREMENT];
		data[i+INCREMENT] = temp 	- data[i+INCREMENT];
	}
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE, int INCREMENT>
void Fourier::Internal<T, SIZE, 2, INCREMENT>::transform(std::complex<T> *data)
{
	Internal2<T, SIZE, INCREMENT>::transform(data);
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE, int INCREMENT>
void Fourier::Internal<T, SIZE, 1, INCREMENT>::transform(std::complex<T> *data)
{
	return;
}

//--------------------------------------------------------------------------
//
template<class T, int TYPE, int SIZE, int INCREMENT>
void Fourier::normalizedFastTransform(std::complex<T> *data)
{
	fastTransform<T, TYPE, SIZE, INCREMENT>(data);
	
	const T oneOverSqrtOfSize = 1.0/sqrt(SIZE);
	for (unsigned int i = 0; i < SIZE*INCREMENT; i+=INCREMENT)
		data[i] *= oneOverSqrtOfSize;
}

//--------------------------------------------------------------------------
//
template<class T, int TYPE, int SIZE, int INCREMENT>
void Fourier::fastTransform(std::complex<T> *data)
{
	static const unsigned int end = SIZE*INCREMENT;

	// Conjugate if backward transform
	if (TYPE == REVERSE)
	{
		for (unsigned int i = 0; i < end; i+=INCREMENT )
			data[i] = conj(data[i]);
	}

	// Main loop
	Internal<T, SIZE, SIZE, INCREMENT>::transform(data);

	// Bit reversal permutation
	unsigned int j = 0;
	for (unsigned int i = 0; i < SIZE-1; i++)
	{
		if (i < j)
		{
			unsigned int iIncrement = i*INCREMENT;
			unsigned int jIncrement = j*INCREMENT;

			std::complex<T> temp = data[jIncrement];
			data[jIncrement] = data[iIncrement];
			data[iIncrement] = temp;
		}
		unsigned int k = SIZE>>1;
		while ( k < j+1 )
		{
			j -= k;
			k >>= 1;
		}
		j += k;
	}

	if (TYPE == REVERSE)
	{
		for (unsigned int i = 0; i < end; i+=INCREMENT)
			data[i] = conj(data[i]);
	}

//	don't scale, let the caller do it

//	const T oneOverSqrtOfSize = 1.0/sqrt(size);
//	for (unsigned int i = 0; i < end; i+=increment)
//		data[i] *= oneOverSqrtOfSize;
}

//--------------------------------------------------------------------------
//
template<class T, int TYPE>
void Fourier::normalizedFastTransform(std::complex<T> *data, unsigned int size, int increment)
{
	fastTransform<T, TYPE>(data, size, increment);
	
	const T oneOverSqrtOfSize = 1.0/sqrt(size);
	for (unsigned int i = 0; i < size*increment; i+=increment)
		data[i] *= oneOverSqrtOfSize;
}


//------------------------------------------------------------------------------
//
template<class T, int TYPE>
void Fourier::fastTransform(std::complex<T> *data, unsigned int size, int increment)
{
//	if (!isPow2(size))
//	{
//		fprintf(stderr, "Can only transform power of 2 data sizes.  %d is not a power of 2\n", size);
//		return;
//	}
	
	const unsigned int end = size*increment;
	
	const T TWO_PI = T(2*M_PI);
	unsigned int m = log2(size);

	// Quick return for size=1
	if (size == 1) return;

	// Conjugate if backward transform
	if (TYPE == REVERSE)
	{
		for (unsigned int i = 0; i < end; i+=increment )
			data[i] = conj(data[i]);
	}

	// Main loop
	const T twoPiOverN = TWO_PI / static_cast<T>(size);
	unsigned int size2 = size;
	for (unsigned int k = 1; k <= m; k++)
	{
		unsigned int size1 = size2;
		size2 >>= 1;
		int ie = size / size1;
		int ia = 1;
		for (unsigned int j = 0; j < size2; j++)
		{
			T a = static_cast<T>(ia-1) * twoPiOverN;
			T cosA = cos(a);
			T sinA = sin(a);
			ia += ie;
			for (unsigned int i = j; i < size; i += size1)
			{
				int l = i + size2;
				int iIncrement = i*increment;
				int lIncrement = l*increment;
				
				std::complex<T> temp = data[iIncrement] - data[lIncrement];
				data[iIncrement] += data[lIncrement];
				data[lIncrement] = std::complex<T>(cosA, -sinA) * temp;
			 }
		}
	}
	
	// Bit reversal permutation
	unsigned int j = 0;
	for (unsigned int i = 0; i < size-1; i++)
	{
		if (i < j)
		{
			unsigned int iIncrement = i*increment;
			unsigned int jIncrement = j*increment;

			std::complex<T> temp = data[jIncrement];
			data[jIncrement] = data[iIncrement];
			data[iIncrement] = temp;
		}
		unsigned int k = size>>1;
		while ( k < j+1 )
		{
			j -= k;
			k >>= 1;
		}
		j += k;
	}

	if (TYPE == REVERSE)
	{
		for (unsigned int i = 0; i < end; i+=increment)
			data[i] = conj(data[i]);
	}

//	don't scale, let the caller do it

//	const T oneOverSqrtOfSize = 1.0/sqrt(size);
//	for (unsigned int i = 0; i < end; i+=increment)
//		data[i] *= oneOverSqrtOfSize;
}

//------------------------------------------------------------------------------
//
inline bool Fourier::isPow2(unsigned int val)
{
	return (val & (val - 1)) == 0;
}

//------------------------------------------------------------------------------
//
inline int Fourier::log2(unsigned int value)
{
	//	this works only on CPUs with IEEE floating numbers, 32 bits int 
	//	and 64 bits double.  Otherwise, use the code commented at the end
	static const int isLittleEndian =  (*(int*)"abcd") != 'abcd';

	union {
		unsigned int asInt[2];
		double asDouble;
	} val;

	val.asDouble = static_cast<double>(value) + 0.5;
	return (val.asInt[isLittleEndian] >> 20)-1023;
	
	//	if the above fails, use this instead

	//	int l2 = 0;
	//	while (value)
	//		++l2, value >>= 1;
	//	return l2;
}

} // namespace seed


#endif // __GENERIC_MATH_FOURIER_INLINE__
