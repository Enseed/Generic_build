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
#ifndef __GENERIC_IMAGE_COLOR_PROFILE__
#define __GENERIC_IMAGE_COLOR_PROFILE__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "../Base/Base.h"

//==============================================================================
//	==> WILL BE USED BY C FILES - DO NOT NAMESPACE <==
//==============================================================================
//#ifdef GENERIC_NAMESPACE
//namespace GENERIC_NAMESPACE {
//#endif

enum
{
	MK_COLORPROFILE_NONE = 0,
	MK_COLORPROFILE_UNCALIBRATED_LUMINANCE,
	MK_COLORPROFILE_UNCALIBRATED_RGBA,
	MK_COLORPROFILE_UNCALIBRATED_BGRA,
	MK_COLORPROFILE_UNCALIBRATED_ABGR,

	//YUV 4444
	MK_COLORPROFILE_UNCALIBRATED_CrYCbA_NTSC,
	MK_COLORPROFILE_UNCALIBRATED_CrYCbA_HDTV,
	MK_COLORPROFILE_UNCALIBRATED_CrYCbA_NTSC_VIDEO,	//	scaled between 16-235
	MK_COLORPROFILE_UNCALIBRATED_CrYCbA_HDTV_VIDEO,	//	scaled between 16-235

	// YUV 4444
	MK_COLORPROFILE_UNCALIBRATED_YCbCrA_NTSC,
	MK_COLORPROFILE_UNCALIBRATED_YCbCrA_HDTV,
	MK_COLORPROFILE_UNCALIBRATED_YCbCrA_HDTV_VIDEO,	//	scaled between 16-235
	MK_COLORPROFILE_UNCALIBRATED_YCbCrA_NTSC_VIDEO,	//	scaled between 16-235

	//YUV 422
	MK_COLORPROFILE_UNCALIBRATED_CbYCrY_HDTV_VIDEO,	//	scaled between 16-235
	MK_COLORPROFILE_UNCALIBRATED_CbYCrY_NTSC_VIDEO,	//	scaled between 16-235

	// YUV 422
	MK_COLORPROFILE_UNCALIBRATED_YCbYCr_NTSC_VIDEO,	//	scaled between 16-235
	MK_COLORPROFILE_UNCALIBRATED_YCbYCr_HDTV_VIDEO,	//	scaled between 16-235

	// YUV 4444
	MK_COLORPROFILE_UNCALIBRATED_CrCbYA_NTSC_VIDEO,	//	scaled between 16-235

	MK_COLORPROFILE_COUNT
};
typedef int ColorProfile;


//#ifdef GENERIC_NAMESPACE
//}
//#endif

#endif // __GENERIC_IMAGE_COLOR_PROFILE__
