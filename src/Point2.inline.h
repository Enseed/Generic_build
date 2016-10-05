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
#ifndef __GEOMETRY_POINT2_INLINE__
#define __GEOMETRY_POINT2_INLINE__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "../Point2.h"

#ifndef NDEBUG
#include "../../Devel/Debug.h"
#endif

#include <cmath>
#include <sstream>
#include <cstring>
#include <limits>

namespace seed {

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 2>::Point()
:
	x(),
	y()
{}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 2>::Point(T inX, T inY)
:
	x(inX),
	y(inY)
{}


//------------------------------------------------------------------------------
//
template<class T>
Point<T, 2>::Point(const Point<T, 1> &inX, const Point<T, 1> &inY)
:
	x(inX.x),
	y(inY.x)
{}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 2>::Point(const T &inX, const Point<T, 1> &inY)
:
	x(inX),
	y(inY.x)
{}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 2>::Point(const Point<T, 1> &inX, const T &inY)
:
	x(inX.x),
	y(inY)
{}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 2>::Point(T inVal)
:
	x(inVal),
	y(inVal)
{}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 2>::Point(const T *data)
:
	x(data[0]),
	y(data[1])
{}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 2>::Point(const Matrix<T, 1, 2> &rhs)
:
	x(reinterpret_cast<const T*>(&rhs)[0]),
	y(reinterpret_cast<const T*>(&rhs)[1])
{}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 2>::Point(const Point &rhs)
:
	x(rhs.x),
	y(rhs.y)
{}

	//------------------------------------------------------------------------------
	//
	template<class T>
	template<class U>
	Point<T, 2>::Point(const Point<U,2> &rhs)
		:
	x(rhs.x),
	y(rhs.y)
	{}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 2>& Point<T, 2>::operator = (const Point<T, 2> &rhs)
{
	x = rhs.x;
	y = rhs.y;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 2>& Point<T, 2>::operator = (const Matrix<T, 1, 2> &rhs)
{
	x = reinterpret_cast<const T*>(&rhs)[0];
	y = reinterpret_cast<const T*>(&rhs)[1];
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
bool Point<T, 2>::operator == (const Point<T, 2> &rhs) const
{
	return (rhs.x == x) && (rhs.y == y);
}

//------------------------------------------------------------------------------
//
template<class T>
bool Point<T, 2>::operator != (const Point<T, 2> &rhs) const
{
	return (rhs.x != x) || (rhs.y != y);
}

//------------------------------------------------------------------------------
//
template<class T>
bool Point<T, 2>::operator < (const Point<T, 2> &rhs) const
{
	return (x < rhs.x) || ((x == rhs.x) && (y < rhs.y));
}

//------------------------------------------------------------------------------
//
template<class T>
bool Point<T, 2>::operator <= (const Point<T, 2> &rhs) const
{
	return (x < rhs.x) || ((x == rhs.x) && (y <= rhs.y));
}

//------------------------------------------------------------------------------
//
template<class T>
bool Point<T, 2>::operator > (const Point<T, 2> &rhs) const
{
	return (x > rhs.x) || ((x == rhs.x) && (y > rhs.y));
}

//------------------------------------------------------------------------------
//
template<class T>
bool Point<T, 2>::operator >= (const Point<T, 2> &rhs) const
{
	return (x > rhs.x) || ((x == rhs.x) && (y >= rhs.y));
}

//------------------------------------------------------------------------------
//
template<class T>
const T& Point<T, 2>::operator [] (int index) const
{
	return reinterpret_cast<const T*>(this)[index];
}

//------------------------------------------------------------------------------
//
template<class T>
T& Point<T, 2>::operator [] (int index)
{
	return reinterpret_cast<T*>(this)[index];
}

//------------------------------------------------------------------------------
//
template<class T>
T* Point<T, 2>::ptr()
{
	return reinterpret_cast<T*>(this);
}

//------------------------------------------------------------------------------
//
template<class T>
const T* Point<T, 2>::ptr() const
{
	return reinterpret_cast<const T*>(this);
}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 2> Point<T, 2>::operator + (const Point<T, 2> &rhs) const
{
	return Point<T, 2>(x+rhs.x, y+rhs.y);
}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 2> Point<T, 2>::operator - (const Point<T, 2> &rhs) const
{
	return Point<T, 2>(x-rhs.x, y-rhs.y);
}

//------------------------------------------------------------------------------
//
template<class T>
T Point<T, 2>::operator * (const Point<T, 2> &rhs) const
{
	return x*rhs.x + y*rhs.y;
}

//------------------------------------------------------------------------------
//
template<class T>
T Point<T, 2>::operator ^ (const Point<T, 2> &rhs) const
{
	return x*rhs.y - y*rhs.x;
}

//------------------------------------------------------------------------------
//
template<class T> template<class U>
Point<T, 2> Point<T, 2>::operator * (const U &rhs) const
{
	return Point<T, 2>(x*rhs, y*rhs);
}

//------------------------------------------------------------------------------
//
template<class T> template<class U>
Point<T, 2> Point<T, 2>::operator / (const U &rhs) const
{
	return Point<T, 2>(x/rhs, y/rhs);
}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 2>& Point<T, 2>::operator += (const Point<T, 2> &rhs)
{
	x += rhs.x; y += rhs.y;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 2>& Point<T, 2>::operator -= (const Point<T, 2> &rhs)
{
	x -= rhs.x; y -= rhs.y;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T> template<class U>
Point<T, 2>& Point<T, 2>::operator *= (const U &rhs)
{
	x *= rhs; y *= rhs;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T> template<class U>
Point<T, 2>& Point<T, 2>::operator /= (const U &rhs)
{
	x /= rhs; y /= rhs;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 2> Point<T, 2>::operator - () const
{
	return Point<T, 2>(-x, -y);
}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 2> Point<T, 2>::operator ~ () const
{
	return perpendicular();
}

//------------------------------------------------------------------------------
//
template<class T>
void Point<T, 2>::setLength(double aLength)
{
	*this *= aLength / length();
}

//------------------------------------------------------------------------------
//
template<class T>
double Point<T, 2>::length() const
{
	return sqrt(length2());
}

//------------------------------------------------------------------------------
//
template<class T>
T Point<T, 2>::length2() const
{
	return x*x+y*y;
}

//------------------------------------------------------------------------------
//
template<class T>
void Point<T, 2>::scale(double newLength)
{
#ifndef NDEBUG
	ASSERTF(!std::numeric_limits<T>::is_integer, "scaling of integer vector is not defined.");
#endif

	*this = scaled(newLength);
}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 2> Point<T, 2>::scaled(double newLength) const
{
#ifndef NDEBUG
	ASSERTF(!std::numeric_limits<T>::is_integer, "scaling of integer vector is not defined.");
#endif
	double scaleRatio = newLength/length();
	return *this * scaleRatio;
}


//------------------------------------------------------------------------------
//
template<class T>
void Point<T, 2>::normalize()
{
#ifndef NDEBUG
	ASSERTF(!std::numeric_limits<T>::is_integer, "scaling of integer vector is not defined.");
#endif
	scale(1.0f);
}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 2> Point<T, 2>::normalized() const
{
#ifndef NDEBUG
	ASSERTF(!std::numeric_limits<T>::is_integer, "scaling of integer vector is not defined.");
#endif
	return scaled(1.0f);
}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 2> Point<T, 2>::perpendicular() const
{
	return Point<T, 2>(-y, x);
}

//------------------------------------------------------------------------------
//
template<class T>
Matrix<T, 1, 2>& Point<T, 2>::asTMatrix()
{
	return *(Matrix<T, 1, 2>*)this;
}

//------------------------------------------------------------------------------
//
template<class T>
const Matrix<T, 1, 2>& Point<T, 2>::asTMatrix() const
{
	return *(Matrix<T, 1, 2>*)this;
}

//------------------------------------------------------------------------------
//
template<class T>
Matrix<T, 2, 1>& Point<T, 2>::asMatrix()
{
	return *(Matrix<T, 2, 1>*)this;
}

//------------------------------------------------------------------------------
//
template<class T>
const Matrix<T, 2, 1>& Point<T, 2>::asMatrix() const
{
	return *(Matrix<T, 2, 1>*)this;
}

//------------------------------------------------------------------------------
//
template<class T>
bool Point<T, 2>::hasNan() const
{
	return std::isnan(x) || std::isnan(y);
}

//------------------------------------------------------------------------------
//
template<class T>
bool Point<T, 2>::hasInf() const
{
	return std::isinf(x) || std::isinf(y);
}

//------------------------------------------------------------------------------
//
template<class U, class T>
static inline Point<T, 2> operator * (const U &lhs, const Point<T, 2> &rhs)
{
	return rhs * lhs;
}

//------------------------------------------------------------------------------
//
template<class T>
std::string Point<T, 2>::serialize() const
{
	std::stringstream strstream;
	strstream << "{ ";
	for (int i = 0; i < size(); ++i)
	{
		strstream << (*this)[i];
		if (i < size()-1)	strstream << ", ";
	}
	strstream << " }";
	return strstream.str();
}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 2> Point<T, 2>::deSerialize(const std::string &str)
{
	char buf[2048];
	strcpy(buf, str.c_str());
	Point p(T(0));

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
int Point<T, 2>::size()
{
	return 2;
}


//------------------------------------------------------------------------------
//
template<class T> template<class U>
Point<U, 2> Point<T, 2>::cast() const
{
	return Point<U, 2>(static_cast<U>(x), static_cast<U>(y));
}

} // namespace seed


#endif // __GEOMETRY_POINT2_INLINE__
