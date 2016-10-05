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
#ifndef __GENERIC_MATH_GAUSSIAN__
#define __GENERIC_MATH_GAUSSIAN__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "../Geometry/Matrix.h"
#include "../Geometry/Point.h"

// The gaussian class is usefull to gather statistics.  You add points
// and then ask for a distribution.  Don't forget that you can use 
// Point#T.asMatrix() (e.g. Point3f.asMatrix()) to make
// your life easier...

//==============================================================================
//	CLASS Gaussian
//==============================================================================
namespace seed {

template <class T, int D>
class Gaussian
{
public:
	//--------------------------------------------------------------------------
	//
	class Distribution
	{
	public:
		Distribution() {}
		Distribution(const Gaussian &gaussian);
		Distribution(const Point<T, D> &mean, const Matrix<T, D, D> &covariance);
	
	public:
		double prob(const Point<T, D> &x) const;

		const Matrix<T, D, D>& covariance() const;
		const Matrix<T, D, D>& inverseCovariance() const;
		T determinant() const;
		const Point<T, D>& mean() const;

		void setCovariance(const Matrix<T, D, D> cov);
		void setMean(const Point<T, D> &mean);

	private:
		Point<T, D>	mMean;
		Matrix<T, D, D>	mCovariance;
		Matrix<T, D, D>	mInverseCovariance;
		T mDeterminant;
	};

	Gaussian();
	void clear();
	void addSample(const Point<T, D> &sample, T weight);
	void addSample(const Point<T, D> &sample);
	T weight();
	

private:
	Point<T, D>	mMeanSum;
	Matrix<T, D, D> mCovSum;
	T mTotal;
};

//==============================================================================
//	TYPE DECLARATIONS
//==============================================================================
typedef Gaussian<float, 3>	Gaussian3f;
typedef Gaussian<float, 2>	Gaussian2f;
typedef Gaussian<float, 1>	Gaussian1f;
typedef Gaussian<double, 1>	Gaussian1d;
typedef Gaussian<double, 3>	Gaussian3d;
typedef Gaussian<double, 2>	Gaussian2d;

} // namespace seed



//==============================================================================
//	INLINED CODE
//==============================================================================
#include "src/Gaussian.inline.h"

#endif // __GENERIC_MATH_GAUSSIAN__
