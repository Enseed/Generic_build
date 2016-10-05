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
#ifndef __GEOMETRY_ROPE__
#define __GEOMETRY_ROPE__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "../Devel/Debug.h"
#include "Point2.h"
#include <math.h>
#include <vector>

namespace seed {

//==============================================================================
//	CLASS Rope
//==============================================================================

class Rope
{
public:

	Rope(float density = 0.05, float elasticity = 0.1f, float damping = 0.1f)
	:
		mDensity(density),
		mElasticity(elasticity),
		mDamping(damping),
		mPoints(),
		mVelocity()
	{}
	
	void clear()
	{
		mPoints.clear();
		mVelocity.clear();
	}

	void startAt(Point2f pt)
	{
		if (mPoints.size() > 0)
		{
			ASSERT(mPoints.size() >= 2);
			
			Point2f end = mPoints[mPoints.size()-1];
			Point2f dist = end-pt;
			float length = dist.length();
			int expectedNbPts = (int)(length*mDensity);
			int currentNbPts = mPoints.size() - 2;
			
			if (currentNbPts > expectedNbPts)
			{
				//	remove some points
				mPoints.erase(mPoints.begin(), mPoints.begin()+(currentNbPts-expectedNbPts+1));	//	+1 to erase the start point
				mVelocity.erase(mVelocity.begin(), mVelocity.begin()+(currentNbPts-expectedNbPts+1));	//	+1 to erase the start point

				mPoints.insert(mPoints.begin(), pt);
				mVelocity.insert(mVelocity.begin(), Point2f(0.0f, 0.0f));

				ASSERT((int)mPoints.size() == expectedNbPts + 2);
				ASSERT(mPoints.size() == mVelocity.size());
			}
			else
			{
				//	add some points
				int pointsToAdd = expectedNbPts - currentNbPts;
				Point2f oldStart = mPoints[0];
				mPoints.erase(mPoints.begin());
				mVelocity.erase(mVelocity.begin());

				int i;
				for (i = 0; i < pointsToAdd; ++i)
				{
					Point2f interPt = oldStart + (pt - oldStart)*(float)i/(pointsToAdd);
					mPoints.insert(mPoints.begin(), interPt);
					mVelocity.insert(mVelocity.begin(), Point2f(0.0f, 0.0f));
				} 

				mPoints.insert(mPoints.begin(), pt);
				mVelocity.insert(mVelocity.begin(), Point2f(0.0f, 0.0f));

				ASSERT((int)mPoints.size() == expectedNbPts + 2);
				ASSERT(mPoints.size() == mVelocity.size());
			}
		}
		else
		{
			mPoints.push_back(pt);	mVelocity.push_back(Point2f(0.0f, 0.0f));
			mPoints.push_back(pt);	mVelocity.push_back(Point2f(0.0f, 0.0f));
		}
	}

	void endAt(Point2f pt)
	{
		if (mPoints.size() > 0)
		{
		
		}
		else
		{
			mPoints.push_back(pt);	mVelocity.push_back(Point2f(0.0f, 0.0f));
			mPoints.push_back(pt);	mVelocity.push_back(Point2f(0.0f, 0.0f));
		}
	}
	
	void update(float t = 0.5f)
	{
		if (mPoints.size() < 2)	return;
		
		
		ASSERT(mPoints.size() == mVelocity.size());
		int i = 0;
		for (i = 1; i < static_cast<int>(mPoints.size())-1; ++i)
		{
			mVelocity[i].y += -0.02*t/mDensity;
		}

		for (i = 1; i < static_cast<int>(mPoints.size())-1; ++i)
		{
			Point2f movementVector;
			Point2f springVector;
			Point2f forceVector;
		
			float length;
			float forceScaler;
			float normalLength = 1.0f/mDensity;
	
			Point2f pos = mPoints[i];
	
			springVector = mPoints[i-1]-pos;
			length = springVector.length();
			forceScaler = (length - normalLength) / normalLength;
			springVector = springVector * (1/length);
			forceVector = springVector * forceScaler;
			forceVector = forceVector / mElasticity;
			
			
			mVelocity[i] += forceVector*t;
	
			springVector = mPoints[i+1]-pos;
			length = springVector.length();
			forceScaler = (length - normalLength) / normalLength;
			springVector = springVector * (1/length);
			forceVector = springVector * forceScaler;
			forceVector = forceVector / mElasticity;
			
			mVelocity[i] += forceVector*t;
		}

		for (i = 2; i < static_cast<int>(mPoints.size())-2; ++i)
		{
			Point2f movementVector;
			Point2f springVector;
			Point2f forceVector;
		
			float length;
			float forceScaler;
			float normalLength = 2.0f/mDensity;
	
			Point2f pos = mPoints[i];
	
			springVector = mPoints[i-2]-pos;
			length = springVector.length();
			forceScaler = (length - normalLength) / normalLength;
			springVector = springVector * (1/length);
			forceVector = springVector * forceScaler;
			forceVector = forceVector / mElasticity;
			
			
			mVelocity[i] += forceVector*t;
	
			springVector = mPoints[i+2]-pos;
			length = springVector.length();
			forceScaler = (length - normalLength) / normalLength;
			springVector = springVector * (1/length);
			forceVector = springVector * forceScaler;
			forceVector = forceVector / mElasticity;
			
			mVelocity[i] += forceVector*t;
		}


		for (i = 1; i < static_cast<int>(mPoints.size())	-1; ++i)
		{
			mPoints[i] += t*mVelocity[i];
		}

		for (i = 1; i < static_cast<int>(mPoints.size())-1; ++i)
		{
			mVelocity[i] *= pow(1.0f-mDamping, t);
		}
	}
	const std::vector<Point2f>& points() const
	{
		return mPoints;
	}
	

private:
	float mDensity;
	float mElasticity;
	float mDamping;
	
	std::vector<Point2f> mPoints;
	std::vector<Point2f> mVelocity;
};


} // namespace seed


#endif // __GEOMETRY_ROPE__
