/*******************************************************************************
 Copyright 2009 Enseed inc.
 
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
#ifndef __GEOMETRY_LUMATRIXDETERMINANT_INLINE_H__
#define __GEOMETRY_LUMATRIXDETERMINANT_INLINE_H__

#include "../LUMatrixDeterminant.h"
#include "../LUDecomposition.h"

namespace seed {

template<typename _T, int _SIZE>
_T LUMatrixDeterminant::determinant(const Matrix<_T, _SIZE, _SIZE> &matrix)
{
	Matrix<_T, _SIZE, _SIZE> l, u;
	Matrix<int, 1, _SIZE> p;

	// The determinant is simply the product of the diagonals. In our case,
	// our LU decomposition returns 1s on the diagonal of the upper matrix, so
	// we don't have to look it up to tell that |U| = 1.

	if (!LUDecomposition::decompose(matrix, &l, &u, &p))
		return false;

	_T detL = 1;
	for (int i = 0; i < _SIZE; ++i)
		detL *= l[i][i];

	return detL;
}

}

#endif //__GEOMETRY_LUMATRIXDETERMINANT_INLINE_H__

