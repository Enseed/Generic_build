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
#ifndef __GENERIC_MATH_GAUSSIAN_INLINE__
#define __GENERIC_MATH_GAUSSIAN_INLINE__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "../Gaussian.h"


namespace seed {
//==============================================================================
//	CLASS Gaussian::Distribution
//==============================================================================

//------------------------------------------------------------------------------
//
template <class T, int D>
Gaussian<T, D>::Distribution::Distribution(const Point<T, D> &mean, const Matrix<T, D, D> &covariance)
:
	mMean(mean),
	mCovariance(covariance),
	mInverseCovariance(covariance.inversed()),
	mDeterminant(Determinant(covariance))
{}

//------------------------------------------------------------------------------
//
template <class T, int D>
Gaussian<T, D>::Distribution::Distribution(const Gaussian<T, D> &gaussian)
:
	mMean(),
	mCovariance(),
	mInverseCovariance(),
	mDeterminant()
{
	T oneOverTotal = 1/gaussian.mTotal;
	
	Point<T, D> mu = gaussian.mMeanSum*oneOverTotal;

	Matrix<T, D, D> cov;
	for (int j = 0; j < D; ++j)
		for (int i = j; i < D; ++i)
			cov[i][j] = 
				cov[j][i] = 
					gaussian.mCovSum[j][i]*oneOverTotal - 
					mu[j]*mu[i];

	mMean = mu;
	mCovariance = cov;
	mInverseCovariance = Matrix<T,D,D>(mCovariance.inversed());
	mDeterminant = Determinant(mCovariance);
}

//------------------------------------------------------------------------------
//
template <class T, int D>
const Matrix<T, D, D>& Gaussian<T, D>::Distribution::covariance() const
{
	return mCovariance;
}

//------------------------------------------------------------------------------
//
template <class T, int D>
const Matrix<T, D, D>& Gaussian<T, D>::Distribution::inverseCovariance() const
{ 
	return mInverseCovariance;
}

//------------------------------------------------------------------------------
//
template <class T, int D>
T Gaussian<T, D>::Distribution::determinant() const
{
	return mDeterminant;
}

//------------------------------------------------------------------------------
//
template <class T, int D>
const Point<T, D>& Gaussian<T, D>::Distribution::mean() const 
{
	return mMean;
}

//------------------------------------------------------------------------------
//
template <class T, int D>
void Gaussian<T, D>::Distribution::setCovariance(const Matrix<T, D, D> cov)
{
	mCovariance = cov;
	mInverseCovariance = cov.inversed(); 
	mDeterminant = Determinant(cov);
}

//------------------------------------------------------------------------------
//
template <class T, int D>
void Gaussian<T, D>::Distribution::setMean(const Point<T, D> &mean)
{
	mMean = mean;
}

//------------------------------------------------------------------------------
//
template <class T, int D>
double Gaussian<T, D>::Distribution::prob(const Point<T, D> &x) const
{
	ASSERTF(!std::numeric_limits<T>::is_integer, "scaling of integer vector is not defined.");
	Matrix<T, 1, D> d = (x-mMean).asTMatrix();
	if (!mInverseCovariance.hasNan() && !mInverseCovariance.hasInf() && mDeterminant > 0.000000001)
	{
		double pr = exp(	-0.5 * (d.transposed() * mInverseCovariance * d)[0][0] ) / 
				sqrt(pow(2*M_PI, D)*mDeterminant);
		return pr;
	}
	else
	{
		int i = 0;
		for (i = 0; i < D; ++i)
		{
			if (d[0][i] < -0.000000001 || d[0][i] > 0.000000001)
				return 0.0;
		}
		
		return 1.0;
	}
}

//==============================================================================
//	CLASS Gaussian
//==============================================================================

//------------------------------------------------------------------------------
//
template <class T, int D>
Gaussian<T, D>::Gaussian()
:
	mMeanSum(),
	mCovSum(),
	mTotal()
{
	clear();
}

//------------------------------------------------------------------------------
//
template <class T, int D>
void Gaussian<T, D>::addSample(const Point<T, D> &p)
{
	addSample(p, 1);
}

//------------------------------------------------------------------------------
//
template <class T, int D>
void Gaussian<T, D>::addSample(const Point<T, D> &p, T w)
{
	Point<T, D> pw = p*w;
	mMeanSum += pw;
	
	for (int j = 0; j < D; ++j)
		for (int i = j; i < D; ++i)
			mCovSum[j][i] += pw[j]*p[i];
	
	mTotal += w;
}

//------------------------------------------------------------------------------
//
template <class T, int D>
T Gaussian<T, D>::weight()
{
	return mTotal;
}

//------------------------------------------------------------------------------
//
template <class T, int D>
void Gaussian<T, D>::clear()
{
	mTotal = 0;
	mMeanSum = Point<T, D>(0);
	mCovSum = Matrix<T, D, D>::zero();
}


} // namespace seed


#endif // __GENERIC_MATH_GAUSSIAN_INLINE__
