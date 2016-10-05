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
#ifndef __GEOMETRY_TRACKBALL__
#define __GEOMETRY_TRACKBALL__

//==============================================================================
//	TrackBall.h
//
//	This class implements a 3D trackball that can be used to convert mouse
//	drags on a 2D plane into 3D rotations.  We use quaternions, thus there
//	is no gimbal lock.
//
//	How to use:
//
//	//	radius is the radius of the ball, center is it's center on the 2D plane
//	TrackBall tBall(radius, Point2(xCenter, yCenter));
//
//	tBall.beginTracking(clickPoint);
//	...
//	Quatf qrot = tBall.track(dragPoint);
//
//	//	here, qrot is a quaternion containing the rotation, to convert to
//	//	angles as a rotation matrix:
//
//	myRot = qrot*myRot;	//	initially, myRot would be Quatf(1,0,0,0)
//	Matrix4f rot = myRot.as4x4Matrix();
//	
//==============================================================================

//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================
#include "Point2.h"
#include "Point3.h"
#include "Quat.h"

namespace seed {

//==============================================================================
// CLASS TrackBall
//==============================================================================
class TrackBall
{
public:
	TrackBall();
	TrackBall(float radius, const Point2f &center);
	TrackBall(const TrackBall &rhs);

	TrackBall& operator = (const TrackBall &rhs);

	void beginTracking(Point2f pt);
	Quatf track(Point2f pt);
	
private:
	Point2f mStartPos;
	Point3f mStartSphPos;
	Point2f mCenter;
	float   mRadius;
};

} // namespace seed

//==============================================================================
// INLINED CODE
//==============================================================================
#include "src/TrackBall.inline.h"

#endif // __GEOMETRY_TRACKBALL__
