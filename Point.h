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
#ifndef __GEOMETRY_POINT__
#define __GEOMETRY_POINT__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include <string>

namespace seed {

template<class T, int W, int H> class Matrix;

//==============================================================================
//	CLASS Point
//==============================================================================
template<class T, int SIZE>
class Point
{
public:
	Point();
	explicit Point(const T *ptData);

	explicit Point(const T value);
	Point(const Matrix<T, 1, SIZE> &rhs);
	Point(const Point &rhs);
	
	Point& operator = (const Matrix<T, 1, SIZE> &rhs);
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

	Matrix<T, 1, SIZE>& asMatrix();
	const Matrix<T, 1, SIZE>& asMatrix() const;
	const Matrix<T, SIZE, 1>& asTMatrix() const;
	Matrix<T, SIZE, 1>& asTMatrix();

	std::string serialize() const;
	static Point deSerialize(const std::string &str);

	template<class U>
	Point<U, SIZE> cast() const;

public:
	static int size();
	T coords[SIZE];
};

#define IMPLEMENT_POINT_ACCESSOR2(a,b)\
Point<T, 2> a##b() const\
{\
	return Point<T, 2>(a, b);\
}

#define IMPLEMENT_POINT_ACCESSOR3(a, b, c)\
Point<T, 3> a##b##c() const\
{\
	return Point<T, 3>(a, b, c);\
}


#define IMPLEMENT_POINT_ACCESSOR4(a, b, c, d)\
Point<T, 4> a##b##c##d() const\
{\
	return Point<T, 4>(a, b, c, d);\
}

} // namespace seed

//==============================================================================
//	INLINED CODE
//==============================================================================
#include "Point1.h"
#include "Point2.h"
#include "Point3.h"
#include "Point4.h"
#include "src/Point.inline.h"

namespace sd = seed;

#endif // __GEOMETRY_POINT__
