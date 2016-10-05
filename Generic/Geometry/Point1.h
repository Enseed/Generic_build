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
#ifndef __GEOMETRY_POINT1__
#define __GEOMETRY_POINT1__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "Point.h"

namespace seed {

//==============================================================================
//	CLASS Point1
//==============================================================================
template<class T>
class Point<T, 1>
{
public:
	Point();
	explicit Point(T inX);
	Point(const Matrix<T, 1, 1> &rhs);
	Point(const Point &rhs);

	Point& operator = (const Point &rhs);
	Point& operator = (const Matrix<T, 1, 1> &rhs);

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
	Matrix<T, 1, 1>& asMatrix();
	const Matrix<T, 1, 1>& asMatrix() const;
	Matrix<T, 1, 1>& asTMatrix();
	const Matrix<T, 1, 1>& asTMatrix() const;
	bool hasNan() const;
	bool hasInf() const;


	static int size();
	std::string serialize() const;
	static Point deSerialize(const std::string &str);

	template<class U>
	Point<U, 1> cast() const;

public:
	T x;

public:
	IMPLEMENT_POINT_ACCESSOR2(x,x)
	IMPLEMENT_POINT_ACCESSOR3(x, x, x)
	IMPLEMENT_POINT_ACCESSOR4(x, x, x, x)

};

template<class U, class T>
static inline Point<T, 1> operator * (const U &lhs, const Point<T, 1> &rhs);

//==============================================================================
//	TYPE DECLARATIONS
//==============================================================================
typedef Point<float, 1> 	Point1f;
typedef Point<int, 1> 		Point1i;
typedef Point<double, 1>	Point1d;

} // namespace seed


//==============================================================================
//	INLINED CODE
//==============================================================================
#include "src/Point1.inline.h"

namespace sd = seed;

#endif // __GEOMETRY_POINT1__
