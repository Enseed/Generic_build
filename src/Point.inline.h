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
#ifndef __GEOMETRY_POINT_INLINE__
#define __GEOMETRY_POINT_INLINE__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "../Point.h"
#include <string>

namespace seed {

//==============================================================================
//	CLASS Point
//==============================================================================

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
int Point<T, SIZE>::size()
{
	return SIZE;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
Point<T, SIZE>::Point()
{}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
Point<T, SIZE>::Point(const T *ptData)
{
	memcpy(coords, ptData, sizeof(T)*SIZE);
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
Point<T, SIZE>::Point(const T value)
{
	for (int i = 0; i < SIZE; ++i)
		coords[i] = value;
}
	
//------------------------------------------------------------------------------
//
template<class T, int SIZE>
Point<T, SIZE>::Point(const Matrix<T, 1, SIZE> &rhs)
{
	memcpy(coords, &rhs, sizeof(T)*SIZE);
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
Point<T, SIZE>::Point(const Point<T, SIZE> &rhs)
{
	memcpy(coords, rhs.coords, sizeof(T)*SIZE);
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
Point<T, SIZE>& Point<T, SIZE>::operator = (const Matrix<T, 1, SIZE> &rhs)
{
	memcpy(coords, &rhs, sizeof(T)*SIZE);
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
Point<T, SIZE>& Point<T, SIZE>::operator = (const Point<T, SIZE> &rhs)
{
	memcpy(coords, rhs.coords, sizeof(T)*SIZE);
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
bool Point<T, SIZE>::operator == (const Point<T, SIZE> &rhs) const
{
	return memcmp(coords, rhs.coords, sizeof(T)*SIZE) == 0;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
bool Point<T, SIZE>::operator != (const Point<T, SIZE> &rhs) const
{
	return memcmp(coords, rhs.coords, sizeof(T)*SIZE) != 0;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
bool Point<T, SIZE>::operator < (const Point<T, SIZE> &rhs) const
{
	for (int i = 0; i < SIZE; ++i)
	{
		if ((*this)[i] < rhs[i])		return true;
		else if ((*this)[i] > rhs[i])	return false;
	}
	return false;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
bool Point<T, SIZE>::operator <= (const Point<T, SIZE> &rhs) const
{
	for (int i = 0; i < SIZE; ++i)
	{
		if ((*this)[i] < rhs[i])		return true;
		else if ((*this)[i] > rhs[i])	return false;
	}
	return true;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
bool Point<T, SIZE>::operator > (const Point<T, SIZE> &rhs) const
{
	for (int i = 0; i < SIZE; ++i)
	{
		if ((*this)[i] > rhs[i])		return true;
		else if ((*this)[i] < rhs[i])	return false;
	}
	return false;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
bool Point<T, SIZE>::operator >= (const Point<T, SIZE> &rhs) const
{
	for (int i = 0; i < SIZE; ++i)
	{
		if ((*this)[i] > rhs[i])		return true;
		else if ((*this)[i] < rhs[i])	return false;
	}
	return true;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
const T& Point<T, SIZE>::operator [] (int index) const
{
	return coords[index];
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
T& Point<T, SIZE>::operator [] (int index)
{
	return coords[index];
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
T* Point<T, SIZE>::ptr()
{
	return reinterpret_cast<T*>(this);
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
const T* Point<T, SIZE>::ptr() const
{
	return reinterpret_cast<const T*>(this);
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
Point<T, SIZE> Point<T, SIZE>::operator + (const Point<T, SIZE> &rhs) const
{
	Point<T, SIZE> pt;
	for (int i = 0; i < SIZE; ++i) pt[i] = coords[i] + rhs.coords[i];
	return pt;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
Point<T, SIZE> Point<T, SIZE>::operator - (const Point<T, SIZE> &rhs) const
{
	Point<T, SIZE> pt;
	for (int i = 0; i < SIZE; ++i) pt[i] = coords[i] - rhs.coords[i];
	return pt;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
Matrix<T, 1, SIZE>& Point<T, SIZE>::asMatrix()
{
	return *reinterpret_cast<Matrix<T, 1, SIZE>*>(this);
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
const Matrix<T, 1, SIZE>& Point<T, SIZE>::asMatrix() const
{
	return *reinterpret_cast<const Matrix<T, 1, SIZE>*>(this);
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
const Matrix<T, SIZE, 1>& Point<T, SIZE>::asTMatrix() const
{
	return *reinterpret_cast<const Matrix<T, SIZE, 1>*>(this);
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
Matrix<T, SIZE, 1>& Point<T, SIZE>::asTMatrix()
{
	return *reinterpret_cast<Matrix<T, SIZE, 1>*>(this);
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
T Point<T, SIZE>::operator * (const Point &rhs) const
{
	T v = 0;
	for (int i = 0; i < SIZE; ++i)
		v += (*this)[i]*rhs[i];

	return v;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE> template<class U>
Point<T, SIZE> Point<T, SIZE>::operator * (const U &rhs) const
{
	Point<T, SIZE> pt;
	for (int i = 0; i < SIZE; ++i) pt[i] = coords[i] * rhs;
	return pt;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE> template<class U>
Point<T, SIZE> Point<T, SIZE>::operator / (const U &rhs) const
{
	Point<T, SIZE> pt;
	for (int i = 0; i < SIZE; ++i) pt[i] = coords[i] / rhs;
	return pt;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
Point<T, SIZE>& Point<T, SIZE>::operator += (const Point &rhs)
{
	for (int i = 0; i < SIZE; ++i) coords[i] += rhs.coords[i];
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
Point<T, SIZE>& Point<T, SIZE>::operator -= (const Point &rhs)
{
	for (int i = 0; i < SIZE; ++i) coords[i] -= rhs.coords[i];
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE> template<class U>
Point<T, SIZE>& Point<T, SIZE>::operator *= (const U &rhs)
{
	for (int i = 0; i < SIZE; ++i) coords[i] -= rhs;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE> template<class U>
Point<T, SIZE>& Point<T, SIZE>::operator /= (const U &rhs)
{
	for (int i = 0; i < SIZE; ++i) coords[i] /= rhs;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
Point<T, SIZE> Point<T, SIZE>::operator - () const
{
	Point<T, SIZE> retVal;
	for (int i = 0; i < SIZE; ++i) retVal.coords[i] = -coords[i];
	return retVal;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
void Point<T, SIZE>::setLength(double aLength)
{
	*this *= aLength / length();
}


//------------------------------------------------------------------------------
//
template<class T, int SIZE>
double Point<T, SIZE>::length() const
{
	return sqrt(length2());
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
T Point<T, SIZE>::length2() const
{
	T len2 = 0;
	for (int i = 0; i < SIZE; ++i)
		len2 += (*this)[i]*(*this)[i];
	
	return len2;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
std::string  Point<T, SIZE>::serialize() const
{
	std::string str = "";
	char buf[2048];

	str += "{ ";
	for (int i = 0; i < size(); ++i)
	{
		sprintf(buf, "%.10f", (*this)[i]); str += buf;
		if (i < size()-1)	str += ", ";
	}
	str += " }";
	return str;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE>
Point<T, SIZE> Point<T, SIZE>::deSerialize(const std::string &str)
{
	char buf[2048];
	strcpy(buf, str.c_str());
	Point<T, SIZE> p(T(0));

	char *value;
	value = strtok(buf, " \t\r\n{,}");

	int i = 0;
	while (value && i < size())
	{
		double v;
		sscanf(value, "%lf", &v);
		p[i++] = v;
		value = strtok(NULL, " \t\r\n{,}");
	}

	return p;
}

//------------------------------------------------------------------------------
//
template<class T, int SIZE> template<class U>
Point<U, SIZE> Point<T, SIZE>::cast() const
{
	Point<U, SIZE> pt;
	for (int i = 0; i < SIZE; ++i)
		pt.coords[i] = static_cast<U>(coords[i]);

	return pt;
}

//------------------------------------------------------------------------------
//
template<class U, class T, int SIZE>
static inline Point<T, SIZE> operator * (const U &lhs, const Point<T, SIZE> &rhs)
{
	return rhs * lhs;
}


} // namespace seed


#endif // __GEOMETRY_POINT_INLINE__
