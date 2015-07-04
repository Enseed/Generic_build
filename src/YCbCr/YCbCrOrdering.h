/*******************************************************************************
 Copyright 2009 Enseed Inc. & Gaspard Petit <gaspardpetit@enseed.com>
 
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
*******************************************************************************/
#ifndef __ITL__YCBCRORDERING_H__
#define __ITL__YCBCRORDERING_H__

//==============================================================================
// FILE YCbCrOrdering.h
//==============================================================================
// Various ordering for YCbCr pixels
//------------------------------------------------------------------------------

struct ComponentOrderingYCbCr { public: enum { Y, CB, CR, COMPONENT_COUNT }; };
struct ComponentOrderingCrCbY { public: enum { CR, CB, Y, COMPONENT_COUNT }; };

struct ComponentOrderingYCbCrA { public: enum { Y, CB, CR, ALPHA, COMPONENT_COUNT }; };
struct ComponentOrderingAYCbCr { public: enum { ALPHA, Y, CB, CR, COMPONENT_COUNT }; };

struct ComponentOrderingCbYCrA { public: enum { CB, Y, CR, ALPHA, COMPONENT_COUNT }; };
struct ComponentOrderingACbYCr { public: enum { ALPHA, CB, Y, CR, COMPONENT_COUNT }; };

struct ComponentOrderingCrCbYA { public: enum { CR, CB, Y, ALPHA, COMPONENT_COUNT }; };
struct ComponentOrderingACrCbY { public: enum { ALPHA, CR, CB, Y, COMPONENT_COUNT }; };

//==============================================================================
// ALPHA
//==============================================================================
struct ComponentOrderingYA { public: enum { Y, ALPHA, COMPONENT_COUNT }; };
struct ComponentOrderingAY { public: enum { ALPHA, Y, COMPONENT_COUNT }; };

//==============================================================================
// PLANAR
//==============================================================================
struct ComponentOrderingY { public: enum { Y, COMPONENT_COUNT }; };
struct ComponentOrderingCb { public: enum { CB, COMPONENT_COUNT }; };
struct ComponentOrderingCr { public: enum { CR, COMPONENT_COUNT }; };

//==============================================================================
// YCbCr 422 Pixel declarations
//==============================================================================
struct ComponentOrderingY0CbY1Cr { public: enum { Y0, CB, Y1, CR, COMPONENT_COUNT }; };
struct ComponentOrderingY0CrY1Cb { public: enum { Y0, CR, Y1, CB, COMPONENT_COUNT }; };
struct ComponentOrderingY1CbY0Cr { public: enum { Y1, CB, Y0, CR, COMPONENT_COUNT }; };
struct ComponentOrderingY1CrY0Cb { public: enum { Y1, CR, Y0, CB, COMPONENT_COUNT }; };

struct ComponentOrderingCbY0CrY1 { public: enum { CB, Y0, CR, Y1, COMPONENT_COUNT }; };
struct ComponentOrderingCrY0CbY1 { public: enum { CR, Y0, CB, Y1, COMPONENT_COUNT }; };
struct ComponentOrderingCbY1CrY0 { public: enum { CB, Y1, CR, Y0, COMPONENT_COUNT }; };
struct ComponentOrderingCrY1CbY0 { public: enum { CR, Y1, CB, Y0, COMPONENT_COUNT }; };

struct ComponentOrderingY0Y1CbCr { public: enum { Y0, Y1, CB, CR, COMPONENT_COUNT }; };
struct ComponentOrderingY0Y1CrCb { public: enum { Y0, Y1, CR, CB, COMPONENT_COUNT }; };
struct ComponentOrderingY1Y0CbCr { public: enum { Y1, Y0, CB, CR, COMPONENT_COUNT }; };
struct ComponentOrderingY1Y0CrCb { public: enum { Y1, Y0, CR, CB, COMPONENT_COUNT }; };

//==============================================================================
// PLANAR 422
//==============================================================================
struct ComponentOrderingYY { public: enum { Y0, Y1, COMPONENT_COUNT }; };


#endif // __ITL__YCBCRORDERING_H__
