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
#ifndef __GENERIC_BASE_WINDOWS__
#define __GENERIC_BASE_WINDOWS__

#ifdef WIN32

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#ifndef _WIN32_WINNT 
#define _WIN32_WINNT 0x0501
#endif

#pragma warning(push)
#include <windows.h>
#pragma warning(pop)

#pragma warning(push)
#pragma warning (disable: 4548) // stl doesn't like // expression before comma has no effect; expected expression with side-effect
#include <malloc.h>
#pragma warning(pop)
#include <math.h>

#ifdef __cplusplus
#define _DO_NOT_USE_NULLPTR_IN_ATL
#pragma warning(push)
#pragma warning (disable: 4619) // there is no warning number '####'
#pragma warning (disable: 4987) // nonstandard extension used
#pragma warning (disable: 4191) // W3 'operator/operation' : unsafe conversion from 'type of expression' to 'type required'
#include <AtlBase.h>
#include <AtlConv.h>
#include <tchar.h>
#pragma warning(pop)
#ifdef UNICODE
#define MK_ATON(x)	A2W(x)
#define MK_NTOA(x)	W2A(x)
#define MK_T(x) L ## x
#define NCHAR WCHAR
#define nstrcmp wcscmp
#define nstrcpy wcscpy
#else
#define MK_ATON(x)	(x)
#define MK_NTOA(x)	(x)
#define MK_T(x) (x)
#define NCHAR CHAR
#define nstrcmp strcmp
#define nstrcpy strcpy
#endif
#endif

#ifndef M_PI
#ifdef __cplusplus
static const double M_PI_V = 2 * acos(0.0);
#else
static const double M_PI_V = 3.14159265358979323846264f;
#endif
#define M_PI M_PI_V
#endif

#ifdef __cplusplus
#include <cmath>
namespace std {
#else
#include <math.h>
#define inline __inline
#endif

static __inline BOOL isnan(double x) {return ((x) != (x));}

static __inline BOOL isinf(double x)
{
    int expon = 0;
    double val = frexp (x, &expon);
    if (expon == 1025) {
        if (val == 0.5) {
            return TRUE;
        } else if (val == -0.5) {
            return TRUE;
        } else {
            return FALSE;
        }
	} else {
        return FALSE;
	}
}

#ifdef __cplusplus
}
#endif

#endif

#endif	//	__GENERIC_BASE_WINDOWS__
