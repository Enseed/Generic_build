///////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2002, Industrial Light & Magic, a division of Lucas
// Digital Ltd. LLC
// 
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
// *       Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
// *       Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
// *       Neither the name of Industrial Light & Magic nor the names of
// its contributors may be used to endorse or promote products derived
// from this software without specific prior written permission. 
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
///////////////////////////////////////////////////////////////////////////

// Primary authors:
//     Florian Kainz <kainz@ilm.com>
//     Rod Bogart <rgb@ilm.com>

//---------------------------------------------------------------------------
//
//	half -- a 16-bit floating point number class:
//
//	Type half can represent positive and negative numbers, whose
//	magnitude is between roughly 6.1e-5 and 6.5e+4, with a relative
//	error of 9.8e-4; numbers smaller than 6.1e-5 can be represented
//	with an absolute error of 6.0e-8.  All integers from -2048 to
//	+2048 can be represented exactly.
//
//	Type half behaves (almost) like the built-in C++ floating point
//	types.  In arithmetic expressions, half, float and double can be
//	mixed freely.  Here are a few examples:
//
//	    half a (3.5);
//	    float b (a + sqrt (a));
//	    a += b;
//	    b += a;
//	    b = a + 7;
//
//	Conversions from half to float are lossless; all half numbers
//	are exactly representable as floats.
//
//	Conversions from float to half may not preserve the float's
//	value exactly.  If a float is not representable as a half, the
//	float value is rounded to the nearest representable half.  If
//	a float value is exactly in the middle between the two closest
//	representable half values, then the float value is rounded to
//	the half with the greater magnitude.
//
//	Overflows during float-to-half conversions cause arithmetic
//	exceptions.  An overflow occurs when the float value to be
//	converted is too large to be represented as a half, or if the
//	float value is an infinity or a NAN.
//
//	The implementation of type half makes the following assumptions
//	about the implementation of the built-in C++ types:
//
//	    float is an IEEE 754 single-precision number
//	    sizeof (float) == 4
//	    sizeof (unsigned int) == sizeof (float)
//	    alignof (unsigned int) == alignof (float)
//	    sizeof (unsigned short) == 2
//
//---------------------------------------------------------------------------

#ifndef _HALF_H_
#define _HALF_H_


#include <iosfwd>

#ifdef GENERIC_NAMESPACE
namespace GENERIC_NAMESPACE {
#endif

class half
{
  public:

    //-------------
    // Constructors
    //-------------

    half ();			// no initialization
    half (float f);


    //--------------------
    // Conversion to float
    //--------------------

    operator		float () const;


    //------------
    // Unary minus
    //------------

    half		operator - () const;


    //-----------
    // Assignment
    //-----------

    half &		operator = (half  h);
    half &		operator = (float f);

    half &		operator += (half  h);
    half &		operator += (float f);

    half &		operator -= (half  h);
    half &		operator -= (float f);

    half &		operator *= (half  h);
    half &		operator *= (float f);

    half &		operator /= (half  h);
    half &		operator /= (float f);


    //---------------------------------------------------------
    // Round to n-bit precision (n should be between 0 and 10).
    // After rounding, the significand's 10-n least significant
    // bits will be zero.
    //---------------------------------------------------------

    half		round (unsigned int n) const;


    //--------------------------------------------------------------------
    // Classification:
    //
    //	h.isFinite()		returns true if h is a normalized number,
    //				a denormalized number or zero
    //
    //	h.isNormalized()	returns true if h is a normalized number
    //
    //	h.isDenormalized()	returns true if h is a denormalized number
    //
    //	h.isZero()		returns true if h is zero
    //
    //	h.isNan()		returns true if h is a NAN
    //
    //	h.isInfinity()		returns true if h is a positive
    //				or a negative infinity
    //
    //	h.isNegative()		returns true if the sign bit of h
    //				is set (negative)
    //--------------------------------------------------------------------

    bool		isFinite () const;
    bool		isNormalized () const;
    bool		isDenormalized () const;
    bool		isZero () const;
    bool		isNan () const;
    bool		isInfinity () const;
    bool		isNegative () const;


    //--------------------------------------------
    // Special values
    //
    //	posInf()	returns +infinity
    //
    //	negInf()	returns +infinity
    //
    //	qNan()		returns a NAN with the bit
    //			pattern 0111111111111111
    //
    //	sNan()		returns a NAN with the bit
    //			pattern 0111110111111111
    //--------------------------------------------

    static half		posInf ();
    static half		negInf ();
    static half		qNan ();
    static half		sNan ();


    //--------------------------------------
    // Access to the internal representation
    //--------------------------------------

    unsigned short	bits () const;
    void		setBits (unsigned short bits);


  public:

    union uif
    {
	unsigned int	i;
	float		f;
    };

  private:

    static short	convert (int i);
    static float	overflow ();

    unsigned short	_h;

    //---------------------------------------------------
    // Windows dynamic libraries don't like static
    // member variables.
    //---------------------------------------------------
#ifndef OPENEXR_DLL
    static const uif	        _toFloat[1 << 16];
    static const unsigned short _eLut[1 << 9];
#endif
};

#if defined(OPENEXR_DLL)
    //--------------------------------------
    // Lookup tables defined for Windows DLL
    //--------------------------------------
    #if defined(HALF_EXPORTS)
        extern __declspec(dllexport) half::uif		_toFloat[1 << 16];
        extern __declspec(dllexport) unsigned short	_eLut[1 << 9];
    #else
        extern __declspec(dllimport) half::uif		_toFloat[1 << 16];
        extern __declspec(dllimport) unsigned short	_eLut[1 << 9];
    #endif
#endif


//-----------
// Stream I/O
//-----------

std::ostream &		operator << (std::ostream &os, half  h);
std::istream &		operator >> (std::istream &is, half &h);


//----------
// Debugging
//----------

void			printBits   (std::ostream &os, half  h);
void			printBits   (std::ostream &os, float f);
void			printBits   (char  c[19], half  h);
void			printBits   (char  c[35], float f);


#ifdef GENERIC_NAMESPACE
}
#endif

#include "src/half/half.inline.h"

#endif
