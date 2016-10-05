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
#ifndef __GEOMETRY_QUAT_INLINE__
#define __GEOMETRY_QUAT_INLINE__


//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "../Quat.h"
#include "../../Devel/Debug.h"
#include <cmath>
#include <limits>

namespace seed {


//==============================================================================
//	CLASS Quat
//==============================================================================
//------------------------------------------------------------------------------
//
template<class T>
Quat<T>::Quat()
:
	w(),
	x(),
	y(),
	z()
{}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T>::Quat(T inW, T inX, T inY, T inZ)
:
	w(inW),
	x(inX),
	y(inY),
	z(inZ)
{}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T>::Quat(const Point<T,3> &axis, T angle)
:
	w(),
	x(),
	y(),
	z()
{
	T sinAngleOver2 = sin(angle/2);
	w = cos(angle/2);
	x = reinterpret_cast<const T*>(&axis)[0]*sinAngleOver2;
	y = reinterpret_cast<const T*>(&axis)[1]*sinAngleOver2;
	z = reinterpret_cast<const T*>(&axis)[2]*sinAngleOver2;
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T>::Quat(const Matrix<T, 1, 4> &rhs)
:
	w(reinterpret_cast<const T*>(&rhs)[0]),
	x(reinterpret_cast<const T*>(&rhs)[1]),
	y(reinterpret_cast<const T*>(&rhs)[2]),
	z(reinterpret_cast<const T*>(&rhs)[3])
{}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T>& Quat<T>::operator = (const Matrix<T, 1, 4> &rhs)
{
	w = reinterpret_cast<const T*>(&rhs)[0];
	x = reinterpret_cast<const T*>(&rhs)[1];
	y = reinterpret_cast<const T*>(&rhs)[2];
	z = reinterpret_cast<const T*>(&rhs)[3];
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T>::Quat(const Quat<T> &rhs)
:
	w(rhs.w),
	x(rhs.x),
	y(rhs.y),
	z(rhs.z)
{}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T>& Quat<T>::operator = (const Quat<T> &rhs)
{
	w = rhs.w;
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
bool Quat<T>::operator == (const Quat<T> &rhs) const
{
	return (rhs.w == w) && (rhs.x == x) && (rhs.y == y) && (rhs.z == z);
}

//------------------------------------------------------------------------------
//
template<class T>
bool Quat<T>::operator != (const Quat<T> &rhs) const
{
	return (rhs.w != w) || (rhs.x != x) || (rhs.y != y) || (rhs.z != z);
}

//------------------------------------------------------------------------------
//
template<class T>
bool Quat<T>::operator < (const Quat<T> &rhs) const
{
	return (w < rhs.w) || ((w == rhs.w) && ((x < rhs.x) || ((x == rhs.x) && ((y < rhs.y) || ((y == rhs.y) && (z < rhs.z))))));
}

//------------------------------------------------------------------------------
//
template<class T>
bool Quat<T>::operator <= (const Quat<T> &rhs) const
{
	return (w < rhs.w) || ((w == rhs.w) && ((x < rhs.x) || ((x == rhs.x) && ((y < rhs.y) || ((y == rhs.y) && (z <= rhs.z))))));
}

//------------------------------------------------------------------------------
//
template<class T>
bool Quat<T>::operator > (const Quat<T> &rhs) const
{
	return (w > rhs.w) || ((w == rhs.w) && ((x > rhs.x) || ((x == rhs.x) && ((y > rhs.y) || ((y == rhs.y) && (z > rhs.z))))));
}

//------------------------------------------------------------------------------
//
template<class T>
bool Quat<T>::operator >= (const Quat<T> &rhs) const
{
	return (w > rhs.w) || ((w == rhs.w) && ((x > rhs.x) || ((x == rhs.x) && ((y > rhs.y) || ((y == rhs.y) && (z >= rhs.z))))));
}

//------------------------------------------------------------------------------
//
template<class T>
const T& Quat<T>::operator [] (int index) const
{
	return reinterpret_cast<const T*>(this)[index];
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T>::operator T*()
{
	return reinterpret_cast<T*>(this);
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T>::operator const T*() const
{
	return reinterpret_cast<const T*>(this);
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T> Quat<T>::operator + (const Quat<T> &rhs) const
{
	return Quat(x+rhs.x, y+rhs.y, z+rhs.z, w+rhs.w);
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T> Quat<T>::operator - (const Quat<T> &rhs) const
{
	return Quat(x-rhs.x, y-rhs.y, z-rhs.z, w-rhs.w);
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T> Quat<T>::operator * (const Quat<T> &rhs) const
{
	return Quat(
		w*rhs.w - x*rhs.x - y*rhs.y - z*rhs.z,
		w*rhs.x + x*rhs.w + y*rhs.z - z*rhs.y,
		w*rhs.y + y*rhs.w + z*rhs.x - x*rhs.z,
		w*rhs.z + z*rhs.w + x*rhs.y - y*rhs.x
	);
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T> Quat<T>::operator * (const T &rhs) const
{
	return Quat(w*rhs, x*rhs, y*rhs, z*rhs);
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T> Quat<T>::operator / (const T &rhs) const
{
	return Quat(w/rhs, x/rhs, y/rhs, z/rhs);
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T>& Quat<T>::operator += (const Quat<T> &rhs)
{
	w+= rhs.w; x += rhs.x; y += rhs.y; z += rhs.z;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T>& Quat<T>::operator -= (const Quat<T> &rhs)
{
	w -= rhs.w; x -= rhs.x; y -= rhs.y; z -= rhs.z;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T>& Quat<T>::operator *= (const T &rhs)
{
	*this = *this * rhs;

	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T>& Quat<T>::operator /= (const T &rhs)
{
	w /= rhs; x /= rhs; y /= rhs; z /= rhs;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T>& Quat<T>::operator - ()
{
	x = -x, y = -y; z = -z; w = -w;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
double Quat<T>::length()
{
	return sqrt(length2());
}

//------------------------------------------------------------------------------
//
template<class T>
T Quat<T>::length2()
{
	return w*w+x*x+y*y+z*z;
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T>& Quat<T>::scale(double newLength)
{
	ASSERTF(!std::numeric_limits<T>::is_integer, "scaling of integer vector is not defined.");
	double s = newLength/length();
	w *= s;	x *= s, y *= s; z *= s;
	return *this;
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T>& Quat<T>::normalize()
{
	ASSERTF(!std::numeric_limits<T>::is_integer, "scaling of integer vector is not defined.");
	return scale(1.0f);
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T> Quat<T>::conjugate()
{
	return Quat(w, -x, -y, -z);
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T> Quat<T>::unitInverse()	//	assumes we have a unit quaternion
{
	return conjugate();
}

//------------------------------------------------------------------------------
//
template<class T>
Quat<T> Quat<T>::inverse()
{
	return conjugate()/length2();
}

//------------------------------------------------------------------------------
//
template<class T>
void Quat<T>::to4x4Matrix(Matrix<T, 4, 4> *outMatrix)
{
	// avoid depending on Matrix.h
	T* m = reinterpret_cast<T*>(outMatrix);
	
	T xx = x*x;	T xy = x*y;
	T xz = x*z;	T xw = x*w;

	T yy = y*y;	T yz = y*z;
	T yw = y*w;

	T zz = z*z;	T zw = z*w;

	m[0*4+0] = 1-2*(yy+zz); m[1*4+0] =   2*(xy-zw); m[2*4+0] =   2*(xz+yw); m[3*4+0] = 0;
	m[0*4+1] =   2*(xy+zw); m[1*4+1] = 1-2*(xx+zz); m[2*4+1] =   2*(yz-xw); m[3*4+1] = 0;
	m[0*4+2] =   2*(xz-yw); m[1*4+2] =   2*(yz+xw); m[2*4+2] = 1-2*(xx+yy); m[3*4+2] = 0;
	m[0*4+3] =           0; m[1*4+3] =           0; m[2*4+3] =           0; m[3*4+3] = 1;
}

//------------------------------------------------------------------------------
//
template<class T>
void Quat<T>::to3x3Matrix(Matrix<T, 3, 3> *outMatrix)
{
	// avoid depending on Matrix.h
	T* m = reinterpret_cast<T*>(outMatrix);

	float xx = x*x;	float xy = x*y;
	float xz = x*z;	float xw = x*w;

	float yy = y*y;	float yz = y*z;
	float yw = y*w;

	float zz = z*z;	float zw = z*w;

	m[0*3+0] = 1-2*(yy+zz); m[1*3+0] =   2*(xy-zw); m[2*3+0] =   2*(xz+yw);
	m[0*3+1] =   2*(xy+zw); m[1*3+1] = 1-2*(xx+zz); m[2*3+1] =   2*(yz-xw);
	m[0*3+2] =   2*(xz-yw); m[1*3+2] =   2*(yz+xw); m[2*3+2] = 1-2*(xx+yy);
}

//------------------------------------------------------------------------------
//
template<class T>
static inline Quat<T> operator * (const T &lhs, const Quat<T> &rhs)
{
	return rhs * lhs;
}

} // namespace seed


#endif // __GEOMETRY_QUAT_INLINE__
