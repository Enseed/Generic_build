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
#ifndef __GEOMETRY_ARCCURVE__
#define __GEOMETRY_ARCCURVE__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "Point2.h"
#include "../Math/Float.h"

namespace seed {


template<class T>
class ArcCurve
{
public:
	typedef Point<T, 2> PT;

	ArcCurve(const ArcCurve<T>& rhs)
	:
		mCenter(rhs.mCenter),
		mRadius(rhs.mRadius),
		mStartAngle(rhs.mStartAngle),
		mTotalAngle(rhs.mTotalAngle)
	{}
	
	ArcCurve<T>& operator = (const ArcCurve<T> &rhs)
	{
		mCenter = rhs.mCenter;
		mRadius = rhs.mRadius;
		mStartAngle = rhs.mStartAngle;
		mTotalAngle = rhs.mTotalAngle;
		return *this;
	}
	

	ArcCurve(PT center, float radius, float startAngle, float arcAngle)
	:
		mCenter(center),
		mRadius(radius),
		mStartAngle(startAngle),
		mTotalAngle(arcAngle)
	{}

	ArcCurve(float cx, float cy, float radius, float startAngle, float arcAngle)
	:
		mCenter(cx, cy),
		mRadius(radius),
		mStartAngle(startAngle),
		mTotalAngle(arcAngle)
	{}

	
	PT pos(T t) const
	{
		T currentAngle = angle(t);
		return mCenter + mRadius*PT(Float::cos(currentAngle), Float::sin(currentAngle));
	}
	
	float angle(T t) const
	{
		// let t = {0,1} be from {mStartAngle to mStartAngle+mTotalAngle}
		T deltaTheta = t*mTotalAngle;
		return mStartAngle + deltaTheta;
	}
	
	void setCenter(PT center)	{	mCenter = center;		}
	void setRadius(T radius)	{ 	mRadius = radius;		}
	void setStartAngle(T angle)	{	mStartAngle = angle;	}
	void setTotalAngle(T total)	{	mTotalAngle = total;	}

	PT center()	const		{	return mCenter;	}
	T radius() const 		{	return mRadius;	}
	T startAngle() const	{	return mStartAngle;	}
	T totalAngle() const	{	return mTotalAngle;	}

public:
	PT mCenter;
	T mRadius;
	T mStartAngle;
	T mTotalAngle;

};

typedef ArcCurve<float>		ArcCurvef;
typedef ArcCurve<double>	ArcCurved;

} // namespace seed


#endif // __GEOMETRY_ARCCURVE__
