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
#ifndef __GEOMETRY_POINT2__
#define __GEOMETRY_POINT2__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "Point.h"

namespace seed {

//==============================================================================
//	CLASS Point2
//==============================================================================

//	+ : addition of points
//	- : different of points
//	* : dot product or scalar multiplication
//	/ : scalar division
//	^ : cross product (determinant)
//	~ : perpendicular

template<class T>
class Point<T, 2>
{
public:
	Point();
	Point(T inX, T inY);
	Point(const Point<T, 1> &inX, const Point<T, 1> &inY);
	Point(const T &inX, const Point<T, 1> &inY);
	Point(const Point<T, 1> &inX, const T &inY);
	explicit Point(T inVal);
	explicit Point(const T *inVal);
	Point(const Matrix<T, 1, 2> &rhs);
	Point(const Point &rhs);

	template<class U>
	explicit Point(const Point<U, 2> &rhs);

	Point& operator = (const Point &rhs);
	Point& operator = (const Matrix<T, 1, 2> &rhs);
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
	T operator ^ (const Point &rhs) const;

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
	Point operator ~ () const;

	void setLength(double aLength);

	double length() const;
	T length2() const;

	void scale(double newLength);
	Point scaled(double newLength) const;

	Point normalized() const;
	void normalize();

	Point perpendicular() const;

	Matrix<T, 1, 2>& asTMatrix();
	const Matrix<T, 1, 2>& asTMatrix() const;
	Matrix<T, 2, 1>& asMatrix();
	const Matrix<T, 2, 1>& asMatrix() const;
	bool hasNan() const;
	bool hasInf() const;

	static int size();
	std::string serialize() const;
	static Point deSerialize(const std::string &str);

	template<class U>
	Point<U, 2> cast() const;

	Point<T, 1> project() const { return Point<T, 1>(x)/y; }

public:
	IMPLEMENT_POINT_ACCESSOR2(x,x); IMPLEMENT_POINT_ACCESSOR2(x,y);
	IMPLEMENT_POINT_ACCESSOR2(y,x); IMPLEMENT_POINT_ACCESSOR2(y,y);

	IMPLEMENT_POINT_ACCESSOR3(x,x,x); IMPLEMENT_POINT_ACCESSOR3(x,x,y);
	IMPLEMENT_POINT_ACCESSOR3(x,y,x); IMPLEMENT_POINT_ACCESSOR3(x,y,y);
	IMPLEMENT_POINT_ACCESSOR3(y,x,x); IMPLEMENT_POINT_ACCESSOR3(y,x,y);
	IMPLEMENT_POINT_ACCESSOR3(y,y,x); IMPLEMENT_POINT_ACCESSOR3(y,y,y);

	IMPLEMENT_POINT_ACCESSOR4(x,x,x,x); IMPLEMENT_POINT_ACCESSOR4(x,x,x,y);
	IMPLEMENT_POINT_ACCESSOR4(x,x,y,x); IMPLEMENT_POINT_ACCESSOR4(x,x,y,y);
	IMPLEMENT_POINT_ACCESSOR4(x,y,x,x); IMPLEMENT_POINT_ACCESSOR4(x,y,x,y);
	IMPLEMENT_POINT_ACCESSOR4(x,y,y,x); IMPLEMENT_POINT_ACCESSOR4(x,y,y,y);

	IMPLEMENT_POINT_ACCESSOR4(y,x,x,x); IMPLEMENT_POINT_ACCESSOR4(y,x,x,y);
	IMPLEMENT_POINT_ACCESSOR4(y,x,y,x); IMPLEMENT_POINT_ACCESSOR4(y,x,y,y);
	IMPLEMENT_POINT_ACCESSOR4(y,y,x,x); IMPLEMENT_POINT_ACCESSOR4(y,y,x,y);
	IMPLEMENT_POINT_ACCESSOR4(y,y,y,x); IMPLEMENT_POINT_ACCESSOR4(y,y,y,y);

public:
	T x;
	T y;
};

template<class U, class T>
static inline Point<T, 2> operator * (const U &lhs, const Point<T, 2> &rhs);

//==============================================================================
//	TYPE DECLARATION
//==============================================================================
typedef Point<float, 2> 	Point2f;
typedef Point<int, 2> 		Point2i;
typedef Point<double, 2>	Point2d;

} // namespace seed


//==============================================================================
//	INLINED CODE
//==============================================================================
#include "src/Point2.inline.h"

namespace sd = seed;

#endif // __GEOMETRY_POINT2__
