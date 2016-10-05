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
#ifndef __GEOMETRY_RECT__
#define __GEOMETRY_RECT__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "Point2.h"
#include "Matrix.h"
#include "../Math/Math.h"


namespace seed {

//==============================================================================
//	CLASS Rect
//==============================================================================

template<class T>
class Rect
{
public:
	typedef Point<T, 2> Point2;

	Rect()
	:
		pos(),
		size()
	{}
	
	static Rect<T> boundingBox(const Point2 &pt1, const Point2 &pt2, const Point2 &pt3, const Point2 &pt4)
	{
		T xMin = Math::min(Math::min(Math::min(pt1.x, pt2.x), pt3.x), pt4.x);
		T yMin = Math::min(Math::min(Math::min(pt1.y, pt2.y), pt3.y), pt4.y);
		T xMax = Math::max(Math::max(Math::max(pt1.x, pt2.x), pt3.x), pt4.x);
		T yMax = Math::max(Math::max(Math::max(pt1.y, pt2.y), pt3.y), pt4.y);
		return Rect<T>(xMin, yMin, xMax-xMin, yMax-yMin);
	}

	static Rect<T> boundingBox(const Rect<T> &lhs, const Rect<T> &rhs)
	{
		T x1 = Math::min(lhs.pos.x, rhs.pos.x);
		T y1 = Math::min(lhs.pos.y, rhs.pos.y);
		T x2 = Math::max(lhs.pos.x+lhs.size.x, rhs.pos.x+rhs.size.x);
		T y2 = Math::max(lhs.pos.y+lhs.size.y, rhs.pos.y+rhs.size.y);
		return Rect<T>(x1, y1, x2-x1, y2-y1);
	}

	void getFourPoints(Point2 points[4])
	{
		points[0] = Point2(pos.x				, pos.y + size.y	);
		points[1] = Point2(pos.x				, pos.y				);
		points[2] = Point2(pos.x + size.x	, pos.y + size.y	);
		points[3] = Point2(pos.x + size.x	, pos.y				);
	}


	Rect(const T &x, const T &y, const T &width, const T &height)
	:
		pos(x, y),
		size(width, height)
	{}
	static Rect rectBetweenPoints(const Point2 &pt1, const Point2 &pt2)
	{
		if (pt1.x < pt2.x)
		{
			if (pt1.y < pt2.y)
				return Rect(pt1.x, pt1.y, pt2.x-pt1.x, pt2.y-pt1.y);
			else
				return Rect(pt1.x, pt2.y, pt2.x-pt1.x, pt1.y-pt2.y);
		}
		else
		{
			if (pt1.y < pt2.y)
				return Rect(pt2.x, pt1.y, pt1.x-pt2.x, pt2.y-pt1.y);
			else
				return Rect(pt2.x, pt2.y, pt1.x-pt2.x, pt1.y-pt2.y);
		}
	}

	Rect(const Point2 &inPos, const Point2 &inSize)
	:
		pos(inPos),
		size(inSize)
	{}

	Rect(const Point2 &inPos, const T &width, const T &height)
	:
		pos(inPos),
		size(width, height)
	{}

	Rect(const T &x, const T &y, const Point2 &inSize)
	:
		pos(x, y),
		size(inSize)
	{}

	Rect(const Rect &rhs)
	:
		pos(rhs.pos),
		size(rhs.size)
	{}

	Rect& operator = (const Rect &rhs)
	{
		pos = rhs.pos;
		size = rhs.size;
		return *this;
	}
	
	T area() const
	{
		return size.x*size.y;
	}

	bool operator == (const Rect &rhs) const
	{
		return (rhs.pos == pos) && (rhs.size == size);
	}
	
	bool operator != (const Rect &rhs) const
	{
		return (rhs.pos != pos) || (rhs.size != size);
	}

	bool operator < (const Rect &rhs) const
	{
		return (area() < rhs.area());
	}
	
	bool operator <= (const Rect &rhs) const
	{
		return (area() <= rhs.area());
	}

	bool operator > (const Rect &rhs) const
	{
		return (area() > rhs.area());
	}

	bool operator >= (const Rect &rhs) const
	{
		return (area() >= rhs.area());
	}
	
	T& operator [] (int index)
	{
		return reinterpret_cast<T*>(this)[index];
	}

	const T& operator [] (int index) const
	{
		return reinterpret_cast<const T*>(this)[index];
	}

	operator T*()
	{
		return reinterpret_cast<T*>(this);
	}
	
	operator const T*() const
	{
		return reinterpret_cast<const T*>(this);
	}

	void grow(const T amount)
	{
		pos.x -= amount;
		pos.y -= amount;
		size.x += 2*amount;
		size.y += 2*amount;
	}

	// There is no obvious meaning in adding or substracting a rect from another.
	// If this operation is realy useful, we should name it, not use an operator.
// 	//	did you grow a rect today?	
// 	Rect operator + (const Rect &rhs) const
// 	{
// 		return Rect(pos+rhs.pos, size+rhs.size);
// 	}
// 	
// 	Rect operator - (const Rect &rhs) const
// 	{
// 		return Rect(pos-rhs.pos, size-rhs.size);
// 	}


	//	intersection
	Rect operator * (const Rect &rhs) const
	{
		//	should we handle cases where the size is negative?
		T x1 = Math::max(pos.x, rhs.pos.x);
		T y1 = Math::max(pos.y, rhs.pos.y);
		T x2 = Math::min(pos.x+size.x, rhs.pos.x+rhs.size.x);
		T y2 = Math::min(pos.y+size.y, rhs.pos.y+rhs.size.y);
		
		return Rect(x1, y1, x2-x1, y2-y1);
	}

	//	defined as bounding box	
/*	USE boundingBox instead
	Rect operator ^ (const Rect &rhs) const
	{
		T x1 = Math::min(pos.x, rhs.pos.x);
		T y1 = Math::min(pos.y, rhs.pos.y);
		T x2 = Math::max(pos.x+size.x, rhs.pos.x+rhs.size.x);
		T y2 = Math::max(pos.y+size.y, rhs.pos.y+rhs.size.y);
		
		return Rect(x1, y1, x2-x1, y2-y1);
	}
*/

	//	only changes the size - not the position
	Rect operator * (const T &rhs) const
	{
		return Rect(pos, size*rhs);
	}

	Rect operator / (const T &rhs) const
	{
		return Rect(pos, size/rhs);
	}

	// See comment about plus and minus operator.
// 	Rect& operator += (const Rect &rhs)
// 	{
// 		return *this = *this + rhs;
// 	}
// 	
// 	Rect& operator -= (const Rect &rhs)
// 	{
// 		return *this = *this - rhs;
// 	}

	Rect& operator *= (const T &rhs)
	{
		return *this = *this * rhs;
	}

	Rect& operator /= (const T &rhs)
	{
		return *this = *this / rhs;
	}

//	No idea for now...  	 
//	Rect& operator - ()
//	{
//		x = -x, y = -y;
//		return *this;
//	}
	
	//	transpose
	Rect& operator ~ ()
	{
		return *this = Rect(pos, size.y, size.x);
	}

	Rect& operator += (const Point2 &rhs)
	{
		return move(rhs);
	}

	Rect& move(const Point2 &offset)
	{
		pos += offset;
		return *this;
	}

	
	Rect& scaleWidth(T newWidth)
	{
		assert(size.x != 0);
		size.y = size.y*newWidth/size.x;
		size.x = newWidth;
		return *this;
	}

	Rect& scaleHeight(T newHeight)
	{
		assert(size.y != 0);
		size.x = size.x*newHeight/size.y;
		return *this;
	}

	Matrix<T, 2, 4> asMatrix()
	{
		Matrix<T, 2, 4> m;
		m[0][0] = pos.x;			m[0][1] = pos.y;
		m[1][0] = pos.x + size.x;	m[1][1] = pos.y;
		m[2][0] = pos.x + size.x;	m[2][1] = pos.y + size.y;
		m[3][0] = pos.x;			m[3][1] = pos.y + size.y;
		return m;
	}

	Matrix<T, 4, 2> asTMatrix()
	{
		Matrix<T, 4, 2> m;
		m[0][0] = pos.x;			m[1][0] = pos.y;
		m[0][1] = pos.x + size.x;	m[1][1] = pos.y;
		m[0][2] = pos.x + size.x;	m[1][2] = pos.y + size.y;
		m[0][3] = pos.x;			m[1][3] = pos.y + size.y;
		return m;
	}
	
	bool contains(const Point2 &pt) const
	{
		return 	((pt.x >= pos.x) && (pt.y >= pos.y) &&
				 (pt.x < pos.x + size.x) && (pt.y < pos.y + size.y));
	}
	
	void centerToRect(const Rect &rhs)
	{
		pos.x = (rhs.size.x-size.x)/2 + rhs.pos.x;
		pos.y = (rhs.size.y-size.y)/2 + rhs.pos.y;
	}

	Rect& fitToRect(const Rect &rhs)
	{
		T wp = rhs.size.x, hp = rhs.size.y;
		T w = size.x, h = size.y;

		T fw = w * hp / h;
		
		if (fw <= wp)
		{
			size.x = fw;
			size.y = hp;
		}
		else
		{
			T fh = h * wp / w;
			size.x = wp;
			size.y = fh;
		}
		
		//ASSERT(size.x <= wp);
		//ASSERT(size.y <= hp);
		
		pos.x = rhs.pos.x + (wp - size.x)/2;
		pos.y = rhs.pos.y + (hp - size.y)/2;
		return *this;
	}

	std::string serialize() const
	{
		char str[1024];
		sprintf(str, "{%.8f, %.8f, %.8f, %.8f}", double(pos.x), double(pos.y), double(size.x), double(size.y));
		return str;
	}

	static Rect deSerialize(const std::string &str)
	{
		Rect<T> r(0, 0, 0, 0);
		char buf[2048];
		strcpy(buf, str.c_str());

		char *tok = strtok(buf, " \t\r\n{,}");
		if (!tok)	return r;
		double val;
		sscanf(tok, "%lf", &val);
		r.pos.x = val;

		tok = strtok(NULL, " \t\r\n{,}");
		if (!tok)	return r;
		sscanf(tok, "%lf", &val);
		r.pos.y = val;

		tok = strtok(NULL, " \t\r\n{,}");
		if (!tok)	return r;
		sscanf(tok, "%lf", &val);
		r.size.x = val;

		tok = strtok(NULL, " \t\r\n{,}");
		if (!tok)	return r;
		sscanf(tok, "%lf", &val);
		r.size.y = val;

		return r;
	}

	T top() { return pos.y + size.y; }
	T left() { return pos.x; }
	T right() { return pos.x + size.x; }
	T bottom() { return pos.y; }

	Point2 topLeft() const    { return Point2(pos.x, pos.y+size.y); }
	Point2 bottomLeft() const { return Point2(pos.x, pos.y); }
	Point2 topRight() const   { return Point2(pos.x+size.x, pos.y+size.y); }
	Point2 bottomRight() const{ return Point2(pos.x+size.x, pos.y); }

public:
	Point2 pos;
	Point2 size;
};

template<class T>
static inline Rect<T> operator * (const T &lhs, const Rect<T> &rhs)
{
	return rhs * lhs;
}

typedef Rect<float> 	Rectf;
typedef Rect<double>	Rectd;
typedef Rect<int> 		Recti;

} // namespace seed

#endif // __GEOMETRY_RECT__
