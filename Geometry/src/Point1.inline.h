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
#ifndef __GEOMETRY_POINT1_INLINE__
#define __GEOMETRY_POINT1_INLINE__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "../Point1.h"
#include <cmath>
#include <cstring>

namespace seed {

//==============================================================================
//	CLASS Point1
//==============================================================================

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 1>::Point()
:
	x()
{}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 1>::Point(T inX)
:
	x(inX)
{}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 1>::Point(const Matrix<T, 1, 1> &rhs)
:
	x(*reinterpret_cast<const T*>(&rhs))
{}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 1>::Point(const Point<T, 1> &rhs)
:
	x(rhs.x)
{}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 1>& Point<T, 1>::operator = (const Point<T, 1> &rhs)
{
	x = rhs.x;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 1>& Point<T, 1>::operator = (const Matrix<T, 1, 1> &rhs)
{
	x = *reinterpret_cast<const T*>(&rhs);
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
bool Point<T, 1>::operator == (const Point<T, 1> &rhs) const
{
	return (rhs.x == x);
}

//------------------------------------------------------------------------------
//
template<class T>
bool Point<T, 1>::operator != (const Point<T, 1> &rhs) const
{
	return (rhs.x != x);
}

//------------------------------------------------------------------------------
//
template<class T>
bool Point<T, 1>::operator < (const Point<T, 1> &rhs) const
{
	return (x < rhs.x);
}

//------------------------------------------------------------------------------
//
template<class T>
bool Point<T, 1>::operator <= (const Point<T, 1> &rhs) const
{
	return (x < rhs.x);
}

//------------------------------------------------------------------------------
//
template<class T>
bool Point<T, 1>::operator > (const Point<T, 1> &rhs) const
{
	return (x > rhs.x);
}

//------------------------------------------------------------------------------
//
template<class T>
bool Point<T, 1>::operator >= (const Point<T, 1> &rhs) const
{
	return (x > rhs.x);
}

//------------------------------------------------------------------------------
//
template<class T>
const T& Point<T, 1>::operator [] (int index) const
{
	return reinterpret_cast<const T*>(this)[index];
}

//------------------------------------------------------------------------------
//
template<class T>
T& Point<T, 1>::operator [] (int index)
{
	return reinterpret_cast<T*>(this)[index];
}

//------------------------------------------------------------------------------
//
template<class T>
T* Point<T, 1>::ptr()
{
	return reinterpret_cast<T*>(this);
}

//------------------------------------------------------------------------------
//
template<class T>
const T* Point<T, 1>::ptr() const
{
	return reinterpret_cast<const T*>(this);
}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 1> Point<T, 1>::operator + (const Point<T, 1> &rhs) const
{
	return Point<T, 1>(x+rhs.x);
}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 1> Point<T, 1>::operator - (const Point<T, 1> &rhs) const
{
	return Point<T, 1>(x-rhs.x);
}

//------------------------------------------------------------------------------
//
template<class T>
T Point<T, 1>::operator * (const Point<T, 1> &rhs) const
{
	return x*rhs.x;
}

//------------------------------------------------------------------------------
//
template<class T> template<class U>
Point<T, 1> Point<T, 1>::operator * (const U &rhs) const
{
	return Point<T, 1>(x*rhs);
}

//------------------------------------------------------------------------------
//
template<class T> template<class U>
Point<T, 1> Point<T, 1>::operator / (const U &rhs) const
{
	return Point<T, 1>(x/rhs);
}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 1>& Point<T, 1>::operator += (const Point<T, 1> &rhs)
{
	x += rhs.x;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 1>& Point<T, 1>::operator -= (const Point<T, 1> &rhs)
{
	x -= rhs.x;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T> template<class U>
Point<T, 1>& Point<T, 1>::operator *= (const U &rhs)
{
	x *= rhs;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T> template<class U>
Point<T, 1>& Point<T, 1>::operator /= (const U &rhs)
{
	x /= rhs;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 1> Point<T, 1>::operator - () const
{
	return Point<T, 1>(-x);
}

//------------------------------------------------------------------------------
//
template<class T>
void Point<T, 1>::setLength(double aLength)
{
	*this *= aLength / length();
}

//------------------------------------------------------------------------------
//
template<class T>
double Point<T, 1>::length() const
{
	return x;
}

//------------------------------------------------------------------------------
//
template<class T>
T Point<T, 1>::length2() const
{
	return x*x;
}

//------------------------------------------------------------------------------
//
template<class T>
Matrix<T, 1, 1>& Point<T, 1>::asMatrix()
{
	return *(Matrix<T, 1, 1>*)this;
}

//------------------------------------------------------------------------------
//
template<class T>
const Matrix<T, 1, 1>& Point<T, 1>::asMatrix() const
{
	return *(Matrix<T, 1, 1>*)this;
}

//------------------------------------------------------------------------------
//
template<class T>
Matrix<T, 1, 1>& Point<T, 1>::asTMatrix()
{
	return *(Matrix<T, 1, 1>*)this;
}

//------------------------------------------------------------------------------
//
template<class T>
const Matrix<T, 1, 1>& Point<T, 1>::asTMatrix() const
{
	return *(Matrix<T, 1, 1>*)this;
}

//------------------------------------------------------------------------------
//
template<class T>
bool Point<T, 1>::hasNan() const
{
	return std::isnan(x);
}

//------------------------------------------------------------------------------
//
template<class T>
bool Point<T, 1>::hasInf() const
{
	return std::isinf(x);
}

//------------------------------------------------------------------------------
//
template<class U, class T>
static inline Point<T, 1> operator * (const U &lhs, const Point<T, 1> &rhs)
{
	return rhs * lhs;
}

//------------------------------------------------------------------------------
//
template<class T>
std::string Point<T, 1>::serialize() const
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
template<class T>
Point<T, 1> Point<T, 1>::deSerialize(const std::string &str)
{
	char buf[2048];
	strcpy(buf, str.c_str());
	Point p(0);

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
template<class T>
int Point<T, 1>::size()
{
	return 1;
}

//------------------------------------------------------------------------------
//
template<class T> template<class U>
Point<U, 1> Point<T, 1>::cast() const
{
	return Point<U, 1>(static_cast<U>(x));
}

} // namespace seed


#endif // __GEOMETRY_POINT1_INLINE__
