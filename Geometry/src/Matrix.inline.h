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
#ifndef __GEOMETRY_MATRIX_INLINE__
#define __GEOMETRY_MATRIX_INLINE__


//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "../Matrix.h"
#include <cstdio>
#include <cmath>
#include <cstring>
#include <sstream>

namespace seed {

//==============================================================================
//	CLASS Matrix
//==============================================================================
template<typename _T, int _COLS, int _ROWS>
TMatrix<_T, _COLS, _ROWS>::TMatrix()
{}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
TMatrix<_T, _COLS, _ROWS>::TMatrix(const _T *data)
{
	for (int i = 0; i < count(); ++i)
		element[i] = data[i];
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
TMatrix<_T, _COLS, _ROWS>::TMatrix(const _T allValue)
{
	for (int i = 0; i < count(); ++i)
		element[i] = allValue;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS> 
TMatrix<_T, _COLS, _ROWS>::TMatrix(const Matrix<_T, _COLS, _ROWS> &m)
{
	for (int i = 0; i < count(); ++i)
		element[i] = m.element[i];
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
const Matrix<_T, _COLS, _ROWS>& TMatrix<_T, _COLS, _ROWS>::fromPtr(const _T *data)
{
	return *reinterpret_cast<const MatrixType*>(data);
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
Matrix<_T, _COLS, _ROWS>& TMatrix<_T, _COLS, _ROWS>::fromPtr(_T *data)
{
	return *reinterpret_cast<Matrix<_T, _COLS, _ROWS>*>(data);
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
const Matrix<_T, _COLS, _ROWS>& TMatrix<_T, _COLS, _ROWS>::identity()
{
	static Matrix<_T, _COLS, _ROWS> sIdentityMatrix = zero();
	static bool hasIdentityMatrix = false;
	if (!hasIdentityMatrix)
	{
		if (_COLS < _ROWS)
		{
			for (int i = 0; i < _COLS; ++i)
				sIdentityMatrix[i][i] = 1;
		}
		else
		{
			for (int i = 0; i < _ROWS; ++i)
				sIdentityMatrix[i][i] = 1;
		}

		hasIdentityMatrix = true;
	}
	
	return sIdentityMatrix;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
const Matrix<_T, _COLS, _ROWS>& TMatrix<_T, _COLS, _ROWS>::zero()
{
	static MatrixType sZeroMatrix;
	static bool hasZeroMatrix = false;
	if (!hasZeroMatrix)
	{
		memset(sZeroMatrix.ptr(), 0, sZeroMatrix.size());
		hasZeroMatrix = true;
	}

	return sZeroMatrix;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
bool TMatrix<_T, _COLS, _ROWS>::operator == (const Matrix<_T, _COLS, _ROWS> &m) const
{
	return memcmp(element, m.element, size()) == 0;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
bool TMatrix<_T, _COLS, _ROWS>::operator != (const Matrix<_T, _COLS, _ROWS> &m) const
{
	return memcmp(element, m.element, size()) != 0;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
const _T* TMatrix<_T, _COLS, _ROWS>::operator [] (int r) const
{
	return &element[r*_COLS];
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
_T* TMatrix<_T, _COLS, _ROWS>::operator [] (int r)
{
	return &element[r*_COLS];
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
int TMatrix<_T, _COLS, _ROWS>::cols() const
{
	return _COLS;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
int TMatrix<_T, _COLS, _ROWS>::rows() const	
{
	return _ROWS;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
const _T* TMatrix<_T, _COLS, _ROWS>::ptr() const
{
	return element;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
_T* TMatrix<_T, _COLS, _ROWS>::ptr()
{
	return element;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
Matrix<_T, _COLS, _ROWS> TMatrix<_T, _COLS, _ROWS>::operator + (const TMatrix<_T, _COLS, _ROWS> &rhs) const
{
	MatrixType m;
	
	for (int i = 0; i < count(); ++i)
		m.element[i] = element[i] + rhs.element[i];

	return m;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
Matrix<_T, _COLS, _ROWS> TMatrix<_T, _COLS, _ROWS>::operator - (const TMatrix<_T, _COLS, _ROWS> &rhs) const
{
	Matrix<_T, _COLS, _ROWS> m;
	
	for (int i = 0; i < count(); ++i)
		m.element[i] = element[i] - rhs.element[i];

	return m;
}


//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS> template<int _RHSCOLS>
Matrix<_T, _RHSCOLS, _ROWS> TMatrix<_T, _COLS, _ROWS>::operator * (const TMatrix<_T, _RHSCOLS, _COLS> &rhs) const
{
	Matrix<_T, _RHSCOLS, _ROWS> m;

	int i, j, x;
    for (j = 0; j < _ROWS; ++j)
    {
    	for (i = 0; i < _RHSCOLS; ++i)
        {
			m[j][i] = element[j*_COLS] * rhs[0][i];
        	for (x = 1; x < _COLS; ++x)
        	{
				m[j][i] += element[j*_COLS + x] * rhs[x][i];
			}
		}
	}
    return m;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
Matrix<_T, _COLS, _ROWS> TMatrix<_T, _COLS, _ROWS>::operator * (const _T &rhs) const
{
	Matrix<_T, _COLS, _ROWS> m;
	int i;
	for (i = 0; i < count(); ++i)
		m.element[i] = element[i] * rhs;
	return m;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
Matrix<_T, _COLS, _ROWS> TMatrix<_T, _COLS, _ROWS>::operator / (const _T &rhs) const
{
	Matrix<_T, _COLS, _ROWS> m;

	float oneOverRhs = 1.0f / rhs;
	
	int i;
	for (i = 0; i < count(); ++i)
		m.element[i] = element[i] * oneOverRhs;

	return m;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
Matrix<_T, _ROWS, _COLS> TMatrix<_T, _COLS, _ROWS>::transposed() const
{
	Matrix<_T, _ROWS, _COLS> m;
	
	for (int j = 0; j < _ROWS; ++j)
		for (int i = 0; i < _COLS; ++i)
			m.element[i*_ROWS+j] = element[j*_COLS+i];
	 
	return m;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
std::string TMatrix<_T, _COLS, _ROWS>::serialize() const
{
	std::stringstream strstream;

	strstream << "{ ";

	for (int j = 0; j < _ROWS; ++j)
	{
		strstream << "{ ";
		for (int i = 0; i < _COLS; ++i)
		{
			strstream << element[j*_COLS+i];
			if (i < _COLS-1)	strstream << ", ";
		}
		strstream << " }";
		if (j < _ROWS-1)	strstream << ",";
	}
	strstream << " }";
	return strstream.str();
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
Matrix<_T, _COLS, _ROWS> TMatrix<_T, _COLS, _ROWS>::deSerialize(const std::string &str)
{
	char buf[2048];
	::strcpy(buf, str.c_str());
	Matrix<_T, _COLS, _ROWS> m = Matrix<_T, _COLS, _ROWS>::zero();

	char *value;
	value = ::strtok(buf, " \t\r\n{,}");

	int i = 0;
	while (value && i < _COLS*_ROWS)
	{
		double v;
		sscanf(value, "%lf", &v);
		m.element[i++] = v;
		value = ::strtok(NULL, " \t\r\n{,}");
	}

	return m;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
bool TMatrix<_T, _COLS, _ROWS>::hasNan() const
{
	for (int i = 0; i < count(); ++i)
	{
		if (std::isnan(element[i]))	
			return true;
	}
	
	return false;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
bool TMatrix<_T, _COLS, _ROWS>::hasInf() const
{
	for (int i = 0; i < count(); ++i)
	{
		if (std::isinf(element[i]))	
			return true;
	}
	
	return false;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
Matrix<_T, _COLS, _ROWS> operator * (int lhs, const Matrix<_T, _COLS, _ROWS> &m)
{
	return m*lhs;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
Matrix<_T, _COLS, _ROWS> operator * (float lhs, const Matrix<_T, _COLS, _ROWS> &m)
{
	return m*lhs;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
Matrix<_T, _COLS, _ROWS> operator * (double lhs, const Matrix<_T, _COLS, _ROWS> &m)
{
	return m*lhs;
}

//------------------------------------------------------------------------------
//
template<typename _T, int N>
static inline _T Determinant(const Matrix<_T, N, N> &m)
{
	// not the most efficient way, but should work for now...
	_T determinant = 0;
	int factor = 1;
	for (int i = 0; i < N; ++i)
	{
		_T coeff = m[0][i];
		Matrix<_T, N-1, N-1> subM;
		
		for (int x = 0; x < i; ++x)
			for (int y = 1; y < N; ++y)
				subM[y-1][x] = m[y][x];

		for (int x = i+1; x < N; ++x)
			for (int y = 1; y < N; ++y)
				subM[y-1][x-1] = m[y][x];


		determinant += coeff*factor*Determinant(subM);
		factor *= -1;
	}
	return determinant;
}

#ifndef WIN32

//------------------------------------------------------------------------------
//
template<typename _T>
static inline _T Determinant(const Matrix<_T, 1, 1> &m)
{
	return m[0][0];
}

#else

//------------------------------------------------------------------------------
//
template<>
static inline double Determinant(const Matrix<double, 1, 1> &m)
{
	return m[0][0];
}

//------------------------------------------------------------------------------
//
template<>
static inline float Determinant(const Matrix<float, 1, 1> &m)
{
	return m[0][0];
}

#endif

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
size_t TMatrix<_T, _COLS, _ROWS>::size() const
{
	return count()*sizeof(_T);
}
	
//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
int TMatrix<_T, _COLS, _ROWS>::count() const
{
	return _COLS*_ROWS;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
template <int _MW, int _MH>
Matrix<_T, _COLS, _ROWS> TMatrix<_T, _COLS, _ROWS>::subMatrix(int r, int c, const TMatrix<_T, _MW, _MH> &m)
{
	Matrix<_T, _COLS, _ROWS> sub;
	for (int j = 0; j < _ROWS; ++j)
		for (int i = 0; i < _COLS; ++i)
			sub[j][i] = m[r+j][c+i];

	return sub;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
template <int _MW, int _MH>
TMatrix<_T, _COLS, _ROWS>& TMatrix<_T, _COLS, _ROWS>::copy(int r, int c, const TMatrix<_T, _MW, _MH> &m)
{
	for (int j = 0; j < _MH && (j+r) < _ROWS; ++j)
		for (int i = 0; i < _MW && (i+c) < _COLS; ++i)
			element[(j+r)*_COLS+(i+c)] = m[j][i];

	return *this;
}


//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS> template<typename _U>
TMatrix<_T, _COLS, _ROWS>& TMatrix<_T, _COLS, _ROWS>::copy(const _U *data)
{
	for (int i = 0; i < count(); ++i)
		element[i] = data[i];
	return *this;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
TMatrix<_T, _COLS, _ROWS>& TMatrix<_T, _COLS, _ROWS>::copyRow(int index, const TMatrix<_T, _COLS, 1> &m)
{
	return copy(index, 0, m);
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
TMatrix<_T, _COLS, _ROWS>& TMatrix<_T, _COLS, _ROWS>::copyCol(int index, const TMatrix<_T, 1, _ROWS> &m)
{
	return copy(0, index, m);
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
Matrix<_T, _COLS, 1> TMatrix<_T, _COLS, _ROWS>::row(int index) const
{
	return Matrix<_T, _COLS, 1>::subMatrix(index, 0, *this);
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
Matrix<_T, 1, _ROWS> TMatrix<_T, _COLS, _ROWS>::col(int index) const
{
	return Matrix<_T, 1, _ROWS>::subMatrix(0, index, *this);
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
Matrix<_T, _COLS, _ROWS+1> TMatrix<_T, _COLS, _ROWS>::addBackRow(const Matrix<_T, _COLS, 1> &r ) const
{
	return addRow(_ROWS, r);
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
Matrix<_T, _COLS+1, _ROWS> TMatrix<_T, _COLS, _ROWS>::addBackCol(const Matrix<_T, 1, _ROWS> &c) const
{
	return addCol(_COLS, c);
}


//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
Matrix<_T, _COLS, _ROWS+1> TMatrix<_T, _COLS, _ROWS>::addFrontRow(const Matrix<_T, _COLS, 1> &r ) const
{
	return addRow(0, r);
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
Matrix<_T, _COLS+1, _ROWS> TMatrix<_T, _COLS, _ROWS>::addFrontCol(const Matrix<_T, 1, _ROWS> &c) const
{
	return addCol(0, c);
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
Matrix<_T, _COLS, _ROWS+1> TMatrix<_T, _COLS, _ROWS>::addRow(int index, const Matrix<_T, _COLS, 1> &r ) const
{
	Matrix<_T, _COLS, _ROWS+1> m;
	int i = 0, ri = 0;

	for (; i < index; ++i)	m.copyRow(ri++, row(i));
	m.copyRow(ri++, r);
	for (; i < index; ++i)	m.copyRow(ri++, row(i));

	return m;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
Matrix<_T, _COLS+1, _ROWS> TMatrix<_T, _COLS, _ROWS>::addCol(int index, const Matrix<_T, 1, _ROWS> &c) const
{
	Matrix<_T, _COLS+1, _ROWS> m;
	int i = 0, ci = 0;

	for (; i < index; ++i)	m.copyCol(ci++, col(i));
	m.copyCol(ci++, c);
	for (; i < index; ++i)	m.copyCol(ci++, col(i));

	return m;
}



//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
Matrix<_T, _COLS, _ROWS-1> TMatrix<_T, _COLS, _ROWS>::removeBackRow() const
{
	return Matrix<_T, _COLS, _ROWS-1>::subMatrix(0, 0, *this);
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
Matrix<_T, _COLS-1, _ROWS> TMatrix<_T, _COLS, _ROWS>::removeBackCol() const
{
	return Matrix<_T, _COLS-1, _ROWS>::subMatrix(0, 0, *this);
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
Matrix<_T, _COLS, _ROWS-1> TMatrix<_T, _COLS, _ROWS>::removeFrontRow() const
{
	return Matrix<_T, _COLS, _ROWS-1>::subMatrix(1, 0, *this);
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
Matrix<_T, _COLS-1, _ROWS> TMatrix<_T, _COLS, _ROWS>::removeFrontCol() const
{
	return Matrix<_T, _COLS-1, _ROWS>::subMatrix(0, 1, *this);
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
Matrix<_T, _COLS, _ROWS-1> TMatrix<_T, _COLS, _ROWS>::removeRow(int index ) const
{
	Matrix<_T, _COLS, _ROWS-1> m;
	int i = 0, ri = 0;

	for (; i < index; ++i)	m.copyRow(ri++, row(i));
	++i; // skip one row
	for (; i < index; ++i)	m.copyRow(ri++, row(i));

	return m;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
Matrix<_T, _COLS-1, _ROWS> TMatrix<_T, _COLS, _ROWS>::removeCol(int index) const
{
	Matrix<_T, _COLS-1, _ROWS> m;
	int i = 0, ci = 0;

	for (; i < index; ++i)	m.copyCol(ci++, col(i));
	++i; // skip one column
	for (; i < index; ++i)	m.copyCol(ci++, col(i));

	return m;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS> template<typename _U>
TMatrix<_T, _COLS, _ROWS>& TMatrix<_T, _COLS, _ROWS>::operator = (const TMatrix<_U, _COLS, _ROWS> &m)
{
	for (int i = 0; i < count(); ++i)
		element[i] = m.element[i];

	return *this;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
TMatrix<_T, _COLS, _ROWS>& TMatrix<_T, _COLS, _ROWS>::operator += (const TMatrix<_T, _COLS, _ROWS> &rhs)
{
	for (int i = 0; i < count(); ++i)
		element[i] += rhs.element[i];

	return *this;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
TMatrix<_T, _COLS, _ROWS>& TMatrix<_T, _COLS, _ROWS>::operator -= (const TMatrix<_T, _COLS, _ROWS> &rhs)
{
	for (int i = 0; i < count(); ++i)
		element[i] -= rhs.element[i];

	return *this;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
TMatrix<_T, _COLS, _ROWS>& TMatrix<_T, _COLS, _ROWS>::operator - ()
{
	for (int i = 0; i < count(); ++i)
		element[i] = -element[i];

	return *this;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
TMatrix<_T, _COLS, _ROWS>& TMatrix<_T, _COLS, _ROWS>::operator *= (const _T &rhs)
{
	int i;
	for (i = 0; i < count(); ++i)
		element[i] *= rhs;
	return *this;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
TMatrix<_T, _COLS, _ROWS>& TMatrix<_T, _COLS, _ROWS>::operator /= (const _T &rhs)
{
	float oneOverRhs = 1.0f / rhs;
	
	int i;
	for (i = 0; i < count(); ++i)
		element[i] *= oneOverRhs;

	return *this;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
TMatrix<_T, _COLS, _ROWS>& TMatrix<_T, _COLS, _ROWS>::operator *= (const TMatrix<_T, _ROWS, _COLS> &rhs)
{
	(*this) = (*this) * rhs;
	return *this;
}

//------------------------------------------------------------------------------
//
template<typename _T, int _SIZE>
void Matrix<_T, _SIZE, _SIZE>::transpose()
{
	*this = _Super::transposed();
}

//------------------------------------------------------------------------------
//
template<typename _T>
void Matrix<_T, 1, 1>::transpose()
{
	*this = _Super::transposed();
}

//------------------------------------------------------------------------------
//
template<typename _T, int _SIZE>
void Matrix<_T, _SIZE, _SIZE>::invert()
{
	*this = inversed();
}


//------------------------------------------------------------------------------
//
template<typename _T>
void Matrix<_T, 1, 1>::invert()
{
	*this = inversed();
}

//------------------------------------------------------------------------------
//
template<typename _T, int _SIZE>
Matrix<_T, _SIZE, _SIZE> Matrix<_T, _SIZE, _SIZE>::inversed() const
{
	Matrix<_T, _SIZE, _SIZE> inv;
	MatrixInverse<_T, _SIZE, _SIZE>::invert(*this, &inv);
	return inv;
}

//------------------------------------------------------------------------------
//
template<typename _T>
Matrix<_T, 1, 1> Matrix<_T, 1, 1>::inversed() const
{
	Matrix<_T, 1, 1> inv;
	MatrixInverse<_T, 1, 1>::invert(*this, &inv);
	return inv;
}


template<typename _T, int _SIZE>
_T Matrix<_T, _SIZE, _SIZE>::determinant() const
{
	return MatrixDeterminant<_T, _SIZE, _SIZE>::determinant(*this);
}

template<typename _T>
_T Matrix<_T, 1, 1>::determinant() const
{
	return MatrixDeterminant<_T, 1, 1>::determinant(*this);
}

//------------------------------------------------------------------------------
//
template<typename _T, int _COLS, int _ROWS>
Matrix<_T, _COLS, _ROWS> TMatrix<_T, _COLS, _ROWS>::fromPivot(const Matrix<int, 1, _ROWS> &pivot)
{
	MatrixType mat = MatrixType::zero();
	
	for (int i = 0; i < _ROWS; ++i)
	{
		mat[i][pivot[i][0]] = 1;
	}
		
	return mat;
}

} // namespace seed


#endif // __GEOMETRY_MATRIX_INLINE__
