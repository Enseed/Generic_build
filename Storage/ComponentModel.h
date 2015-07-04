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
#ifndef __ITL_COMPONENTMODEL_H__
#define __ITL_COMPONENTMODEL_H__

//==============================================================================
//	FILE ComponentModel.h
//==============================================================================
//------------------------------------------------------------------------------

class ComponentModel_Red {};
class ComponentModel_Green {};
class ComponentModel_Blue {};
class ComponentModel_Alpha {};

class ComponentModel_RGB : ComponentModel_Red, ComponentModel_Green, ComponentModel_Blue {};
class ComponentModel_RGBA : ComponentModel_RGB, ComponentModel_Alpha {};

class ComponentModel_Cyan {};
class ComponentModel_Magenta {};
class ComponentModel_Yellow {};
class ComponentModel_Black {};

class ComponentModel_CMY : ComponentModel_Cyan, ComponentModel_Magenta, ComponentModel_Yellow {};
class ComponentModel_CMYA : ComponentModel_CMY, ComponentModel_Alpha {};

class ComponentModel_CMYK : ComponentModel_CMY, ComponentModel_Black {};
class ComponentModel_CMYKA : ComponentModel_CMYK, ComponentModel_Alpha {};

class ComponentModel_Luminance {};
class ComponentModel_ChromaBlue {};
class ComponentModel_ChromaRed {};
class ComponentModel_YCbCr : ComponentModel_Luminance, ComponentModel_ChromaBlue, ComponentModel_ChromaRed {};
class ComponentModel_YCbCrA : ComponentModel_YCbCr, ComponentModel_Alpha {};
class ComponentModel_YA : ComponentModel_Luminance, ComponentModel_Alpha {};

class ComponentModel_Value;

#endif // __ITL_COLORPROFILE_H__
