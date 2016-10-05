/*******************************************************************************
 Copyright 2007 Enseed inc.
 
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
#ifndef __GENERIC_IMAGE_CONSTANTS__
#define __GENERIC_IMAGE_CONSTANTS__

#include "../Geometry/Matrix.h"
#include "../Base/Types.h"
#include "../Math/Float.h"

namespace seed {

//	y  = (y_r * r) + (y_g * g) + (y_b * b)
//	cb = 0.5 / (1 - y_b) * (B - Y)
//	cr = 0.5 / (1 - y_r) * (R - Y)




//==============================================================================
//	CLASS NTSCColors
//==============================================================================
class NTSCColors
{
public:
	static inline float y_r ();
	static inline float y_g ();
	static inline float y_b ();

	static inline float cb_r();
	static inline float cb_g();
	static inline float cb_b();

	static inline float cr_r();
	static inline float cr_g();
	static inline float cr_b();
	
	static inline float r_y ();
	static inline float r_cb();
	static inline float r_cr();
	
	static inline float g_y ();
	static inline float g_cb();
	static inline float g_cr();
	
	static inline float b_y ();
	static inline float b_cb();
	static inline float b_cr();

	static inline const Matrix3f& rgbToYCbCrMatrix3f();
	static inline const Matrix3d& rgbToYCbCrMatrix3d();

	static inline const Matrix3f& yCbCrToRGBMatrix3f();
	static inline const Matrix3d& yCbCrToRGBMatrix3d();

	static inline const Matrix4f& rgbaToYCbCrAMatrix4f();
	static inline const Matrix4d& rgbaToYCbCrAMatrix4d();

	static inline const Matrix4f& yCbCrAToRGBAMatrix4f();
	static inline const Matrix4d& yCbCrAToRGBAMatrix4d();
};


//==============================================================================
//	CLASS HDTVColors
//==============================================================================
class HDTVColors
{
public:
	static inline float y_r ();
	static inline float y_g ();
	static inline float y_b ();

	static inline float cb_r();
	static inline float cb_g();
	static inline float cb_b();

	static inline float cr_r();
	static inline float cr_g();
	static inline float cr_b();
	
	static inline float r_y ();
	static inline float r_cb();
	static inline float r_cr();
	
	static inline float g_y ();
	static inline float g_cb();
	static inline float g_cr();
	
	static inline float b_y ();
	static inline float b_cb();
	static inline float b_cr();

	static inline const Matrix3f& yCbCrToRGBMatrix3f();
	static inline const Matrix3d& yCbCrToRGBMatrix3d();

	static inline const Matrix3f& rgbToYCbCrMatrix3f();
	static inline const Matrix3d& rgbToYCbCrMatrix3d();

	static inline const Matrix4f& rgbaToYCbCrAMatrix4f();
	static inline const Matrix4d& rgbaToYCbCrAMatrix4d();

	static inline const Matrix4f& yCbCrAToRGBAMatrix4f();
	static inline const Matrix4d& yCbCrAToRGBAMatrix4d();
};

//==============================================================================
//	CLASS NTSCColors16
//==============================================================================

class NTSCColors16
{
public:
	static inline int32 y_r() ;
	static inline int32 y_g() ;
	static inline int32 y_b() ;

	static inline int32 cb_r();
	static inline int32 cb_g();
	static inline int32 cb_b();

	static inline int32 cr_r();
	static inline int32 cr_g();
	static inline int32 cr_b();
	
	static inline int32 r_y() ;
	static inline int32 r_cb();
	static inline int32 r_cr();
	
	static inline int32 g_y() ;
	static inline int32 g_cb();
	static inline int32 g_cr();
	
	static inline int32 b_y() ;
	static inline int32 b_cb();
	static inline int32 b_cr();
};

//==============================================================================
//	CLASS HDTVColors
//==============================================================================
class HDTVColors16
{
public:
	static const int32 y_r  =  13933;
	static const int32 y_g  =  46871;
	static const int32 y_b  =  4732;
	
	static const int32 cb_r = -7509;
	static const int32 cb_g = -25259;
	static const int32 cb_b =  32768;
	
	static const int32 cr_r =  32768;
	static const int32 cr_g = -29763;
	static const int32 cr_b = -3005;
	
	static const int32 r_y =   65536;
	static const int32 r_cb =  0;
	static const int32 r_cr =  103206;
	
	static const int32 g_y =   65536;
	static const int32 g_cb = -12276;
	static const int32 g_cr = -30679;
	
	static const int32 b_y  =  65536;
	static const int32 b_cb =  121609;
	static const int32 b_cr =  0;
};

} // namespace seed

#include "src/Constants.inline.h"

#endif // __GENERIC_IMAGE_CONSTANTS__
