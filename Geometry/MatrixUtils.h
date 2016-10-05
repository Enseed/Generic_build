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
#ifndef __GEOMETRY_MATRIXUTILS__
#define __GEOMETRY_MATRIXUTILS__

namespace seed {

template<class _T, int _WIDTH, int _HEIGHT> class Matrix;
template<class T, int SIZE> class Point;
template<class T> class Quat;

class MatrixUtils
{
public:
	template <class _T, int _SIZE>
	static inline void pivotMatrixFromPoint(const Point<int, _SIZE> &pt, Matrix<_T, _SIZE, _SIZE> *mat);

	static inline Point<double, 3> unProject(const Point<double, 2> &iPt, double atZ, const Matrix<double, 4, 4> &inverseProjectionMatrix);

	template <class _T>
	static inline Matrix<_T, 4, 4> translation(const Point<_T, 3> &t);

	template <class _T>
	static inline Matrix<_T, 4, 4> rotation(_T angle, const Point<_T, 3> &axis);

	template <class _T>
	static inline Matrix<_T, 4, 4> scaling(const Point<_T, 3> &s);

#if 0
	template <class _T, int _SIZE>
	static inline bool qrDecompose(
		const Matrix<_T, _SIZE, _SIZE> &mat, 
		Matrix<_T, _SIZE, _SIZE> *q, 
		Matrix<_T, _SIZE, _SIZE> *r);
#endif

	template <class _T>
	static inline bool rotationMatrixToZYRotation(const Matrix<_T, 3, 3> &rotMatrix, _T *ry, _T *rz);

	template<class _T>
	static inline bool matrixToTransformation(const Matrix<_T, 4, 4> &matrix, _T *ry, _T *rx, Point<_T, 3> *scale, Point<_T, 3> *trans);

	template <class _T, int _SIZE>
	static inline bool luDecompose(
		const Matrix<_T, _SIZE, _SIZE> &mat, 
		Matrix<_T, _SIZE, _SIZE> *l, 
		Matrix<_T, _SIZE, _SIZE> *u);

	template <class _T, int _SIZE>
	static inline bool luDecompose(
		const Matrix<_T, _SIZE, _SIZE> &mat, 
		Matrix<_T, _SIZE, _SIZE> *l, 
		Matrix<_T, _SIZE, _SIZE> *u, 
		Point<int, _SIZE> *p);

	//	solve for x in (p*l*u)*x = b (x and b can be matrices)
	template <class _T, int _SIZE, int _BXWIDTH>
	static inline bool luSolve(
		const Matrix<_T, _SIZE, _SIZE> &l, 
		const Matrix<_T, _SIZE, _SIZE> &u,
		Matrix<_T, _BXWIDTH, _SIZE> *xb);

	template <class _T, int _SIZE>
	static inline bool luInverse(
		const Matrix<_T, _SIZE, _SIZE> &matrix, 
		Matrix<_T, _SIZE, _SIZE> *inverse,
		bool robustButSlower
	);
};


} // namespace seed

#include "src/MatrixUtils.inline.h"

#endif // __GEOMETRY_MATRIXUTILS__
