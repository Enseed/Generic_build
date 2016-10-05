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
#ifndef __GEOMETRY_POINT3_INLINE__
#define __GEOMETRY_POINT3_INLINE__


//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "../Point3.h"
#ifndef NDEBUG
#include "../../Devel/Debug.h"
#endif 

#include <limits>

namespace seed {


//------------------------------------------------------------------------------
//
template<class T>
Point<T, 3>::Point()
:
	x(),
	y(),
	z()
{}

//------------------------------------------------------------------------------
//
template<class T>
template<class U>
Point<T, 3>::Point(const U *array)
:
	x(array[0]),
	y(array[1]),
	z(array[2])
{}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 3>::Point(T inX, T inY, T inZ)
:
	x(inX),
	y(inY),
	z(inZ)
{}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 3>::Point(const Point<T, 1> &inX, const Point<T, 1> &inY, const Point<T, 1> &inZ)
:
	x(inX.x),
	y(inY.x),
	z(inZ.x)
{}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 3>::Point(const T &inX, const Point<T, 1> &inY, const Point<T, 1> &inZ)
:
	x(inX),
	y(inY.x),
	z(inZ.x)
{}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 3>::Point(const Point<T, 1> &inX, const T &inY, const Point<T, 1> &inZ)
:
	x(inX.x),
	y(inY),
	z(inZ.x)
{}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 3>::Point(const Point<T, 1> &inX, const Point<T, 1> &inY, const T &inZ)
:
	x(inX.x),
	y(inY.x),
	z(inZ)
{}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 3>::Point(const T &inX, const T &inY, const Point<T, 1> &inZ)
:
	x(inX),
	y(inY),
	z(inZ.x)
{}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 3>::Point(const Point<T, 1> &inX, const T &inY, const T &inZ)
:
	x(inX.x),
	y(inY),
	z(inZ)
{}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 3>::Point(const Point<T,2> &inXY, const T &inZ)
:
	x(inXY.x),
	y(inXY.y),
	z(inZ)
{}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 3>::Point(const Point<T,2> &inXY, const Point<T, 1> &inZ)
:
	x(inXY.x),
	y(inXY.y),
	z(inZ.x)
{}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 3>::Point(const T &inX, const Point<T, 2> &inYZ)
:
	x(inX),
	y(inYZ.x),
	z(inYZ.y)
{}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 3>::Point(const Point<T, 1> &inX, const Point<T, 2> &inYZ)
:
	x(inX.x),
	y(inYZ.x),
	z(inYZ.y)
{}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 3>::Point(T inVal)
:
	x(inVal),
	y(inVal),
	z(inVal)
{}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 3>::Point(const Matrix<T, 1, 3> &rhs)
:
	x(reinterpret_cast<const T*>(&rhs)[0]),
	y(reinterpret_cast<const T*>(&rhs)[1]),
	z(reinterpret_cast<const T*>(&rhs)[2])
{}

//------------------------------------------------------------------------------
//
template<class T>
template<class U>
Point<T, 3>::Point(const Point<U,3> &rhs)
:
	x(rhs.x),
	y(rhs.y),
	z(rhs.z)
{}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 3>& Point<T, 3>::operator = (const Matrix<T, 1, 3> &rhs)
{
	x = reinterpret_cast<const T*>(&rhs)[0];
	y = reinterpret_cast<const T*>(&rhs)[1];
	z = reinterpret_cast<const T*>(&rhs)[2];
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 3>& Point<T, 3>::operator = (const Point &rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
bool Point<T, 3>::operator == (const Point &rhs) const
{
	return (rhs.x == x) && (rhs.y == y) && (rhs.z == z);
}

//------------------------------------------------------------------------------
//
template<class T>
bool Point<T, 3>::operator != (const Point &rhs) const
{
	return (rhs.x != x) || (rhs.y != y) || (rhs.z != z);
}

//------------------------------------------------------------------------------
//
template<class T>
bool Point<T, 3>::operator < (const Point &rhs) const
{
	return (x < rhs.x) || ((x == rhs.x) && ((y < rhs.y) || ((y == rhs.y) && (z < rhs.z))));
}

//------------------------------------------------------------------------------
//
template<class T>
bool Point<T, 3>::operator <= (const Point &rhs) const
{
	return (x < rhs.x) || ((x == rhs.x) && ((y < rhs.y) || ((y == rhs.y) && (z <= rhs.z))));
}

//------------------------------------------------------------------------------
//
template<class T>
bool Point<T, 3>::operator > (const Point &rhs) const
{
	return (x > rhs.x) || ((x == rhs.x) && ((y > rhs.y) || ((y == rhs.y) && (z > rhs.z))));
}

//------------------------------------------------------------------------------
//
template<class T>
bool Point<T, 3>::operator >= (const Point &rhs) const
{
	return (x > rhs.x) || ((x == rhs.x) && ((y > rhs.y) || ((y == rhs.y) && (z >= rhs.z))));
}

//------------------------------------------------------------------------------
//
template<class T>
const T& Point<T, 3>::operator [] (int index) const
{
	return reinterpret_cast<const T*>(this)[index];
}

//------------------------------------------------------------------------------
//
template<class T>
T& Point<T, 3>::operator [] (int index)
{
	return reinterpret_cast<T*>(this)[index];
}


//------------------------------------------------------------------------------
//
template<class T>
T* Point<T, 3>::ptr()
{
	return reinterpret_cast<T*>(this);
}

//------------------------------------------------------------------------------
//
template<class T>
const T* Point<T, 3>::ptr() const
{
	return reinterpret_cast<const T*>(this);
}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 3> Point<T, 3>::operator + (const Point<T, 3> &rhs) const
{
	return Point<T, 3>(x+rhs.x, y+rhs.y, z+rhs.z);
}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 3> Point<T, 3>::operator - (const Point<T, 3> &rhs) const
{
	return Point<T, 3>(x-rhs.x, y-rhs.y, z-rhs.z);
}

//------------------------------------------------------------------------------
//
template<class T>
T Point<T, 3>::operator * (const Point<T, 3> &rhs) const
{
	return x*rhs.x + y*rhs.y + z*rhs.z;
}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 3> Point<T, 3>::operator ^ (const Point<T, 3> &rhs) const
{
	return Point<T, 3>(y*rhs.z-z*rhs.y, z*rhs.x-x*rhs.z, x*rhs.y-y*rhs.x);
}

//------------------------------------------------------------------------------
//
template<class T> template<class U>
Point<T, 3> Point<T, 3>::operator * (const U &rhs) const
{
	return Point<T, 3>(x*rhs, y*rhs, z*rhs);
}

//------------------------------------------------------------------------------
//
template<class T> template<class U>
Point<T, 3> Point<T, 3>::operator / (const U &rhs) const
{
	return Point<T, 3>(x/rhs, y/rhs, z/rhs);
}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 3>& Point<T, 3>::operator += (const Point<T, 3> &rhs)
{
	x += rhs.x; y += rhs.y; z += rhs.z;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 3>& Point<T, 3>::operator -= (const Point<T, 3> &rhs)
{
	x -= rhs.x; y -= rhs.y; z -= rhs.z;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T> template<class U>
Point<T, 3>& Point<T, 3>::operator *= (const U &rhs)
{
	x *= rhs; y *= rhs; z *= rhs;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T> template<class U>
Point<T, 3>& Point<T, 3>::operator /= (const U &rhs)
{
	x /= rhs; y /= rhs; z /= rhs;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 3> Point<T, 3>::operator - () const
{
	return Point<T, 3>(-x, -y, -z);
}

//------------------------------------------------------------------------------
//
template<class T>
void Point<T, 3>::setLength(double aLength)
{
	*this *= aLength / length();
}

//------------------------------------------------------------------------------
//
template<class T>
double Point<T, 3>::length() const
{
	return sqrt(length2());
}

//------------------------------------------------------------------------------
//
template<class T>
T Point<T, 3>::length2() const
{
	return x*x+y*y+z*z;
}

//------------------------------------------------------------------------------
//
template<class T>
void Point<T, 3>::scale(double newLength)
{
#ifndef NDEBUG
	ASSERTF(!std::numeric_limits<T>::is_integer, "scaling of integer vector is not defined.");
#endif
	*this = scaled(newLength);
}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 3> Point<T, 3>::scaled(double newLength) const
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
void Point<T, 3>::normalize()
{
#ifndef NDEBUG
	ASSERTF(!std::numeric_limits<T>::is_integer, "scaling of integer vector is not defined.");
#endif
	scale(1.0);
}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 3> Point<T, 3>::normalized() const
{
#ifndef NDEBUG
	ASSERTF(!std::numeric_limits<T>::is_integer, "scaling of integer vector is not defined.");
#endif
	return scaled(1.0f);
}

//------------------------------------------------------------------------------
//
template<class T>
Matrix<T, 1, 3>& Point<T, 3>::asTMatrix()
{
	return *(Matrix<T, 1, 3>*)this;
}

//------------------------------------------------------------------------------
//
template<class T>
const Matrix<T, 1, 3>& Point<T, 3>::asTMatrix() const
{
	return *(Matrix<T, 1, 3>*)this;
}

//------------------------------------------------------------------------------
//
template<class T>
Matrix<T, 3, 1>& Point<T, 3>::asMatrix()
{
	return *(Matrix<T, 3, 1>*)this;
}

//------------------------------------------------------------------------------
//
template<class T>
const Matrix<T, 3, 1>& Point<T, 3>::asMatrix() const
{
	return *(Matrix<T, 3, 1>*)this;
}

//------------------------------------------------------------------------------
//
template<class T>
bool Point<T, 3>::hasNan() const
{
	return std::isnan(x) || std::isnan(y) || std::isnan(z);
}

//------------------------------------------------------------------------------
//
template<class T>
bool Point<T, 3>::hasInf() const
{
	return std::isinf(x) || std::isinf(y) || std::isinf(z);
}


//------------------------------------------------------------------------------
//
template<class U, class T>
static inline Point<T,3> operator * (const U &lhs, const Point<T,3> &rhs)
{
	return rhs * lhs;
}


//------------------------------------------------------------------------------
//
template<class T>
static inline Point<T,3> operator * (const Matrix<T, 3, 3> &lhs, const Point<T,3> &rhs)
{
	return lhs * rhs.asTMatrix();
}

//------------------------------------------------------------------------------
//
template<class T>
std::string Point<T, 3>::serialize() const
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
Point<T, 3> Point<T, 3>::deSerialize(const std::string &str)
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
int Point<T, 3>::size()
{
	return 3;
}

//------------------------------------------------------------------------------
//
template<class T> template<class U>
Point<U, 3> Point<T, 3>::cast() const
{
	return Point<U, 3>(static_cast<U>(x), static_cast<U>(y), static_cast<U>(z));
}

} // namespace seed


#endif // __GEOMETRY_POINT3_INLINE__
