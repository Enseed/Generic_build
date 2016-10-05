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
#ifndef __GEOMETRY_MATRIXUTILS_INLINE__
#define __GEOMETRY_MATRIXUTILS_INLINE__

#include "../Matrix.h"
#include "../Point.h"
#include "../Quat.h"
#include "../LUDecomposition.h"

#if 0
#include "../QRDecomposition.h"
#endif

namespace seed {


template <class _T, int _SIZE>
void MatrixUtils::pivotMatrixFromPoint(const Point<int, _SIZE> &pt, Matrix<_T, _SIZE, _SIZE> *mat)
{
	*mat = Matrix<_T, _SIZE, _SIZE>::zero();
	for (int i = 0; i < _SIZE; ++i)
		(*mat)[i][pt[i]] = 1;
}

Point3d MatrixUtils::unProject(const Point2d &iPt, double atZ, const Matrix4d &inverseProjectionMatrix)
{
	// fix me later... there is probably a much better way to do this

	// find the ray that goes from the near to the far plane
	Point4d nPt(iPt.x, iPt.y, 1, 1);
	Point4d fPt(iPt.x, iPt.y, -1, 1);

	// move the ray according to the camera position
	nPt = inverseProjectionMatrix * nPt;
	fPt = inverseProjectionMatrix * fPt;

	// normalize
	Point3d nPt3d = Point3d(nPt.x, nPt.y, nPt.z) /= nPt.w;
	Point3d fPt3d = Point3d(fPt.x, fPt.y, fPt.z) /= fPt.w;

	// find the x,y value along the ray for which z = atZ

	// first get the vector that goes from nPt to fPt
	Point3d vPt = fPt3d - nPt3d;

	// fint t for which the z value in t*vPt + nPt is atZ
	double t = (atZ - nPt3d.z)/vPt.z;

	return  nPt3d + t*vPt;
}

template <class _T>
Matrix<_T, 4, 4> MatrixUtils::translation(const Point<_T, 3> &t)
{
	Matrix<_T, 4, 4> m;
	m = Matrix<_T, 4, 4>::identity();
	m[0][3] = t.x;
	m[1][3] = t.y;
	m[2][3] = t.z;
	return m;
}

template <class _T>
Matrix<_T, 4, 4> MatrixUtils::rotation(_T angle, const Point<_T, 3> &axis)
{
	Matrix<_T, 4, 4> m;
	Quat<_T>(axis, angle).normalize().to4x4Matrix(&m);
	return m;
}

template <class _T>
Matrix<_T, 4, 4> MatrixUtils::scaling(const Point<_T, 3> &s)
{
	Matrix<_T, 4, 4> m;
	m = Matrix<_T, 4, 4>::zero();
	m[0][0] = s.x;
	m[1][1] = s.y;
	m[2][2] = s.z;
	m[3][3] = 1;
	return m;
}

#if 0
template <class _T, int _SIZE>
bool MatrixUtils::qrDecompose(
	const Matrix<_T, _SIZE, _SIZE> &mat, 
	Matrix<_T, _SIZE, _SIZE> *q, 
	Matrix<_T, _SIZE, _SIZE> *r)
{
	return QRDecomposition::decompose(mat, q, r);
}
#endif

template <class _T>
bool MatrixUtils::rotationMatrixToZYRotation(const Matrix<_T, 3, 3> &rotMatrix, _T *ry, _T *rz)
{
	Point<_T, 3> pt(1, 0, 0);
	pt = rotMatrix*pt.asTMatrix();
	if (ry)	*ry = ::asin(pt.z);
	if (rz)
	{
		*rz = ::asin(pt.y);
		if (pt.x < 0)	*rz = M_PI - *rz;
	}
	return true;
}

template<class _T>
bool MatrixUtils::matrixToTransformation(const Matrix<_T, 4, 4> &matrix, _T *ry, _T *rx, Point<_T, 3> *scale, Point<_T, 3> *trans)
{
	Matrix<_T, 3, 3> matrix3x3, q, r;
	for (int j = 0; j < 3; ++j)
		for (int i = 0; i < 3; ++i)
			matrix3x3[j][i] = matrix[j][i];

	qrDecompose(matrix3x3, &q, &r);
	rotationMatrixToZYRotation(q, ry, rx);
	if (scale)
	{
		scale->x = r[0][0];
		scale->y = r[1][1];
		scale->z = r[2][2];
	}
	if (trans)
	{
		trans->x = matrix[0][3];
		trans->y = matrix[1][3];
		trans->z = matrix[2][3];
	}
	return true;
}

template <class _T, int _SIZE>
bool MatrixUtils::luDecompose(
	const Matrix<_T, _SIZE, _SIZE> &mat, 
	Matrix<_T, _SIZE, _SIZE> *l, 
	Matrix<_T, _SIZE, _SIZE> *u)
{
	return LUDecomposition::decompose(mat, l, u);
}

template <class _T, int _SIZE>
bool MatrixUtils::luDecompose(
	const Matrix<_T, _SIZE, _SIZE> &mat, 
	Matrix<_T, _SIZE, _SIZE> *l, 
	Matrix<_T, _SIZE, _SIZE> *u, 
	Point<int, _SIZE> *p)
{
	return LUDecomposition::decompose(mat, l, u, p);
}

//	solve for x in (p*l*u)*x = b (x and b can be matrices)
template <class _T, int _SIZE, int _BXWIDTH>
bool MatrixUtils::luSolve(
	const Matrix<_T, _SIZE, _SIZE> &l, 
	const Matrix<_T, _SIZE, _SIZE> &u,
	Matrix<_T, _BXWIDTH, _SIZE> *xb)
{
	return LUDecomposition::solve(l, u, xb);
}

template <class _T, int _SIZE>
bool MatrixUtils::luInverse(
	const Matrix<_T, _SIZE, _SIZE> &matrix, 
	Matrix<_T, _SIZE, _SIZE> *inverse,
	bool robustButSlower
)
{
	Matrix<_T, _SIZE, _SIZE> l, u;
	if (robustButSlower)
	{
		Point<int, _SIZE> p;
		if (!luDecompose(matrix, &l, &u, &p))	return false;
		pivotMatrixFromPoint(p, inverse);
		if (!luSolve(l, u, inverse))	return false;
	}
	else
	{
		if (!luDecompose(matrix, &l, &u)) return false;
		*inverse = Matrix<_T, _SIZE, _SIZE>::identity();
		if (!luSolve(l, u, inverse))	return false;
	}
	return true;
}

} // namespace seed


#endif // __GEOMETRY_MATRIXUTILS_INLINE__
