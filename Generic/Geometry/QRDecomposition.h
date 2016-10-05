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
#ifndef __GEOMETRY_QRDECOMPOSITION__
#define __GEOMETRY_QRDECOMPOSITION__

// Factorise a matrix A into a Q and R matrices such that A = Q*R, Q being
// orthogonal (Q^t = Q^-1 or Q^tQ = I) and R is an upper triangle matrix

//==============================================================================
// CLASS LUDecomposition
//==============================================================================

namespace seed {

template<class _T, int _WIDTH, int _HEIGHT> class Matrix;

class QRDecomposition
{
public:
	template<class _T, int _SIZE>
	static bool decompose(const Matrix<_T, _SIZE, _SIZE> &m, Matrix<_T, _SIZE, _SIZE> *q, Matrix<_T, _SIZE, _SIZE> *r);
};

} // namespace seed


#include "src/QRDecomposition.inline.h"

#endif // __GEOMETRY_QRDECOMPOSITION__
