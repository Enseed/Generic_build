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
#ifndef __GENERIC_IMAGE_CONSTANTS_INLINE__
#define __GENERIC_IMAGE_CONSTANTS_INLINE__


#include "../Constants.h"
#include "../../Geometry/Matrix.h"
#include "../../Geometry/Point4.h"
#include "../../Math/Float.h"
#include "../../Geometry/LUMatrixInverse.h"
#include <Generic/Base/Base.h>

namespace {


//	y  = (y_r * r) + (y_g * g) + (y_b * b)
//	cb = 0.5 / (1 - y_b) * (B - Y)
//	cr = 0.5 / (1 - y_r) * (R - Y)

template<class T>
seed::Matrix<T, 3, 3> YCbCrMatrixFromLuma(T lr, T lg, T lb)
{
	const T half = 0.5f;
	seed::Matrix<T, 3, 3> m;
	m[0][0] = lr;	m[0][1] = lg;	m[0][2] = lb;

	m[1][0] = half * -lr / (1-lb);
	m[1][1] = half * -lg / (1-lb);
	m[1][2] = half;

	m[2][0] = half;
	m[2][1] = half * -lg / (1-lr);
	m[2][2] = half * -lb / (1-lr);

	return m;
}

template<class T>
class YCbCr601ColorSpace
{
public:
	static const seed::Matrix<T, 3, 3>& forwardMatrix()
	{
		static seed::Matrix<T, 3, 3> sMatrix = YCbCrMatrixFromLuma<T>( 0.299f,  0.587f,  0.114f );
		return sMatrix;
	}

	static const seed::Matrix<T, 3, 3>& inverseMatrix()
	{
		static seed::Matrix<T, 3, 3> sMatrix = forwardMatrix().inversed();
		return sMatrix;
	}
};

typedef YCbCr601ColorSpace<float> YCbCr601ColorSpacef;
typedef YCbCr601ColorSpace<double> YCbCr601ColorSpaced;



template<class T>
class YCbCr709ColorSpace
{
public:
	static const seed::Matrix<T, 3, 3>& forwardMatrix()
	{
		static seed::Matrix<T, 3, 3> sMatrix = YCbCrMatrixFromLuma<T>( 0.2126f,  0.7152f,  0.0722f );
		return sMatrix;
	}

	static const seed::Matrix<T, 3, 3>& inverseMatrix()
	{
		static seed::Matrix<T, 3, 3> sMatrix = forwardMatrix().inversed();
		return sMatrix;
	}
};

typedef YCbCr709ColorSpace<float> YCbCr709ColorSpacef;
typedef YCbCr709ColorSpace<double> YCbCr709ColorSpaced;



static const float NTSCColors_y_r  = YCbCr601ColorSpacef::forwardMatrix()[0][0];
static const float NTSCColors_y_g  = YCbCr601ColorSpacef::forwardMatrix()[0][1];
static const float NTSCColors_y_b  = YCbCr601ColorSpacef::forwardMatrix()[0][2];

static const float NTSCColors_cb_r = YCbCr601ColorSpacef::forwardMatrix()[1][0];
static const float NTSCColors_cb_g = YCbCr601ColorSpacef::forwardMatrix()[1][1];
static const float NTSCColors_cb_b = YCbCr601ColorSpacef::forwardMatrix()[1][2];

static const float NTSCColors_cr_r = YCbCr601ColorSpacef::forwardMatrix()[2][0];
static const float NTSCColors_cr_g = YCbCr601ColorSpacef::forwardMatrix()[2][1];
static const float NTSCColors_cr_b = YCbCr601ColorSpacef::forwardMatrix()[2][2];

static const float NTSCColors_r_y  = YCbCr601ColorSpacef::inverseMatrix()[0][0];
static const float NTSCColors_r_cb = YCbCr601ColorSpacef::inverseMatrix()[0][1];
static const float NTSCColors_r_cr = YCbCr601ColorSpacef::inverseMatrix()[0][2];

static const float NTSCColors_g_y  = YCbCr601ColorSpacef::inverseMatrix()[1][0];
static const float NTSCColors_g_cb = YCbCr601ColorSpacef::inverseMatrix()[1][1];
static const float NTSCColors_g_cr = YCbCr601ColorSpacef::inverseMatrix()[1][2];

static const float NTSCColors_b_y  = YCbCr601ColorSpacef::inverseMatrix()[2][0];
static const float NTSCColors_b_cb = YCbCr601ColorSpacef::inverseMatrix()[2][1];
static const float NTSCColors_b_cr = YCbCr601ColorSpacef::inverseMatrix()[2][2];




static const float HDTVColors_y_r  = YCbCr709ColorSpacef::forwardMatrix()[0][0];
static const float HDTVColors_y_g  = YCbCr709ColorSpacef::forwardMatrix()[0][1];
static const float HDTVColors_y_b  = YCbCr709ColorSpacef::forwardMatrix()[0][2];

static const float HDTVColors_cb_r = YCbCr709ColorSpacef::forwardMatrix()[1][0];
static const float HDTVColors_cb_g = YCbCr709ColorSpacef::forwardMatrix()[1][1];
static const float HDTVColors_cb_b = YCbCr709ColorSpacef::forwardMatrix()[1][2];

static const float HDTVColors_cr_r = YCbCr709ColorSpacef::forwardMatrix()[2][0];
static const float HDTVColors_cr_g = YCbCr709ColorSpacef::forwardMatrix()[2][1];
static const float HDTVColors_cr_b = YCbCr709ColorSpacef::forwardMatrix()[2][2];

static const float HDTVColors_r_y =  YCbCr709ColorSpacef::inverseMatrix()[0][0];
static const float HDTVColors_r_cb = YCbCr709ColorSpacef::inverseMatrix()[0][1];
static const float HDTVColors_r_cr = YCbCr709ColorSpacef::inverseMatrix()[0][2];

static const float HDTVColors_g_y =  YCbCr709ColorSpacef::inverseMatrix()[1][0];
static const float HDTVColors_g_cb = YCbCr709ColorSpacef::inverseMatrix()[1][1];
static const float HDTVColors_g_cr = YCbCr709ColorSpacef::inverseMatrix()[1][2];

static const float HDTVColors_b_y  = YCbCr709ColorSpacef::inverseMatrix()[2][0];
static const float HDTVColors_b_cb = YCbCr709ColorSpacef::inverseMatrix()[2][1];
static const float HDTVColors_b_cr = YCbCr709ColorSpacef::inverseMatrix()[2][2];

static const int32 NTSCColors16_r_y  = seed::Float::round(seed::NTSCColors::r_y ()  * 65536);
static const int32 NTSCColors16_r_cb = seed::Float::round(seed::NTSCColors::r_cb() * 65536);
static const int32 NTSCColors16_r_cr = seed::Float::round(seed::NTSCColors::r_cr() * 65536);

static const int32 NTSCColors16_g_y  = seed::Float::round(seed::NTSCColors::g_y ()  * 65536);
static const int32 NTSCColors16_g_cb = seed::Float::round(seed::NTSCColors::g_cb() * 65536);
static const int32 NTSCColors16_g_cr = seed::Float::round(seed::NTSCColors::g_cr() * 65536);

static const int32 NTSCColors16_b_y  = seed::Float::round(seed::NTSCColors::b_y () * 65536);
static const int32 NTSCColors16_b_cb = seed::Float::round(seed::NTSCColors::b_cb() * 65536);
static const int32 NTSCColors16_b_cr = seed::Float::round(seed::NTSCColors::b_cr() * 65536);

static const int32 NTSCColors16_y_r  = seed::Float::round(seed::NTSCColors::y_r()  * 65536);
static const int32 NTSCColors16_y_g  = seed::Float::round(seed::NTSCColors::y_g()  * 65536);
static const int32 NTSCColors16_y_b  = seed::Float::round(seed::NTSCColors::y_b()  * 65536);

static const int32 NTSCColors16_cb_r = seed::Float::round(seed::NTSCColors::cb_r() * 65536);
static const int32 NTSCColors16_cb_g = seed::Float::round(seed::NTSCColors::cb_g() * 65536);
static const int32 NTSCColors16_cb_b = seed::Float::round(seed::NTSCColors::cb_b() * 65536);

static const int32 NTSCColors16_cr_r = seed::Float::round(seed::NTSCColors::cr_r() * 65536);
static const int32 NTSCColors16_cr_g = seed::Float::round(seed::NTSCColors::cr_g() * 65536);
static const int32 NTSCColors16_cr_b = seed::Float::round(seed::NTSCColors::cr_b() * 65536);


}
namespace seed {


inline float NTSCColors::y_r () { return NTSCColors_y_r ; }
inline float NTSCColors::y_g () { return NTSCColors_y_g ; }
inline float NTSCColors::y_b () { return NTSCColors_y_b ; }

inline float NTSCColors::cb_r() { return NTSCColors_cb_r; }
inline float NTSCColors::cb_g() { return NTSCColors_cb_g; }
inline float NTSCColors::cb_b() { return NTSCColors_cb_b; }

inline float NTSCColors::cr_r() { return NTSCColors_cr_r; }
inline float NTSCColors::cr_g() { return NTSCColors_cr_g; }
inline float NTSCColors::cr_b() { return NTSCColors_cr_b; }

inline float NTSCColors::r_y () { return NTSCColors_r_y ; }
inline float NTSCColors::r_cb() { return NTSCColors_r_cb; }
inline float NTSCColors::r_cr() { return NTSCColors_r_cr; }

inline float NTSCColors::g_y () { return NTSCColors_g_y ; }
inline float NTSCColors::g_cb() { return NTSCColors_g_cb; }
inline float NTSCColors::g_cr() { return NTSCColors_g_cr; }

inline float NTSCColors::b_y () { return NTSCColors_b_y ; }
inline float NTSCColors::b_cb() { return NTSCColors_b_cb; }
inline float NTSCColors::b_cr() { return NTSCColors_b_cr; }


inline float HDTVColors::y_r () { return HDTVColors_y_r ; }
inline float HDTVColors::y_g () { return HDTVColors_y_g ; }
inline float HDTVColors::y_b () { return HDTVColors_y_b ; }

inline float HDTVColors::cb_r() { return HDTVColors_cb_r; }
inline float HDTVColors::cb_g() { return HDTVColors_cb_g; }
inline float HDTVColors::cb_b() { return HDTVColors_cb_b; }

inline float HDTVColors::cr_r() { return HDTVColors_cr_r; }
inline float HDTVColors::cr_g() { return HDTVColors_cr_g; }
inline float HDTVColors::cr_b() { return HDTVColors_cr_b; }

inline float HDTVColors::r_y () { return HDTVColors_r_y ; }
inline float HDTVColors::r_cb() { return HDTVColors_r_cb; }
inline float HDTVColors::r_cr() { return HDTVColors_r_cr; }

inline float HDTVColors::g_y () { return HDTVColors_g_y ; }
inline float HDTVColors::g_cb() { return HDTVColors_g_cb; }
inline float HDTVColors::g_cr() { return HDTVColors_g_cr; }

inline float HDTVColors::b_y () { return HDTVColors_b_y ; }
inline float HDTVColors::b_cb() { return HDTVColors_b_cb; }
inline float HDTVColors::b_cr() { return HDTVColors_b_cr; }


inline int32 NTSCColors16::y_r () { return NTSCColors16_y_r ; }
inline int32 NTSCColors16::y_g () { return NTSCColors16_y_g ; }
inline int32 NTSCColors16::y_b () { return NTSCColors16_y_b ; }

inline int32 NTSCColors16::cb_r() { return NTSCColors16_cb_r; }
inline int32 NTSCColors16::cb_g() { return NTSCColors16_cb_g; }
inline int32 NTSCColors16::cb_b() { return NTSCColors16_cb_b; }

inline int32 NTSCColors16::cr_r() { return NTSCColors16_cr_r; }
inline int32 NTSCColors16::cr_g() { return NTSCColors16_cr_g; }
inline int32 NTSCColors16::cr_b() { return NTSCColors16_cr_b; }

inline int32 NTSCColors16::r_y () { return NTSCColors16_r_y ; }
inline int32 NTSCColors16::r_cb() { return NTSCColors16_r_cb; }
inline int32 NTSCColors16::r_cr() { return NTSCColors16_r_cr; }

inline int32 NTSCColors16::g_y () { return NTSCColors16_g_y ; }
inline int32 NTSCColors16::g_cb() { return NTSCColors16_g_cb; }
inline int32 NTSCColors16::g_cr() { return NTSCColors16_g_cr; }

inline int32 NTSCColors16::b_y () { return NTSCColors16_b_y ; }
inline int32 NTSCColors16::b_cb() { return NTSCColors16_b_cb; }
inline int32 NTSCColors16::b_cr() { return NTSCColors16_b_cr; }


inline static const Matrix3f& YCbCr601ToRGBMatrix()
{
	static Matrix3f sMatrix(YCbCr601ColorSpace<float>::forwardMatrix());
	return sMatrix;
}

inline static const Matrix3f& YCbCr601ToRGBInverseMatrix()
{
	static Matrix3f sMatrix(YCbCr601ColorSpace<float>::inverseMatrix());
	return sMatrix;
}



inline const Matrix4d& NTSCColors::rgbaToYCbCrAMatrix4d()
{
	static Matrix4d m = YCbCr601ColorSpace<double>::forwardMatrix().addCol(3, Point3d(0, 0, 0).asTMatrix()).addRow(3, Point4d(0, 0, 0, 1).asMatrix());
	return m;
}

inline const Matrix4d& NTSCColors::yCbCrAToRGBAMatrix4d()
{
	static Matrix4d m = rgbaToYCbCrAMatrix4d().inversed();
	return m;
}

inline const Matrix4f& NTSCColors::rgbaToYCbCrAMatrix4f()
{
	static Matrix4f m = YCbCr601ColorSpace<float>::forwardMatrix().addCol(3, Point3f(0, 0, 0).asTMatrix()).addRow(3, Point4f(0, 0, 0, 1).asMatrix());
	return m;
}

inline const Matrix4f& NTSCColors::yCbCrAToRGBAMatrix4f()
{
	static Matrix4f m = rgbaToYCbCrAMatrix4f().inversed();
	return m;
}



inline const Matrix4d& HDTVColors::rgbaToYCbCrAMatrix4d()
{
	static Matrix4d m = YCbCr709ColorSpace<double>::forwardMatrix().addCol(3, Point3d(0, 0, 0).asTMatrix()).addRow(3, Point4d(0, 0, 0, 1).asMatrix());
	return m;
}

inline const Matrix4d& HDTVColors::yCbCrAToRGBAMatrix4d()
{
	static Matrix4d m = rgbaToYCbCrAMatrix4d().inversed();
	return m;
}

inline const Matrix4f& HDTVColors::rgbaToYCbCrAMatrix4f()
{
	static Matrix4f m = YCbCr709ColorSpace<float>::forwardMatrix().addCol(3, Point3f(0, 0, 0).asTMatrix()).addRow(3, Point4f(0, 0, 0, 1).asMatrix());
	return m;
}

inline const Matrix4f& HDTVColors::yCbCrAToRGBAMatrix4f()
{
	static Matrix4f m = rgbaToYCbCrAMatrix4f().inversed();
	return m;
}





inline const Matrix3d& HDTVColors::rgbToYCbCrMatrix3d()
{
	return YCbCr709ColorSpace<double>::forwardMatrix();
}

inline const Matrix3d& HDTVColors::yCbCrToRGBMatrix3d()
{
	return YCbCr709ColorSpace<double>::inverseMatrix();
}

inline const Matrix3f& HDTVColors::rgbToYCbCrMatrix3f()
{
	return YCbCr709ColorSpace<float>::forwardMatrix();
}

inline const Matrix3f& HDTVColors::yCbCrToRGBMatrix3f()
{
	return YCbCr709ColorSpace<float>::inverseMatrix();
}



inline const Matrix3d& NTSCColors::rgbToYCbCrMatrix3d()
{
	return YCbCr601ColorSpace<double>::forwardMatrix();
}

inline const Matrix3d& NTSCColors::yCbCrToRGBMatrix3d()
{
	return YCbCr601ColorSpace<double>::inverseMatrix();
}

inline const Matrix3f& NTSCColors::rgbToYCbCrMatrix3f()
{
	return YCbCr601ColorSpace<float>::forwardMatrix();
}

inline const Matrix3f& NTSCColors::yCbCrToRGBMatrix3f()
{
	return YCbCr601ColorSpace<float>::inverseMatrix();
}



} // namespace seed

#endif // __GENERIC_IMAGE_CONSTANTS_INLINE__
