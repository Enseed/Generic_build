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

/*******************************************************************************
THIS CODE REFERS TO FFTW WHICH IS RELEASED UNDER GPL.
*******************************************************************************/

#ifndef __GENERIC_MATH_FOURIERTRANSFORM__
#define __GENERIC_MATH_FOURIERTRANSFORM__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "../Base/Base.h"

namespace seed {

//==============================================================================
//	FORWARD DECLARATIONS
//==============================================================================
class FTR2C;	//	FourierTransform Real to Complex
class FTC2C;	//	FourierTransform Complex to Complex

//==============================================================================
//	CLASS: FourierTransform
//==============================================================================
//	The forward and reverse transform expect either real or complex data
//	(depending on the variation).  When complex data is expected, the
//	real and complex values should be interleaved.
//
//	Use spectralWidth() to know how big your buffer should be - when performing
//	real to complex, only half of the transform is computed since the other
//	half is the complex conjugate of the first.
//
//	
template <typename T>
class FourierTransform
{
public:
	FourierTransform(int width, int height = 0, int depth = 0);
	~FourierTransform();
	
	int spatialWidth();
	int spatialHeight();
	int spatialDepth();
	int spatialLength();	//	number of elements (width*height*depth)
	
	int spectralWidth();
	int spectralHeight();
	int spectralDepth();
	
	int spectralLength();	//	number of elements (width*height*depth)
	
	//	Non-normalized transforms (i.e. F^-1(F(f)) = width*height*f)
	void forward(double *spat, double *spec);
	void reverse(double *spec, double *spat);
	
	//	Normalized transforms (i.e. F^-1(F(f)) = f)
	void forwardNormalized(double *spat, double *spec);
	void reverseNormalized(double *spec, double *spat);

private:
	T *mImp;
	
private:
	FourierTransform(const FourierTransform&);
	FourierTransform& operator=(const FourierTransform&);
};

//==============================================================================
//	TYPE DECLARATIONS
//==============================================================================
typedef class FourierTransform<FTR2C> FourierTransformR2C;
typedef class FourierTransform<FTC2C> FourierTransformC2C;

} // namespace seed



#endif // __GENERIC_MATH_FOURIERTRANSFORM__
