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
#ifndef __GEOMETRY_TRACKBALL_INLINE__
#define __GEOMETRY_TRACKBALL_INLINE__

//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================
#include "../TrackBall.h"
#include "../../Devel/Debug.h"

namespace seed {

//==============================================================================
// CLASS TrackBall
//==============================================================================
//------------------------------------------------------------------------------
//
TrackBall::TrackBall()
:
	mStartPos(),
	mStartSphPos(),
	mCenter(Point2f(0, 0)),
	mRadius(1)
{}

//------------------------------------------------------------------------------
//
TrackBall::TrackBall(float radius, const Point2f &center)
:
	mStartPos(),
	mStartSphPos(),
	mCenter(center),
	mRadius(radius)
{}

//------------------------------------------------------------------------------
//
TrackBall::TrackBall(const TrackBall &rhs)
:
	mStartPos(rhs.mStartPos),
	mStartSphPos(rhs.mStartSphPos),
	mCenter(rhs.mCenter),
	mRadius(rhs.mRadius)
{}

//------------------------------------------------------------------------------
//
TrackBall& TrackBall::operator = (const TrackBall &rhs)
{
	mStartPos = rhs.mStartPos;
	mStartSphPos = rhs.mStartSphPos;
	mCenter = rhs.mCenter;
	mRadius = rhs.mRadius;
	return *this;
}

//------------------------------------------------------------------------------
//
void TrackBall::beginTracking(Point2f pt)
{
	pt -= mCenter;
	mStartPos = pt;
	mStartSphPos = Point3f(pt.x, pt.y, mRadius);
}

//------------------------------------------------------------------------------
//
Quatf TrackBall::track(Point2f pt)
{
	pt -= mCenter;
	float angle = (pt-mStartPos).length()*4/mRadius;
	Point3f ptSph = Point3f(pt.x, pt.y, mRadius);
	Point3f axis = (ptSph ^ mStartSphPos).normalized();
	
	if (axis.hasNan()  || axis.hasInf())
		return Quatf(1, 0, 0, 0);
	
	return Quatf(axis, angle);
}

} // namespace seed

#endif // __GEOMETRY_TRACKBALL_INLINE__
