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
#ifndef __GEOMETRY_QUAT__
#define __GEOMETRY_QUAT__


//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================

//==============================================================================
//	FORWARD DECLARATIONS
//==============================================================================
namespace seed {

template<class T, int S> class Point;
template<class T, int W, int H> class Matrix;

//==============================================================================
//	CLASS Quat
//==============================================================================
template<class T>
class Quat
{
public:
	Quat();
	Quat(T inW, T inX, T inY, T inZ);
	Quat(const Point<T,3> &axis, T angle);
	Quat(const Matrix<T, 1, 4> &rhs);
	Quat& operator = (const Matrix<T, 1, 4> &rhs);
	Quat(const Quat &rhs);
	Quat& operator = (const Quat &rhs);
	bool operator == (const Quat &rhs) const;
	bool operator != (const Quat &rhs) const;
	bool operator < (const Quat &rhs) const;
	bool operator <= (const Quat &rhs) const;
	bool operator > (const Quat &rhs) const;
	bool operator >= (const Quat &rhs) const;
	const T& operator [] (int index) const;
	operator T*();
	operator const T*() const;
	Quat operator + (const Quat &rhs) const;
	Quat operator - (const Quat &rhs) const;
	Quat operator * (const Quat &rhs) const;

public:
	
	Quat operator * (const T &rhs) const;
	Quat operator / (const T &rhs) const;
	Quat& operator += (const Quat &rhs);
	Quat& operator -= (const Quat &rhs);
	Quat& operator *= (const T &rhs);
	Quat& operator /= (const T &rhs);
	Quat& operator - ();
	double length();
	T length2();
	Quat& scale(double newLength);
	Quat& normalize();
	Quat conjugate();
	Quat unitInverse();	//	assumes we have a unit quaternion
	Quat inverse();
	void to4x4Matrix(Matrix<T, 4, 4> *outMatrix);
	void to3x3Matrix(Matrix<T, 3, 3> *outMatrix);

public:
	T w;
	T x;
	T y;
	T z;
};


template<class T>
static inline Quat<T> operator * (const T &lhs, const Quat<T> &rhs);

typedef Quat<float> 	Quatf;
typedef Quat<double>	Quatd;

} // namespace seed


//==============================================================================
//	INLINED CODE
//==============================================================================
#include "src/Quat.inline.h"

#endif // __GEOMETRY_QUAT__
