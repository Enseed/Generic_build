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
#ifndef __GEOMETRY_MATRIX__
#define __GEOMETRY_MATRIX__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include <string>

#ifdef WIN32
// Unfortunately, VisualC++ complains if we don't have the full declaration...
#include "LUMatrixInverse.h"
#include "LUMatrixDeterminant.h"
#endif

namespace seed {

//==============================================================================
//	FORWARD DECLARATIONS
//==============================================================================
template<class _T, int _COLS, int _ROWS> class Matrix;

//==============================================================================
//	MATRIX INVERSE
//==============================================================================

//-----------------------------------------------------------------------------
// We don't want to refer directly to the code that inverts a matrix since
// it will pull out a few other files just for that.  By default, inverting
// a matrix uses the MatrixUtils class which uses the LUDecomposition.
// Unless you call Matrix.invert() or Matrix.inversed(), you will not need to
// even include those files.  But if you do, you'll have to include MatrixUtils
// in your .cpp file.

#ifndef WIN32
class LUMatrixInverse;
class LUMatrixDeterminant;
#endif

template<class _INVERTER=LUMatrixInverse>
class DefaultMatrixInverter
{
public:
	template<typename _T, int _COLS, int _ROWS>
	static bool invert(const Matrix<_T, _COLS, _ROWS> &m, Matrix<_T, _COLS, _ROWS> *outInverse)
	{	return _INVERTER::invert(m, outInverse);	}
};

template<class _DETERMINANT=LUMatrixDeterminant>
class DefaultMatrixDeterminant
{
public:
	template<typename _T, int _COLS, int _ROWS>
	static _T determinant(const Matrix<_T, _COLS, _ROWS> &m)
	{	return _DETERMINANT::determinant(m);	}
};

//-----------------------------------------------------------------------------
// You might want to override the default helpers.  For instance, if you'd
// like to use a custom inverter for a given matrix size, you could simply
// declare a special case for 1x1 matrices:
//
// template<typename _T>
// bool MatrixHelper<_T, 1, 1>::invert(const Matrix<_T, _COLS, _ROWS> &m, Matrix<_T, _COLS, _ROWS> *outInverse)
// {
//     *outInverse = m;
//     return true;
// }
//
template<typename _T, int _COLS, int _ROWS>
class MatrixInverse
{
public:
	static bool invert(const Matrix<_T, _COLS, _ROWS> &m, Matrix<_T, _COLS, _ROWS> *outInverse)
	{
		return DefaultMatrixInverter<>::invert(m, outInverse);
	}
};

template<typename _T, int _COLS, int _ROWS>
class MatrixDeterminant
{
public:
	static _T determinant(const Matrix<_T, _COLS, _ROWS> &m)
	{
		return DefaultMatrixDeterminant<>::determinant(m);
	}
};



//==============================================================================
//	CLASS Matrix
//==============================================================================
template<class _T, int _COLS, int _ROWS>
class TMatrix
{
public:
	typedef _T Type;
	typedef Matrix<_T, _COLS, _ROWS> MatrixType;

public:
	TMatrix();
	explicit TMatrix(const _T *data);
	explicit TMatrix(const _T allValue);
	TMatrix(const MatrixType &m);

	static const MatrixType& fromPtr(const _T *data);
	static MatrixType& fromPtr(_T *data);
	static const MatrixType& identity();
	static const MatrixType& zero();
	
	// A pivot is a matrix that contains the index where a 1 should be, for
	// example, {1, 2, 3} is a pivot matrix for a 3x3 identity matrix.
	// {3, 2, 2} however, would result in the following matrix:
	//
	//  {0, 0, 1}
	//  {0, 1, 0}
	//  {0, 1, 0}
	//
	static Matrix<_T, _COLS, _ROWS> fromPivot(const Matrix<int, 1, _ROWS> &pivotMatrix);

	template <int _MW, int _MH>
	static MatrixType subMatrix(int r, int c, const TMatrix<_T, _MW, _MH> &m);

	bool operator == (const MatrixType &m) const;
	bool operator != (const MatrixType &m) const;

	const _T* operator [] (int row) const;
	_T* operator [] (int row);

	int cols() const;
	int rows() const;

	const _T* ptr() const;
	_T* ptr();

	Matrix<_T, _COLS, _ROWS> operator + (const TMatrix<_T, _COLS, _ROWS> &rhs) const;
	Matrix<_T, _COLS, _ROWS> operator - (const TMatrix<_T, _COLS, _ROWS> &rhs) const;

	template<int _RHSWIDTH>
	Matrix<_T, _RHSWIDTH, _ROWS> operator * (const TMatrix<_T, _RHSWIDTH, _COLS> &rhs) const;

	Matrix<_T, _COLS, _ROWS> operator * (const _T &rhs) const;
	Matrix<_T, _COLS, _ROWS> operator / (const _T &rhs) const;
	
	Matrix<_T, _ROWS, _COLS> transposed() const;

	TMatrix& operator /= (const _T &rhs);
	TMatrix& operator *= (const _T &rhs);

	TMatrix& operator *= (const TMatrix<_T, _ROWS, _COLS> &rhs);

	bool hasNan() const;
	bool hasInf() const;
	
	std::string serialize() const;
	static MatrixType deSerialize(const std::string &str);

	template<int _MW, int _MH>
	TMatrix& copy(int r, int c, const TMatrix<_T, _MW, _MH> &m);

	TMatrix& copyRow(int index, const TMatrix<_T, _COLS, 1> &m);
	TMatrix& copyCol(int index, const TMatrix<_T, 1, _ROWS> &m);

	Matrix<_T, _COLS, 1> row(int index) const;
	Matrix<_T, 1, _ROWS> col(int index) const;

	Matrix<_T, _COLS, _ROWS+1> addBackRow(const Matrix<_T, _COLS, 1> &r ) const;
	Matrix<_T, _COLS+1, _ROWS> addBackCol(const Matrix<_T, 1, _ROWS> &c) const;

	Matrix<_T, _COLS, _ROWS+1> addFrontRow(const Matrix<_T, _COLS, 1> &r ) const;
	Matrix<_T, _COLS+1, _ROWS> addFrontCol(const Matrix<_T, 1, _ROWS> &c) const;

	Matrix<_T, _COLS, _ROWS+1> addRow(int index, const Matrix<_T, _COLS, 1> &r ) const;
	Matrix<_T, _COLS+1, _ROWS> addCol(int index, const Matrix<_T, 1, _ROWS> &c) const;

	Matrix<_T, _COLS-1, _ROWS> removeBackCol() const;
	Matrix<_T, _COLS-1, _ROWS> removeFrontCol() const;
	Matrix<_T, _COLS-1, _ROWS> removeCol(int index) const;

	Matrix<_T, _COLS, _ROWS-1> removeBackRow() const;
	Matrix<_T, _COLS, _ROWS-1> removeFrontRow() const;
	Matrix<_T, _COLS, _ROWS-1> removeRow(int index) const;

	template<class _U>
	TMatrix& copy(const _U *data);

	template<class _U>
	TMatrix& operator = (const TMatrix<_U, _COLS, _ROWS> &m);

	TMatrix& operator += (const TMatrix &rhs);
	TMatrix& operator -= (const TMatrix &rhs);
	TMatrix& operator - ();

public:
	_T element[_COLS*_ROWS];

protected:
	size_t size() const;
	int count() const;
};

template<class _T, int _COLS, int _ROWS>
class Matrix: public TMatrix<_T, _COLS, _ROWS>
{
private:
	typedef TMatrix<_T, _COLS, _ROWS> _Super;

public:
	typedef _T Type;

public:
	Matrix() : _Super() {}
	explicit Matrix(const _T *data) : _Super(data) {}
	explicit Matrix(const _T allValue) : _Super(allValue) {}
	Matrix(const Matrix &m) : _Super(m) {}

	template<class _U>
	Matrix& operator = (const Matrix<_U, _COLS, _ROWS> &m)
	{	_Super::operator=(m);	return *this;	}

	template<class _U>
	Matrix& copy(const _U *data)
	{	_Super::copy(data);		return *this;	}

	Matrix& operator += (const Matrix &rhs)
	{ _Super::operator+=(rhs); return *this; }

	Matrix& operator -= (const Matrix &rhs)
	{ _Super::operator-=(rhs); return *this; }
	
	Matrix& operator - ()
	{ _Super::operator-(); return *this; }
	
	using _Super::operator-;
	
	template<int _MW, int _MH>
	Matrix& copy(int r, int c, const Matrix<_T, _MW, _MH> &m);

	Matrix& operator /= (const _T &rhs)
	{ _Super::operator/=(rhs); return *this; }

	Matrix& operator *= (const _T &rhs)
	{ _Super::operator*=(rhs); return *this; }
	
	Matrix& operator *= (const Matrix &rhs)
	{ _Super::operator*=(rhs); return *this; }

	Matrix& copyRow(int index, const Matrix<_T, _COLS, 1> &m)
	{	_Super::copyRow(index, m); return *this; }

	Matrix& copyCol(int index, const Matrix<_T, 1, _ROWS> &m)
	{	_Super::copyCol(index, m); return *this; }
};

template<class _T, int _SIZE>
class Matrix<_T, _SIZE, _SIZE>: public TMatrix<_T, _SIZE, _SIZE>
{
private:
	typedef TMatrix<_T, _SIZE, _SIZE> _Super;

public:
	typedef _T Type;

public:
	Matrix() : _Super() {}
	explicit Matrix(const _T *data) : _Super(data) {}
	explicit Matrix(const _T allValue) : _Super(allValue) {}
	Matrix(const Matrix &m) : _Super(m) {}

	template<class _U>
	Matrix& operator = (const Matrix<_U, _SIZE, _SIZE> &m)
	{	_Super::operator=(m);	return *this;	}

	template<class _U>
	Matrix& copy(const _U *data)
	{	_Super::copy(data);		return *this;	}

	Matrix& operator += (const Matrix &rhs)
	{ _Super::operator+=(rhs); return *this; }

	Matrix& operator -= (const Matrix &rhs)
	{ _Super::operator-=(rhs); return *this; }
	
	Matrix& operator - ()
	{ _Super::operator-(); return *this; }
	
	using _Super::operator-;
	
	template<int _MW, int _MH>
	Matrix& copy(int r, int c, const Matrix<_T, _MW, _MH> &m);

	Matrix& operator /= (const _T &rhs)
	{ _Super::operator/=(rhs); return *this; }

	Matrix& operator *= (const _T &rhs)
	{ _Super::operator*=(rhs); return *this; }
	
	Matrix& operator *= (const Matrix &rhs)
	{ _Super::operator*=(rhs); return *this; }

	Matrix& copyRow(int index, const Matrix<_T, _SIZE, 1> &m)
	{	_Super::copyRow(index, m); return *this; }

	Matrix& copyCol(int index, const Matrix<_T, 1, _SIZE> &m)
	{	_Super::copyCol(index, m); return *this; }

public:
	// SPECIAL CASES FOR NxN SQUARE MATRICES
	void transpose();
	void invert();

	// We call it inversed rather than simply inverse to avoid the confusion
	// with invert().  Somebody guessing the name of the method could actually
	// end up calling inverse() thinking it's doing what invert() does.
	Matrix inversed() const;
	
	_T determinant() const;
};

template<class _T, int _SIZE> class Point;

template<class _T>
class Matrix<_T, 1, 1>: public TMatrix<_T, 1, 1>
{
private:
	typedef TMatrix<_T, 1, 1> _Super;

public:
	typedef _T Type;

public:
	Matrix() : _Super() {}
	explicit Matrix(const _T *data) : _Super(data) {}
	explicit Matrix(const _T allValue) : _Super(allValue) {}
	Matrix(const Matrix &m) : _Super(m) {}

	template<class _U>
	Matrix& operator = (const Matrix<_U, 1, 1> &m)
	{	_Super::operator=(m);	return *this;	}

	template<class _U>
	Matrix& copy(const _U *data)
	{	_Super::copy(data);		return *this;	}

	Matrix& operator += (const Matrix &rhs)
	{ _Super::operator+=(rhs); return *this; }

	Matrix& operator -= (const Matrix &rhs)
	{ _Super::operator-=(rhs); return *this; }
	
	Matrix& operator - ()
	{ _Super::operator-(); return *this; }
	
	using _Super::operator-;
	
	template<int _MW, int _MH>
	Matrix& copy(int r, int c, const Matrix<_T, _MW, _MH> &m);

	Matrix& operator /= (const _T &rhs)
	{ _Super::operator/=(rhs); return *this; }

	Matrix& operator *= (const _T &rhs)
	{ _Super::operator*=(rhs); return *this; }
	
	Matrix& operator *= (const Matrix &rhs)
	{ _Super::operator*=(rhs); return *this; }

	Matrix& copyRow(int index, const Matrix<_T, 1, 1> &m)
	{	_Super::copyRow(index, m); return *this; }

	Matrix& copyCol(int index, const Matrix<_T, 1, 1> &m)
	{	_Super::copyCol(index, m); return *this; }

public:
	// SPECIAL CASES FOR NxN SQUARE MATRICES
	void transpose();
	void invert();

	// We call it inversed rather than simply inverse to avoid the confusion
	// with invert().  Somebody guessing the name of the method could actually
	// end up calling inverse() thinking it's doing what invert() does.
	Matrix inversed() const;
	
	_T determinant() const;


	const Point<_T, 1>& asPoint() const { return *reinterpret_cast<const Point<_T, 1>*>(this); }
	Point<_T, 1>& asPoint() { return *reinterpret_cast<Point<_T, 1>*>(this); }
};

template<class _T, int _ROWS>
class Matrix<_T, 1, _ROWS>: public TMatrix<_T, 1, _ROWS>
{
private:
	typedef TMatrix<_T, 1, _ROWS> _Super;

public:
	typedef _T Type;

public:
	Matrix() : _Super() {}
	explicit Matrix(const _T *data) : _Super(data) {}
	explicit Matrix(const _T allValue) : _Super(allValue) {}
	Matrix(const Matrix &m) : _Super(m) {}

	template<class _U>
	Matrix& operator = (const Matrix<_U, 1, _ROWS> &m)
	{	_Super::operator=(m);	return *this;	}

	template<class _U>
	Matrix& copy(const _U *data)
	{	_Super::copy(data);		return *this;	}

	Matrix& operator += (const Matrix &rhs)
	{ _Super::operator+=(rhs); return *this; }

	Matrix& operator -= (const Matrix &rhs)
	{ _Super::operator-=(rhs); return *this; }
	
	Matrix& operator - ()
	{ _Super::operator-(); return *this; }
	
	using _Super::operator-;
	
	template<int _MW, int _MH>
	Matrix& copy(int r, int c, const Matrix<_T, _MW, _MH> &m);

	Matrix& operator /= (const _T &rhs)
	{ _Super::operator/=(rhs); return *this; }

	Matrix& operator *= (const _T &rhs)
	{ _Super::operator*=(rhs); return *this; }
	
	Matrix& operator *= (const Matrix &rhs)
	{ _Super::operator*=(rhs); return *this; }

	Matrix& copyRow(int index, const Matrix<_T, 1, 1> &m)
	{	_Super::copyRow(index, m); return *this; }

	Matrix& copyCol(int index, const Matrix<_T, 1, _ROWS> &m)
	{	_Super::copyCol(index, m); return *this; }

	// SPECIAL CASES FOR COLS==1
	const Point<_T, _ROWS>& asPoint() const { return *reinterpret_cast<const Point<_T, _ROWS>*>(this); }
	Point<_T, _ROWS>& asPoint() { return *reinterpret_cast<Point<_T, _ROWS>*>(this); }
};

template<class _T, int _COLS>
class Matrix<_T, _COLS, 1>: public TMatrix<_T, _COLS, 1>
{
private:
	typedef TMatrix<_T, _COLS, 1> _Super;

public:
	typedef _T Type;

public:
	Matrix() : _Super() {}
	explicit Matrix(const _T *data) : _Super(data) {}
	explicit Matrix(const _T allValue) : _Super(allValue) {}
	Matrix(const Matrix &m) : _Super(m) {}

	template<class _U>
	Matrix& operator = (const Matrix<_U, _COLS, 1> &m)
	{	_Super::operator=(m);	return *this;	}

	template<class _U>
	Matrix& copy(const _U *data)
	{	_Super::copy(data);		return *this;	}

	Matrix& operator += (const Matrix &rhs)
	{ _Super::operator+=(rhs); return *this; }

	Matrix& operator -= (const Matrix &rhs)
	{ _Super::operator-=(rhs); return *this; }
	
	Matrix& operator - ()
	{ _Super::operator-(); return *this; }
	
	using _Super::operator-;
	
	template<int _MW, int _MH>
	Matrix& copy(int r, int c, const Matrix<_T, _MW, _MH> &m);

	Matrix& operator /= (const _T &rhs)
	{ _Super::operator/=(rhs); return *this; }

	Matrix& operator *= (const _T &rhs)
	{ _Super::operator*=(rhs); return *this; }
	
	Matrix& operator *= (const Matrix &rhs)
	{ _Super::operator*=(rhs); return *this; }

	Matrix& copyRow(int index, const Matrix<_T, _COLS, 1> &m)
	{	_Super::copyRow(index, m); return *this; }

	Matrix& copyCol(int index, const Matrix<_T, 1, 1> &m)
	{	_Super::copyCol(index, m); return *this; }

	// SPECIAL CASES FOR ROWS==1
	const Point<_T, _COLS>& asPoint() const { return *reinterpret_cast<const Point<_T, _COLS>*>(this); }
	Point<_T, _COLS>& asPoint() { return *reinterpret_cast<Point<_T, _COLS>*>(this); }
};



typedef Matrix<float, 0, 0> Matrix0f;
typedef Matrix<float, 1, 1> Matrix1f;
typedef Matrix<float, 2, 2> Matrix2f;
typedef Matrix<float, 3, 3> Matrix3f;
typedef Matrix<float, 4, 4> Matrix4f;
typedef Matrix<float, 5, 5> Matrix5f;
typedef Matrix<float, 6, 6> Matrix6f;
typedef Matrix<float, 7, 7> Matrix7f;
typedef Matrix<float, 8, 8> Matrix8f;
typedef Matrix<float, 9, 9> Matrix9f;

typedef Matrix<double, 0, 0> Matrix0d;
typedef Matrix<double, 1, 1> Matrix1d;
typedef Matrix<double, 2, 2> Matrix2d;
typedef Matrix<double, 3, 3> Matrix3d;
typedef Matrix<double, 4, 4> Matrix4d;
typedef Matrix<double, 5, 5> Matrix5d;
typedef Matrix<double, 6, 6> Matrix6d;
typedef Matrix<double, 7, 7> Matrix7d;
typedef Matrix<double, 8, 8> Matrix8d;
typedef Matrix<double, 9, 9> Matrix9d;

typedef Matrix<float, 0, 1> MatrixRow0f;
typedef Matrix<float, 1, 1> MatrixRow1f;
typedef Matrix<float, 2, 1> MatrixRow2f;
typedef Matrix<float, 3, 1> MatrixRow3f;
typedef Matrix<float, 4, 1> MatrixRow4f;
typedef Matrix<float, 5, 1> MatrixRow5f;
typedef Matrix<float, 6, 1> MatrixRow6f;
typedef Matrix<float, 7, 1> MatrixRow7f;
typedef Matrix<float, 8, 1> MatrixRow8f;
typedef Matrix<float, 9, 1> MatrixRow9f;

typedef Matrix<float, 1, 0> MatrixCol0f;
typedef Matrix<float, 1, 1> MatrixCol1f;
typedef Matrix<float, 1, 2> MatrixCol2f;
typedef Matrix<float, 1, 3> MatrixCol3f;
typedef Matrix<float, 1, 4> MatrixCol4f;
typedef Matrix<float, 1, 5> MatrixCol5f;
typedef Matrix<float, 1, 6> MatrixCol6f;
typedef Matrix<float, 1, 7> MatrixCol7f;
typedef Matrix<float, 1, 8> MatrixCol8f;
typedef Matrix<float, 1, 9> MatrixCol9f;

typedef Matrix<double, 0, 1> MatrixRow0d;
typedef Matrix<double, 1, 1> MatrixRow1d;
typedef Matrix<double, 2, 1> MatrixRow2d;
typedef Matrix<double, 3, 1> MatrixRow3d;
typedef Matrix<double, 4, 1> MatrixRow4d;
typedef Matrix<double, 5, 1> MatrixRow5d;
typedef Matrix<double, 6, 1> MatrixRow6d;
typedef Matrix<double, 7, 1> MatrixRow7d;
typedef Matrix<double, 8, 1> MatrixRow8d;
typedef Matrix<double, 9, 1> MatrixRow9d;

typedef Matrix<double, 1, 0> MatrixCol0d;
typedef Matrix<double, 1, 1> MatrixCol1d;
typedef Matrix<double, 1, 2> MatrixCol2d;
typedef Matrix<double, 1, 3> MatrixCol3d;
typedef Matrix<double, 1, 4> MatrixCol4d;
typedef Matrix<double, 1, 5> MatrixCol5d;
typedef Matrix<double, 1, 6> MatrixCol6d;
typedef Matrix<double, 1, 7> MatrixCol7d;
typedef Matrix<double, 1, 8> MatrixCol8d;
typedef Matrix<double, 1, 9> MatrixCol9d;

} // namespace seed


#include "src/Matrix.inline.h"

#endif // __GEOMETRY_MATRIX__
