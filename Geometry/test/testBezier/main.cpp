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
#include "Generic/Geometry/Bezier.h"
#include "Generic/Geometry/Point2.h"

#ifdef GENERIC_LAYER_NAMESPACE
using namespace GENERIC_LAYER_NAMESPACE;
#endif

int main(int argc, const char *argv[])
{
	Point2f curve[] = {
		Point2f(0, 0),  // pt
		Point2f(1, 1),  // ctrl
		Point2f(2, 0),  // pt
		Point2f(3, -1), // ctrl
		Point2f(4, 0),  // pt
	};
	
	Point2f curve2[] = {
		Point2f(0, 0),  // pt
		Point2f(1, 1),  // ctrl
		Point2f(1, 1),  // ctrl
		Point2f(2, 0),  // pt
		Point2f(3, -1), // ctrl
		Point2f(3, -1), // ctrl
		Point2f(4, 0),  // pt
	};

	int steps = 100;
	for (int i = 0; i < steps; ++i)
	{
		float t = i/(steps-1.0);

		Point2f pt;
		BezierCurve::evalQuadratic(curve, curve+sizeof(curve)/sizeof(Point2f), t, &pt);

		Point2f pt2;
		BezierCurve::evalCubic(curve2, curve2+sizeof(curve2)/sizeof(Point2f), t, &pt2);
		printf("[%.2f] (%.2f %.2f) / (%.2f %.2f)\n", t, pt.x, pt.y, pt2.x, pt2.y);
	}
	

	return 0;
}
