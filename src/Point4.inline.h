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
#ifndef __GEOMETRY_POINT4_INLINE__
#define __GEOMETRY_POINT4_INLINE__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "../Point4.h"
#include <limits>

namespace seed {


//==============================================================================
//	CLASS Point4
//==============================================================================
//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>::Point()
:
	x(),
	y(),
	z(),
	w()
{}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>::Point(T inAll)
:
	x(inAll),
	y(inAll),
	z(inAll),
	w(inAll)
{}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>::Point(const T *data)
:
	x(data[0]),
	y(data[1]),
	z(data[2]),
	w(data[3])
{}


//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>::Point(T inX, T inY, T inZ, T inW)
:
	x(inX),
	y(inY),
	z(inZ),
	w(inW)
{}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>::Point(const Point<T, 1> &inX, const Point<T, 1> &inY, const Point<T, 1> &inZ, const Point<T, 1> &inW)
:
	x(inX.x),
	y(inY.x),
	z(inZ.x),
	w(inW.x)
{}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>::Point(const Point<T, 1> &inX, const Point<T, 1> &inY, const Point<T, 1> &inZ, const T &inW)
:
	x(inX.x),
	y(inY.x),
	z(inZ.x),
	w(inW)
{}


//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>::Point(const Point<T, 1> &inX, const Point<T, 1> &inY, const T &inZ, const T &inW)
:
	x(inX.x),
	y(inY.x),
	z(inZ),
	w(inW)
{}


//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>::Point(const Point<T, 1> &inX, const T &inY, const Point<T, 1> &inZ, const T &inW)
:
	x(inX.x),
	y(inY),
	z(inZ.x),
	w(inW)
{}


//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>::Point(const T &inX, const Point<T, 1> &inY, const Point<T, 1> &inZ, const T &inW)
:
	x(inX),
	y(inY.x),
	z(inZ.x),
	w(inW)
{}


//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>::Point(const Point<T, 1> &inX, const T &inY, const T &inZ, const T &inW)
:
	x(inX.x),
	y(inY),
	z(inZ),
	w(inW)
{}


//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>::Point(const T &inX, const Point<T, 1> &inY, const T &inZ, const T &inW)
:
	x(inX),
	y(inY.x),
	z(inZ),
	w(inW)
{}


//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>::Point(const Point<T, 1> &inX, const Point<T, 1> &inY, const T &inZ, const Point<T, 1> &inW)
:
	x(inX.x),
	y(inY.x),
	z(inZ),
	w(inW.x)
{}


//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>::Point(const Point<T, 1> &inX, const T &inY, const T &inZ, const Point<T, 1> &inW)
:
	x(inX.x),
	y(inY),
	z(inZ),
	w(inW.x)
{}


//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>::Point(const T &inX, const Point<T, 1> &inY, const T &inZ, const Point<T, 1> &inW)
:
	x(inX),
	y(inY.x),
	z(inZ),
	w(inW.x)
{}


//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>::Point(const T &inX, const T &inY, const T &inZ, const Point<T, 1> &inW)
:
	x(inX),
	y(inY),
	z(inZ),
	w(inW.x)
{}


//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>::Point(const Point<T, 1> &inX, const T &inY, const Point<T, 1> &inZ, const Point<T, 1> &inW)
:
	x(inX.x),
	y(inY),
	z(inZ.x),
	w(inW.x)
{}


//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>::Point(const T &inX, const T &inY, const Point<T, 1> &inZ, const Point<T, 1> &inW)
:
	x(inX),
	y(inY),
	z(inZ.x),
	w(inW.x)
{}


//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>::Point(const T &inX, const Point<T, 1> &inY, const Point<T, 1> &inZ, const Point<T, 1> &inW)
:
	x(inX),
	y(inY.x),
	z(inZ.x),
	w(inW.x)
{}


//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>::Point(const Point<T, 2> &inXY, const Point<T, 1> &inZ, const Point<T, 1> &inW)
:
	x(inXY.x),
	y(inXY.y),
	z(inZ.x),
	w(inW.x)
{}


//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>::Point(const Point<T, 2> &inXY, const Point<T, 1> &inZ, const T &inW)
:
	x(inXY.x),
	y(inXY.y),
	z(inZ.x),
	w(inW)
{}


//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>::Point(const Point<T, 2> &inXY, const T &inZ, const T &inW)
:
	x(inXY.x),
	y(inXY.y),
	z(inZ),
	w(inW)
{}


//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>::Point(const Point<T, 2> &inXY, const T &inZ, const Point<T, 1> &inW)
:
	x(inXY.x),
	y(inXY.y),
	z(inZ),
	w(inW.x)
{}


//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>::Point(const Point<T, 1> &inX, const Point<T, 2> &inYZ, const Point<T, 1> &inW)
:
	x(inX.x),
	y(inYZ.x),
	z(inYZ.y),
	w(inW.x)
{}


//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>::Point(const Point<T, 1> &inX, const Point<T, 2> &inYZ, const T &inW)
:
	x(inX.x),
	y(inYZ.x),
	z(inYZ.y),
	w(inW)
{}


//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>::Point(const T &inX, const Point<T, 2> &inYZ, const T &inW)
:
	x(inX),
	y(inYZ.x),
	z(inYZ.y),
	w(inW)
{}


//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>::Point(const T &inX, const Point<T, 2> &inYZ, const Point<T, 1> &inW)
:
	x(inX),
	y(inYZ.x),
	z(inYZ.y),
	w(inW.x)
{}


//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>::Point(const Point<T, 1> &inX, const Point<T, 1> &inY, const Point<T, 2> &inZW)
:
	x(inX.x),
	y(inY.x),
	z(inZW.x),
	w(inZW.y)
{}


//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>::Point(const Point<T, 1> &inX, const T &inY, const Point<T, 2> &inZW)
:
	x(inX.x),
	y(inY),
	z(inZW.x),
	w(inZW.y)
{}


//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>::Point(const T &inX, const T &inY, const Point<T, 2> &inZW)
:
	x(inX),
	y(inY),
	z(inZW.x),
	w(inZW.y)
{}


//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>::Point(const T &inX, const Point<T, 1> &inY, const Point<T, 2> &inZW)
:
	x(inX),
	y(inY.x),
	z(inZW.x),
	w(inZW.y)
{}


//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>::Point(const Point<T, 2> &inXY, const Point<T, 2> &inZW)
:
	x(inXY.x),
	y(inXY.y),
	z(inZW.x),
	w(inZW.y)
{}

	
//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>::Point(const Point<T, 3> &inXYZ, const Point<T, 1> &inW)
:
	x(inXYZ.x),
	y(inXYZ.y),
	z(inXYZ.z),
	w(inW.x)
{}


//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>::Point(const Point<T, 3> &inXYZ, const T &inW)
:
	x(inXYZ.x),
	y(inXYZ.y),
	z(inXYZ.z),
	w(inW)
{}


//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>::Point(const Point<T, 1> &inX, const Point<T, 3> &inYZW)
:
	x(inX.x),
	y(inYZW.x),
	z(inYZW.y),
	w(inYZW.z)
{}


//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>::Point(const T &inX, const Point<T, 3> &inYZW)
:
	x(inX),
	y(inYZW.x),
	z(inYZW.y),
	w(inYZW.z)
{}


//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>::Point(const Matrix<T, 1, 4> &rhs)
:
	x(reinterpret_cast<const T*>(&rhs)[0]),
	y(reinterpret_cast<const T*>(&rhs)[1]),
	z(reinterpret_cast<const T*>(&rhs)[2]),
	w(reinterpret_cast<const T*>(&rhs)[3])
{}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>::Point(const Point<T, 4> &rhs)
:
	x(rhs.x),
	y(rhs.y),
	z(rhs.z),
	w(rhs.w)
{}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>& Point<T, 4>::operator = (const Matrix<T, 1, 4> &rhs)
{
	x = reinterpret_cast<const T*>(&rhs)[0];
	y = reinterpret_cast<const T*>(&rhs)[1];
	z = reinterpret_cast<const T*>(&rhs)[2];
	w = reinterpret_cast<const T*>(&rhs)[3];
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>& Point<T, 4>::operator = (const Point<T, 4> &rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	w = rhs.w;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
bool Point<T, 4>::operator == (const Point<T, 4> &rhs) const
{
	return (rhs.x == x) && (rhs.y == y) && (rhs.z == z) && (rhs.w == w);
}

//------------------------------------------------------------------------------
//
template<class T>
bool Point<T, 4>::operator != (const Point<T, 4> &rhs) const
{
	return (rhs.x != x) || (rhs.y != y) || (rhs.z != z) || (rhs.w != w);
}

//------------------------------------------------------------------------------
//
template<class T>
bool Point<T, 4>::operator < (const Point<T, 4> &rhs) const
{
	return (x < rhs.x) || ((x == rhs.x) && ((y < rhs.y) || ((y == rhs.y) && ((z < rhs.z) || ((z == rhs.z) && (w < rhs.w))))));
}

//------------------------------------------------------------------------------
//
template<class T>
bool Point<T, 4>::operator <= (const Point<T, 4> &rhs) const
{
	return (x < rhs.x) || ((x == rhs.x) && ((y < rhs.y) || ((y == rhs.y) && ((z < rhs.z) || ((z == rhs.z) && (w <= rhs.w))))));
}

//------------------------------------------------------------------------------
//
template<class T>
bool Point<T, 4>::operator > (const Point<T, 4> &rhs) const
{
	return (x > rhs.x) || ((x == rhs.x) && ((y > rhs.y) || ((y == rhs.y) && ((z > rhs.z) || ((z == rhs.z) && (w > rhs.w))))));
}

//------------------------------------------------------------------------------
//
template<class T>
bool Point<T, 4>::operator >= (const Point<T, 4> &rhs) const
{
	return (x > rhs.x) || ((x == rhs.x) && ((y > rhs.y) || ((y == rhs.y) && ((z > rhs.z) || ((z == rhs.z) && (w >= rhs.w))))));
}

//------------------------------------------------------------------------------
//
template<class T>
const T& Point<T, 4>::operator [] (int index) const
{
	return reinterpret_cast<const T*>(this)[index];
}

//------------------------------------------------------------------------------
//
template<class T>
T& Point<T, 4>::operator [] (int index)
{
	return reinterpret_cast<T*>(this)[index];
}

//------------------------------------------------------------------------------
//
template<class T>
T* Point<T, 4>::ptr()
{
	return reinterpret_cast<T*>(this);
}

//------------------------------------------------------------------------------
//
template<class T>
const T* Point<T, 4>::ptr() const
{
	return reinterpret_cast<const T*>(this);
}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4> Point<T, 4>::operator + (const Point<T, 4> &rhs) const
{
	return Point<T, 4>(x+rhs.x, y+rhs.y, z+rhs.z, w+rhs.w);
}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4> Point<T, 4>::operator - (const Point<T, 4> &rhs) const
{
	return Point<T, 4>(x-rhs.x, y-rhs.y, z-rhs.z, w-rhs.w);
}

//------------------------------------------------------------------------------
//
template<class T>
T Point<T, 4>::operator * (const Point<T, 4> &rhs) const
{
	return x*rhs.x + y*rhs.y + z*rhs.z + w*rhs.w;
}

//------------------------------------------------------------------------------
//
template<class T> template<class U>
Point<T, 4> Point<T, 4>::operator * (const U &rhs) const
{
	return Point<T, 4>(x*rhs, y*rhs, z*rhs, w*rhs);
}

//------------------------------------------------------------------------------
//
template<class T> template<class U>
Point<T, 4> Point<T, 4>::operator / (const U &rhs) const
{
	return Point<T, 4>(x/rhs, y/rhs, z/rhs, w/rhs);
}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>& Point<T, 4>::operator += (const Point<T, 4> &rhs)
{
	x += rhs.x; y += rhs.y; z += rhs.z; w+= rhs.w;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4>& Point<T, 4>::operator -= (const Point<T, 4> &rhs)
{
	x -= rhs.x; y -= rhs.y; z -= rhs.z; w -= rhs.w;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T> template<class U>
Point<T, 4>& Point<T, 4>::operator *= (const U &rhs)
{
	x *= rhs; y *= rhs; z *= rhs; w *= rhs;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T> template<class U>
Point<T, 4>& Point<T, 4>::operator /= (const U &rhs)
{
	x /= rhs; y /= rhs; z /= rhs; w /= rhs;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4> Point<T, 4>::operator - () const
{
	return Point<T, 4>(-x,-y, -z, -w);
}

//------------------------------------------------------------------------------
//
template<class T>
void Point<T, 4>::setLength(double aLength)
{
	*this *= aLength / length();
}

//------------------------------------------------------------------------------
//
template<class T>
double Point<T, 4>::length() const
{
	return sqrt(length2());
}

//------------------------------------------------------------------------------
//
template<class T>
T Point<T, 4>::length2() const
{
	return x*x+y*y+z*z+w*w;
}

//------------------------------------------------------------------------------
//
template<class T>
void Point<T, 4>::scale(double newLength)
{
#ifndef NDEBUG
	ASSERTF(!std::numeric_limits<T>::is_integer, "scaling of integer vector is not defined.");
#endif
	*this = scaled(newLength);
}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4> Point<T, 4>::scaled(double newLength) const
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
void Point<T, 4>::normalize()
{
#ifndef NDEBUG
	ASSERTF(!std::numeric_limits<T>::is_integer, "scaling of integer vector is not defined.");
#endif
	scale(1.0f);
}

//------------------------------------------------------------------------------
//
template<class T>
Point<T, 4> Point<T, 4>::normalized() const
{
#ifndef NDEBUG
	ASSERTF(!std::numeric_limits<T>::is_integer, "scaling of integer vector is not defined.");
#endif
	return scaled(1.0);
}

//------------------------------------------------------------------------------
//
template<class T>
Matrix<T, 4, 1>& Point<T, 4>::asMatrix()
{
	return *(Matrix<T, 4, 1>*)this;
}

//------------------------------------------------------------------------------
//
template<class T>
Matrix<T, 1, 4>& Point<T, 4>::asTMatrix()
{
	return *(Matrix<T, 1, 4>*)this;
}

//------------------------------------------------------------------------------
//
template<class T>
const Matrix<T, 4, 1>& Point<T, 4>::asMatrix() const
{
	return *(Matrix<T, 4, 1>*)this;
}

//------------------------------------------------------------------------------
//
template<class T>
const Matrix<T, 1, 4>& Point<T, 4>::asTMatrix() const
{
	return *(Matrix<T, 1, 4>*)this;
}

template<class U, class T> 
static inline Point<T,4> operator * (const U &lhs, const Point<T,4> &rhs)
{
	return rhs * lhs;
}

template<class T, class U>
static inline Point<U,4> operator * (const Matrix<T, 4, 4> &lhs, const Point<U,4> &rhs)
{
	return lhs * rhs.asTMatrix();
}

//------------------------------------------------------------------------------
//
template<class T>
std::string Point<T, 4>::serialize() const
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
Point<T, 4> Point<T, 4>::deSerialize(const std::string &str)
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
int Point<T, 4>::size()
{
	return 4;
}

//------------------------------------------------------------------------------
//
template<class T> template<class U>
Point<U, 4> Point<T, 4>::cast() const
{
	return Point<U, 4>(static_cast<U>(x), static_cast<U>(y), static_cast<U>(z), static_cast<U>(w));
}



} // namespace seed


#endif // __GEOMETRY_POINT4_INLINE__
