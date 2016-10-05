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
#ifndef __GEOMETRY_LUDECOMPOSITION__
#define __GEOMETRY_LUDECOMPOSITION__

// Factorise a matrix A into an L and U matrix such that A = L*U or P*A = L*U 
// where P is a pivot matrix (changes the row order).

//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================
namespace seed {

//==============================================================================
// FORWARD DECLARATIONS
//==============================================================================
template <class _T, int _WIDTH, int _HEIGHT> class Matrix;

//==============================================================================
// CLASS LUDecomposition
//==============================================================================
class LUDecomposition
{
public:
	//--------------------------------------------------------------------------
	//
	template<typename _T, int _SIZE>
	static bool decompose(
		const Matrix<_T, _SIZE, _SIZE> &matrix, 
		Matrix<_T, _SIZE, _SIZE> *l, 
		Matrix<_T, _SIZE, _SIZE> *u
	);

	//--------------------------------------------------------------------------
	//
	template<typename _T, int _SIZE>
	static bool decompose(
		const Matrix<_T, _SIZE, _SIZE> &matrix, 
		Matrix<_T, _SIZE, _SIZE> *l,
		Matrix<_T, _SIZE, _SIZE> *u,
		Matrix<int, 1, _SIZE> *p);

	//--------------------------------------------------------------------------
	//
	template<typename _T, int _SIZE, int _BXWIDTH>
	static bool solve(
		const Matrix<_T, _SIZE, _SIZE> &l, 
		const Matrix<_T, _SIZE, _SIZE> &u,
		Matrix<_T, _BXWIDTH, _SIZE> *xb);

private:
	//==========================================================================
	// PRIVATE CLASS LUDecomposition::LUSubDecomposition
	//==========================================================================
	template<typename _T, int _OFFSET, int _WIDTH, int _HEIGHT>
	class LUSubDecomposition
	{
	public:
		static bool decomposeRecur(_T * u, _T * l);
		static bool decompose(_T * u, _T * l);
		static bool decomposeRecur(_T *u, _T *l, int *p);
		static bool decompose(_T *u, _T *l, int *p);

		template<int _BXWIDTH>
		static bool solveLyEqualsB(
			Matrix<_T, _WIDTH, _HEIGHT> *l,
			Matrix<_T, _BXWIDTH, _HEIGHT> *bx);

		template<int _BXWIDTH>
		static bool solveUxEqualsY(
			Matrix<_T, _WIDTH, _HEIGHT> *u,
			Matrix<_T, _BXWIDTH, _HEIGHT> *bx);

		template<int _BXWIDTH>
		static bool solve(
			const Matrix<_T, _WIDTH, _HEIGHT> &l, 
			const Matrix<_T, _WIDTH, _HEIGHT> &u,
			Matrix<_T, _BXWIDTH, _HEIGHT> *bx);
	};

	//==========================================================================
	// PRIVATE CLASS LUDecomposition::RowOperation
	//==========================================================================
	template<typename _T, int _SIZE>
	class RowOperation
	{
	public:
		static void multiply(_T *intoRow, const _T *row, const _T &factor);
		static void addRowTimesFactor(_T *intoRow, const _T *srcRow, const _T *addRow, const _T &timesFactor);
		static void swap(_T *row1, _T *row2);
	};

	//==========================================================================
	// PRIVATE CLASS LUDecomposition::RowOperation<_T, 0>
	//==========================================================================
	template<typename _T>
	class RowOperation<_T, 0>
	{
	public:
		static void multiply(_T *intoRow, const _T *row, const _T &factor);
		static void addRowTimesFactor(_T *intoRow, const _T *srcRow, const _T *addRow, const _T &timesFactor);
		static void swap(_T *row1, _T *row2);
	};

	//==========================================================================
	// PRIVATE CLASS LUDecomposition::LUSubDecomposition
	//==========================================================================
	template<typename _T, int _OFFSET, int _WIDTH>
	class LUSubDecomposition<_T, _OFFSET, _WIDTH, _OFFSET>
	{
	public:
		static bool decomposeRecur(_T *u, _T *l, int *p);
		static bool decomposeRecur(_T *u, _T *l);

		template<int _BXWIDTH>
		static bool solveUxEqualsY(Matrix<_T, _WIDTH, _OFFSET> *u, Matrix<_T, _BXWIDTH, _OFFSET> *bx);

		template<int _BXWIDTH>
		static bool solveLyEqualsB(Matrix<_T, _WIDTH, _OFFSET> *l, Matrix<_T, _BXWIDTH, _OFFSET> *bx);
	};
};


} // namespace seed


#include "src/LUDecomposition.inline.h"

#endif // __GEOMETRY_LUDECOMPOSITION__
