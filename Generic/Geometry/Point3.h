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
#ifndef __GEOMETRY_POINT3__
#define __GEOMETRY_POINT3__


//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "Point.h"


namespace seed {

//==============================================================================
//	CLASS Point3
//==============================================================================

//	+ : addition of points
//	- : different of points
//	* : dot product or scalar multiplication
//	/ : scalar division
//	^ : cross product (determinant)
//	~ : perpendicular


template<class T>
class Point<T, 3>
{
public:
	Point();

	template<class U>
	explicit Point(const U *array);

	explicit Point(T inVal);
	Point(T inX, T inY, T inZ);

	Point(const T &inX, const T &inY, const Point<T, 1> &inZ);
	Point(const Point<T, 1> &inX, const T &inY, const T &inZ);

	Point(const Point<T, 1> &inX, const T &inY, const Point<T, 1> &inZ);
	Point(const Point<T, 1> &inX, const Point<T, 1> &inY, const T &inZ);
	Point(const T &inX, const Point<T, 1> &inY, const Point<T, 1> &inZ);

	Point(const Point<T, 1> &inX, const Point<T, 1> &inY, const Point<T, 1> &inZ);

	Point(const Point<T,2> &inXY, const T &inZ);
	Point(const T &inX, const Point<T, 2> &inYZ);

	Point(const Point<T,2> &inXY, const Point<T, 1> &inZ);
	Point(const Point<T, 1> &inX, const Point<T, 2> &inYZ);
	
	template<class U>
	explicit Point(const Point<U, 3> &rhs);

	Point(const Matrix<T, 1, 3> &rhs);


	Point& operator = (const Matrix<T, 1, 3> &rhs);
	Point& operator = (const Point &rhs);
	
	bool operator == (const Point &rhs) const;
	bool operator != (const Point &rhs) const;
	bool operator < (const Point &rhs) const;
	bool operator <= (const Point &rhs) const;
	bool operator > (const Point &rhs) const;
	bool operator >= (const Point &rhs) const;
	const T& operator [] (int index) const;
	T& operator [] (int index);
	T* ptr();
	const T* ptr() const;
	Point operator + (const Point &rhs) const;
	Point operator - (const Point &rhs) const;

	T operator * (const Point &rhs) const;
	Point operator ^ (const Point &rhs) const;

	template<class U>
	Point operator * (const U &rhs) const;

	template<class U>
	Point operator / (const U &rhs) const;
	Point& operator += (const Point &rhs);
	Point& operator -= (const Point &rhs);

	template<class U>
	Point& operator *= (const U &rhs);

	template<class U>
	Point& operator /= (const U &rhs);
	Point operator - () const;

	void setLength(double aLength);

	double length() const;
	T length2() const;
	
	Point scaled(double newLength) const;
	void scale(double newLength);

	Point normalized() const;
	void normalize();

	Matrix<T, 1, 3>& asTMatrix();
	const Matrix<T, 1, 3>& asTMatrix() const;
	Matrix<T, 3, 1>& asMatrix();
	const Matrix<T, 3, 1>& asMatrix() const;
	bool hasNan() const;
	bool hasInf() const;
	
	static int size();
	std::string serialize() const;
	static Point deSerialize(const std::string &str);

	template<class U>
	Point<U, 3> cast() const;

	Point<T, 2> project() const { return xy()/z; }

	IMPLEMENT_POINT_ACCESSOR2(x,x); IMPLEMENT_POINT_ACCESSOR2(x,y); IMPLEMENT_POINT_ACCESSOR2(x,z);
	IMPLEMENT_POINT_ACCESSOR2(y,x); IMPLEMENT_POINT_ACCESSOR2(y,y); IMPLEMENT_POINT_ACCESSOR2(y,z);
	IMPLEMENT_POINT_ACCESSOR2(z,x); IMPLEMENT_POINT_ACCESSOR2(z,y); IMPLEMENT_POINT_ACCESSOR2(z,z);

	IMPLEMENT_POINT_ACCESSOR3(x,x,x); IMPLEMENT_POINT_ACCESSOR3(x,x,y); IMPLEMENT_POINT_ACCESSOR3(x,x,z);
	IMPLEMENT_POINT_ACCESSOR3(x,y,x); IMPLEMENT_POINT_ACCESSOR3(x,y,y); IMPLEMENT_POINT_ACCESSOR3(x,y,z);
	IMPLEMENT_POINT_ACCESSOR3(x,z,x); IMPLEMENT_POINT_ACCESSOR3(x,z,y); IMPLEMENT_POINT_ACCESSOR3(x,z,z);
	IMPLEMENT_POINT_ACCESSOR3(y,x,x); IMPLEMENT_POINT_ACCESSOR3(y,x,y); IMPLEMENT_POINT_ACCESSOR3(y,x,z);
	IMPLEMENT_POINT_ACCESSOR3(y,y,x); IMPLEMENT_POINT_ACCESSOR3(y,y,y); IMPLEMENT_POINT_ACCESSOR3(y,y,z);
	IMPLEMENT_POINT_ACCESSOR3(y,z,x); IMPLEMENT_POINT_ACCESSOR3(y,z,y); IMPLEMENT_POINT_ACCESSOR3(y,z,z);
	IMPLEMENT_POINT_ACCESSOR3(z,x,x); IMPLEMENT_POINT_ACCESSOR3(z,x,y); IMPLEMENT_POINT_ACCESSOR3(z,x,z);
	IMPLEMENT_POINT_ACCESSOR3(z,y,x); IMPLEMENT_POINT_ACCESSOR3(z,y,y); IMPLEMENT_POINT_ACCESSOR3(z,y,z);
	IMPLEMENT_POINT_ACCESSOR3(z,z,x); IMPLEMENT_POINT_ACCESSOR3(z,z,y); IMPLEMENT_POINT_ACCESSOR3(z,z,z);

	IMPLEMENT_POINT_ACCESSOR4(x,x,x,x); IMPLEMENT_POINT_ACCESSOR4(x,x,x,y); IMPLEMENT_POINT_ACCESSOR4(x,x,x,z);
	IMPLEMENT_POINT_ACCESSOR4(x,x,y,x); IMPLEMENT_POINT_ACCESSOR4(x,x,y,y); IMPLEMENT_POINT_ACCESSOR4(x,x,y,z);
	IMPLEMENT_POINT_ACCESSOR4(x,x,z,x); IMPLEMENT_POINT_ACCESSOR4(x,x,z,y); IMPLEMENT_POINT_ACCESSOR4(x,x,z,z);
	IMPLEMENT_POINT_ACCESSOR4(x,y,x,x); IMPLEMENT_POINT_ACCESSOR4(x,y,x,y); IMPLEMENT_POINT_ACCESSOR4(x,y,x,z);
	IMPLEMENT_POINT_ACCESSOR4(x,y,y,x); IMPLEMENT_POINT_ACCESSOR4(x,y,y,y); IMPLEMENT_POINT_ACCESSOR4(x,y,y,z);
	IMPLEMENT_POINT_ACCESSOR4(x,y,z,x); IMPLEMENT_POINT_ACCESSOR4(x,y,z,y); IMPLEMENT_POINT_ACCESSOR4(x,y,z,z);
	IMPLEMENT_POINT_ACCESSOR4(x,z,x,x); IMPLEMENT_POINT_ACCESSOR4(x,z,x,y); IMPLEMENT_POINT_ACCESSOR4(x,z,x,z);
	IMPLEMENT_POINT_ACCESSOR4(x,z,y,x); IMPLEMENT_POINT_ACCESSOR4(x,z,y,y); IMPLEMENT_POINT_ACCESSOR4(x,z,y,z);
	IMPLEMENT_POINT_ACCESSOR4(x,z,z,x); IMPLEMENT_POINT_ACCESSOR4(x,z,z,y); IMPLEMENT_POINT_ACCESSOR4(x,z,z,z);

	IMPLEMENT_POINT_ACCESSOR4(y,x,x,x); IMPLEMENT_POINT_ACCESSOR4(y,x,x,y); IMPLEMENT_POINT_ACCESSOR4(y,x,x,z);
	IMPLEMENT_POINT_ACCESSOR4(y,x,y,x); IMPLEMENT_POINT_ACCESSOR4(y,x,y,y); IMPLEMENT_POINT_ACCESSOR4(y,x,y,z);
	IMPLEMENT_POINT_ACCESSOR4(y,x,z,x); IMPLEMENT_POINT_ACCESSOR4(y,x,z,y); IMPLEMENT_POINT_ACCESSOR4(y,x,z,z);
	IMPLEMENT_POINT_ACCESSOR4(y,y,x,x); IMPLEMENT_POINT_ACCESSOR4(y,y,x,y); IMPLEMENT_POINT_ACCESSOR4(y,y,x,z);
	IMPLEMENT_POINT_ACCESSOR4(y,y,y,x); IMPLEMENT_POINT_ACCESSOR4(y,y,y,y); IMPLEMENT_POINT_ACCESSOR4(y,y,y,z);
	IMPLEMENT_POINT_ACCESSOR4(y,y,z,x); IMPLEMENT_POINT_ACCESSOR4(y,y,z,y); IMPLEMENT_POINT_ACCESSOR4(y,y,z,z);
	IMPLEMENT_POINT_ACCESSOR4(y,z,x,x); IMPLEMENT_POINT_ACCESSOR4(y,z,x,y); IMPLEMENT_POINT_ACCESSOR4(y,z,x,z);
	IMPLEMENT_POINT_ACCESSOR4(y,z,y,x); IMPLEMENT_POINT_ACCESSOR4(y,z,y,y); IMPLEMENT_POINT_ACCESSOR4(y,z,y,z);
	IMPLEMENT_POINT_ACCESSOR4(y,z,z,x); IMPLEMENT_POINT_ACCESSOR4(y,z,z,y); IMPLEMENT_POINT_ACCESSOR4(y,z,z,z);
	
	IMPLEMENT_POINT_ACCESSOR4(z,x,x,x); IMPLEMENT_POINT_ACCESSOR4(z,x,x,y); IMPLEMENT_POINT_ACCESSOR4(z,x,x,z);
	IMPLEMENT_POINT_ACCESSOR4(z,x,y,x); IMPLEMENT_POINT_ACCESSOR4(z,x,y,y); IMPLEMENT_POINT_ACCESSOR4(z,x,y,z);
	IMPLEMENT_POINT_ACCESSOR4(z,x,z,x); IMPLEMENT_POINT_ACCESSOR4(z,x,z,y); IMPLEMENT_POINT_ACCESSOR4(z,x,z,z);
	IMPLEMENT_POINT_ACCESSOR4(z,y,x,x); IMPLEMENT_POINT_ACCESSOR4(z,y,x,y); IMPLEMENT_POINT_ACCESSOR4(z,y,x,z);
	IMPLEMENT_POINT_ACCESSOR4(z,y,y,x); IMPLEMENT_POINT_ACCESSOR4(z,y,y,y); IMPLEMENT_POINT_ACCESSOR4(z,y,y,z);
	IMPLEMENT_POINT_ACCESSOR4(z,y,z,x); IMPLEMENT_POINT_ACCESSOR4(z,y,z,y); IMPLEMENT_POINT_ACCESSOR4(z,y,z,z);
	IMPLEMENT_POINT_ACCESSOR4(z,z,x,x); IMPLEMENT_POINT_ACCESSOR4(z,z,x,y); IMPLEMENT_POINT_ACCESSOR4(z,z,x,z);
	IMPLEMENT_POINT_ACCESSOR4(z,z,y,x); IMPLEMENT_POINT_ACCESSOR4(z,z,y,y); IMPLEMENT_POINT_ACCESSOR4(z,z,y,z);
	IMPLEMENT_POINT_ACCESSOR4(z,z,z,x); IMPLEMENT_POINT_ACCESSOR4(z,z,z,y); IMPLEMENT_POINT_ACCESSOR4(z,z,z,z);
	
public:
	T x;
	T y;
	T z;
};

template<class U, class T>
static inline Point<T, 3> operator * (const U &lhs, const Point<T, 3> &rhs);


template<class T>
static inline Point<T, 3> operator * (const Matrix<T, 3, 3> &lhs, const Point<T, 3> &rhs);


typedef Point<float, 3> 	Point3f;
typedef Point<double, 3>	Point3d;
typedef Point<int, 3>		Point3i;

} // namespace seed


//==============================================================================
//	INLINED CODE
//==============================================================================
#include "src/Point3.inline.h"

namespace sd = seed;

#endif // __GEOMETRY_POINT3__
