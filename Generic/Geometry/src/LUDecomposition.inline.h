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
#ifndef __GEOMETRY_LUDECOMPOSITION_INLINE__
#define __GEOMETRY_LUDECOMPOSITION_INLINE__

//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================
#include "../LUDecomposition.h"
#include "../Matrix.h"

namespace seed {


//==============================================================================
// DEBUGGING
//==============================================================================
/*
namespace {
// Used for debugging
template<class T, int SIZE>
void PrintPivotedMatrix( const T *mdata, const int *pdata)
{
	Matrix<T, SIZE, SIZE> m(mdata);
	Point<int, SIZE> pivot(pdata);
	Matrix<T, SIZE, SIZE> pm;
	pm.zero();
	for (int i =0; i < SIZE; ++i)
		pm[i][pivot[i]] = 1;

	(pm*m).dump();
}
}
*/

//==============================================================================
// CLASS LUDecomposition
//==============================================================================

//------------------------------------------------------------------------------
//
template<typename _T, int _SIZE>
bool LUDecomposition::decompose(
	const Matrix<_T, _SIZE, _SIZE> &matrix, 
	Matrix<_T, _SIZE, _SIZE> *l, 
	Matrix<_T, _SIZE, _SIZE> *u
)
{
	*u = matrix;
	*l = Matrix<_T, _SIZE, _SIZE>::identity();
	return LUSubDecomposition<_T, 0, _SIZE, _SIZE>::decomposeRecur(u->ptr(), l->ptr());
}

//------------------------------------------------------------------------------
//
template<typename _T, int _SIZE>
bool LUDecomposition::decompose(
	const Matrix<_T, _SIZE, _SIZE> &matrix, 
	Matrix<_T, _SIZE, _SIZE> *l,
	Matrix<_T, _SIZE, _SIZE> *u,
	Matrix<int, 1, _SIZE> *p)
{
	for (int i = 0; i < _SIZE; ++i)	(*p)[i][0] = i;
	*u = matrix;
	*l = Matrix<_T, _SIZE, _SIZE>::identity();
	return LUSubDecomposition<_T, 0, _SIZE, _SIZE>::decomposeRecur(u->ptr(), l->ptr(), p->ptr());
}

//------------------------------------------------------------------------------
//
template<typename _T, int _SIZE, int _BXWIDTH>
bool LUDecomposition::solve(
	const Matrix<_T, _SIZE, _SIZE> &l, 
	const Matrix<_T, _SIZE, _SIZE> &u,
	Matrix<_T, _BXWIDTH, _SIZE> *xb)
{
	return LUSubDecomposition<_T, 0, _SIZE, _SIZE>::solve(l, u, xb);
}

//==============================================================================
// PRIVATE CLASS LUDecomposition::RowOperation
//==============================================================================

//------------------------------------------------------------------------------
//
template<typename _T, int _SIZE>
void LUDecomposition::RowOperation<_T, _SIZE>::multiply(_T *intoRow, const _T *row, const _T &factor)
{
	for (int i = 0; i < _SIZE; ++i)	intoRow[i] = row[i] * factor;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _SIZE>
void LUDecomposition::RowOperation<_T, _SIZE>::addRowTimesFactor(_T *intoRow, const _T *srcRow, const _T *addRow, const _T &timesFactor)
{
	for (int i = 0; i < _SIZE; ++i)	intoRow[i] = srcRow[i] + addRow[i] * timesFactor;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _SIZE>
void LUDecomposition::RowOperation<_T, _SIZE>::swap(_T *row1, _T *row2)
{
	_T tmp[_SIZE];
	memcpy(tmp, row1, _SIZE*sizeof(_T));
	memcpy(row1, row2, _SIZE*sizeof(_T));
	memcpy(row2, tmp, _SIZE*sizeof(_T));
}

//==============================================================================
// PRIVATE CLASS LUDecomposition::RowOperation<_T, 0>
//==============================================================================

//------------------------------------------------------------------------------
//
template<typename _T>
void LUDecomposition::RowOperation<_T, 0>::multiply(_T *intoRow, const _T *row, const _T &factor)
{}

//------------------------------------------------------------------------------
//
template<typename _T>
void LUDecomposition::RowOperation<_T, 0>::addRowTimesFactor(_T *intoRow, const _T *srcRow, const _T *addRow, const _T &timesFactor)
{}

//------------------------------------------------------------------------------
//
template<typename _T>
void LUDecomposition::RowOperation<_T, 0>::swap(_T *row1, _T *row2)
{}

//==============================================================================
// PRIVATE CLASS LUDecomposition::LUSubDecomposition
//==============================================================================

//------------------------------------------------------------------------------
//
template<typename _T, int _OFFSET, int _WIDTH, int _HEIGHT>
bool LUDecomposition::LUSubDecomposition<_T, _OFFSET, _WIDTH, _HEIGHT>::decomposeRecur(_T * u, _T * l)
{
	if (!decompose(u, l))
		return false;
		
	return LUSubDecomposition<_T, _OFFSET+1, _WIDTH, _HEIGHT>::decomposeRecur(u, l);
}

//------------------------------------------------------------------------------
//
template<typename _T, int _OFFSET, int _WIDTH, int _HEIGHT>
bool LUDecomposition::LUSubDecomposition<_T, _OFFSET, _WIDTH, _HEIGHT>::decompose(_T * u, _T * l)
{
	const int width = _WIDTH;
	const int height = _HEIGHT;

	// normalize the row
	_T factor = u[_OFFSET*width + _OFFSET];
	l[_OFFSET*width + _OFFSET] = factor;
			
	u[_OFFSET*width + _OFFSET] = 1;
	RowOperation<_T, _WIDTH-_OFFSET-1>::multiply(
		&u[_OFFSET*width + _OFFSET+1], 
		&u[_OFFSET*width + _OFFSET+1], 
		static_cast<_T>(1.0)/factor
	);

	for (int j = _OFFSET+1; j < height; ++j)
	{
		factor = u[j*width + _OFFSET];
		l[j*width + _OFFSET] = factor;
		u[j*width + _OFFSET] = 0;
		RowOperation<_T, _WIDTH-_OFFSET-1>::addRowTimesFactor(&u[j*width + _OFFSET+1], &u[j*width + _OFFSET+1], &u[_OFFSET*width + _OFFSET+1], -factor);
	}
	
	return true;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _OFFSET, int _WIDTH, int _HEIGHT>
bool LUDecomposition::LUSubDecomposition<_T, _OFFSET, _WIDTH, _HEIGHT>::decomposeRecur(_T *u, _T *l, int *p)
{
	if (!decompose(u, l, p))
		return false;

	return LUSubDecomposition<_T, _OFFSET+1, _WIDTH, _HEIGHT>::decomposeRecur(u, l, p);
}

//------------------------------------------------------------------------------
//
template<typename _T, int _OFFSET, int _WIDTH, int _HEIGHT>
bool LUDecomposition::LUSubDecomposition<_T, _OFFSET, _WIDTH, _HEIGHT>::decompose(_T *u, _T *l, int *p)
{
	const int width = _WIDTH;
	const int height = _HEIGHT;

	//	swap with a lower row so that we have the highest value factor
	// FIXME: we need to use something other than fabs here
	_T max = fabs(u[_OFFSET*width + _OFFSET]);
	int maxRow = _OFFSET;
	for (int j = _OFFSET+1; j < height; ++j)
	{
		_T v = fabs(u[j*width + _OFFSET]);
		if (v > max)
		{
			max = v;
			maxRow = j;
		}
	}

	if (maxRow != _OFFSET)
	{
		int temp = p[_OFFSET];
		p[_OFFSET] = p[maxRow];
		p[maxRow] = temp;
		RowOperation<_T, _WIDTH-_OFFSET>::swap(&u[maxRow*width+_OFFSET], &u[_OFFSET*width+_OFFSET]);
		RowOperation<_T, _OFFSET>::swap(&l[maxRow*width], &l[_OFFSET*width]);

	}

	return decompose(u, l);
}

//------------------------------------------------------------------------------
//
template<typename _T, int _OFFSET, int _WIDTH, int _HEIGHT> template<int _BXWIDTH>
bool LUDecomposition::LUSubDecomposition<_T, _OFFSET, _WIDTH, _HEIGHT>::solveLyEqualsB(
	Matrix<_T, _WIDTH, _HEIGHT> *l,
	Matrix<_T, _BXWIDTH, _HEIGHT> *bx)
{
	_T factor = (*l)[_OFFSET][_OFFSET];
	RowOperation<_T, _BXWIDTH>::multiply((*bx)[_OFFSET], (*bx)[_OFFSET], 1.0f/factor);

	// make sure there is a row under us
	if (_OFFSET >= _HEIGHT-1)	return true;

	// substract the row so that all lower rows have a 0 at _OFFSET
	for (int j = _OFFSET+1; j < _HEIGHT; ++j)
	{
		factor = (*l)[j][_OFFSET];
		RowOperation<_T, _BXWIDTH>::addRowTimesFactor((*bx)[j], (*bx)[j], (*bx)[_OFFSET], -factor);
		(*l)[j][_OFFSET] = 0;
	}
	// solve the problem for _SIZE-1
	LUSubDecomposition<_T, _OFFSET+1, _WIDTH, _HEIGHT>::solveLyEqualsB(l, bx);

	return true;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _OFFSET, int _WIDTH, int _HEIGHT> template<int _BXWIDTH>
bool LUDecomposition::LUSubDecomposition<_T, _OFFSET, _WIDTH, _HEIGHT>::solveUxEqualsY(
	Matrix<_T, _WIDTH, _HEIGHT> *u,
	Matrix<_T, _BXWIDTH, _HEIGHT> *bx)
{
	// make sure there is a row under us
	if (_OFFSET >= _HEIGHT-1)	return true;

	// solve the problem for _SIZE-1
	LUSubDecomposition<_T, _OFFSET+1, _WIDTH, _HEIGHT>::solveUxEqualsY(u, bx);

	// substract the row so that all upper rows have a 0 at _OFFSET
	for (int j = 0; j < _OFFSET+1; ++j)
	{
		_T factor = (*u)[j][_OFFSET+1];
		RowOperation<_T, _BXWIDTH>::addRowTimesFactor((*bx)[j], (*bx)[j], (*bx)[_OFFSET+1], -factor);
		(*u)[j][_OFFSET+1] = 0;
	}

	return true;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _OFFSET, int _WIDTH, int _HEIGHT> template<int _BXWIDTH>
bool LUDecomposition::LUSubDecomposition<_T, _OFFSET, _WIDTH, _HEIGHT>::solve(
	const Matrix<_T, _WIDTH, _HEIGHT> &l, 
	const Matrix<_T, _WIDTH, _HEIGHT> &u,
	Matrix<_T, _BXWIDTH, _HEIGHT> *bx)
{
	// we want to solve Ax = b where A = LU
	// we can write LUx = b
	// subsituing Ux = y, we have:
	//				Ly = b
	//
	// Ux = y is easy to solve, and Ly = b is also easy to solve

	// start solving Ly = b

	Matrix<_T, _WIDTH, _HEIGHT> lCopy(l);
	if (!solveLyEqualsB(&lCopy, bx))	return false;

	Matrix<_T, _WIDTH, _HEIGHT> uCopy(u);
	if (!solveUxEqualsY(&uCopy, bx))	return false;

	return true;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _OFFSET, int _WIDTH>
bool LUDecomposition::LUSubDecomposition<_T, _OFFSET, _WIDTH, _OFFSET>::decomposeRecur(_T *u, _T *l, int *p)
{
	return true;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _OFFSET, int _WIDTH>
bool LUDecomposition::LUSubDecomposition<_T, _OFFSET, _WIDTH, _OFFSET>::decomposeRecur(_T *u, _T *l)
{
	return true;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _OFFSET, int _WIDTH> template<int _BXWIDTH>
bool LUDecomposition::LUSubDecomposition<_T, _OFFSET, _WIDTH, _OFFSET>::solveUxEqualsY(Matrix<_T, _WIDTH, _OFFSET> *u, Matrix<_T, _BXWIDTH, _OFFSET> *bx)
{
	return true;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _OFFSET, int _WIDTH> template<int _BXWIDTH>
bool LUDecomposition::LUSubDecomposition<_T, _OFFSET, _WIDTH, _OFFSET>::solveLyEqualsB(Matrix<_T, _WIDTH, _OFFSET> *l, Matrix<_T, _BXWIDTH, _OFFSET> *bx)
{
	return true;
}

} // namespace seed


#endif // __GEOMETRY_LUDECOMPOSITION_INLINE__
