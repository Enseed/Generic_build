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
#ifndef __ITL_TYPEINFO_H__
#define __ITL_TYPEINFO_H__

//==============================================================================
// FILE TypeInfo.h
//==============================================================================
// This was needed to find the non-const type of a type
//------------------------------------------------------------------------------

		// FIXME:
		// the iterator_traits have something similar, there is no
		// need to reimplement this - instead, refer to std::
		
#ifdef ITL_NAMESPACE
namespace ITL_NAMESPACE {
#endif

//==============================================================================
// CLASS TypeInfoConstSelector
//==============================================================================
template<class T>
struct TypeInfoConstSelector { typedef T BaseType; enum { IS_CONST = false }; };

//------------------------------------------------------------------------------
// CLASS TypeInfoConstSelector - const case
//------------------------------------------------------------------------------
template<class T>
struct TypeInfoConstSelector<const T> { typedef T BaseType; enum { IS_CONST = true }; };

//==============================================================================
// CLASS TypeInfo
//==============================================================================
template<class T>
struct TypeInfo
{
	typedef T Type;
	typedef typename TypeInfoConstSelector<T>::BaseType BaseType;
	enum { IS_CONST = TypeInfoConstSelector<T>::IS_CONST };

	typedef BaseType* pointer;
	typedef BaseType& reference;

	typedef const BaseType* const_pointer;
	typedef const BaseType& const_reference;

	typedef ptrdiff_t difference_type;
};

#ifdef ITL_NAMESPACE
}
#endif

#endif // __ITL_TYPEINFO_H__
