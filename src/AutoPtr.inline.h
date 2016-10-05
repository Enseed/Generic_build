/*******************************************************************************
 Copyright 2010 Enseed inc.
 
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
#ifndef __GENERIC_MEMORY_AUTOPTR_INLINE_H__
#define __GENERIC_MEMORY_AUTOPTR_INLINE_H__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "../AutoPtr.h"
#include "../Devel/Debug.h"
#include <stddef.h>

BEGIN_GENERIC_NAMESPACE

//------------------------------------------------------------------------------
//
template<typename T, typename ALLOCATOR>
AutoPtr<T, ALLOCATOR>::AutoPtr()
:
	mPtr(NULL)
{}

//------------------------------------------------------------------------------
//
template<typename T, typename ALLOCATOR>
AutoPtr<T, ALLOCATOR>::AutoPtr(T *p)
:
	mPtr(p)
{}

//------------------------------------------------------------------------------
//
template<typename T, typename ALLOCATOR>
AutoPtr<T, ALLOCATOR>::AutoPtr(AutoPtr<T, ALLOCATOR> &autoPtr)
:
	mPtr(autoPtr.givePtr())
{}

//------------------------------------------------------------------------------
//
template<typename T, typename ALLOCATOR> template <typename RhsT, typename RhsALLOCATOR>
AutoPtr<T, ALLOCATOR>::AutoPtr(AutoPtr<RhsT, RhsALLOCATOR> &autoPtr)
:
	mPtr(autoPtr.givePtr())
{}

//------------------------------------------------------------------------------
//
template<typename T, typename ALLOCATOR>
AutoPtr<T, ALLOCATOR>::~AutoPtr()
{
	delete mPtr;
}

//------------------------------------------------------------------------------
//
template<typename T, typename ALLOCATOR>
AutoPtr<T, ALLOCATOR>& AutoPtr<T, ALLOCATOR>::operator = (T *p)
{
	if (p != mPtr)
	{
		delete mPtr;
		mPtr = p;
	}

	return *this;
}

//------------------------------------------------------------------------------
//
template<typename T, typename ALLOCATOR>
void AutoPtr<T, ALLOCATOR>::reset()
{
	if (mPtr)
	{
		delete mPtr;
		mPtr = nullptr;
	}
}

//------------------------------------------------------------------------------
//
template<typename T, typename ALLOCATOR>
AutoPtr<T, ALLOCATOR>& AutoPtr<T, ALLOCATOR>::operator = (AutoPtr<T, ALLOCATOR> &autoPtr)
{
	if (autoPtr.mPtr != mPtr)
	{
		delete mPtr;
		mPtr = autoPtr.givePtr();
	}

	return *this;
}

//------------------------------------------------------------------------------
//
template<typename T, typename ALLOCATOR> 	template <typename RhsT, typename RhsALLOCATOR>
AutoPtr<T, ALLOCATOR>& AutoPtr<T, ALLOCATOR>::operator = (AutoPtr<RhsT, RhsALLOCATOR> &autoPtr)
{
	if (autoPtr.ptr() != mPtr)
	{
		delete mPtr;
		mPtr = autoPtr.givePtr();
	}

	return *this;
}

//------------------------------------------------------------------------------
//
template<typename T, typename ALLOCATOR>
T* AutoPtr<T, ALLOCATOR>::operator -> () const
{
	return mPtr;
}

//------------------------------------------------------------------------------
//
template<typename T, typename ALLOCATOR>
T& AutoPtr<T, ALLOCATOR>::operator * () const
{
	ASSERT(mPtr != NULL);
	return *mPtr;
}

//------------------------------------------------------------------------------
//
template<typename T, typename ALLOCATOR>
T* AutoPtr<T, ALLOCATOR>::ptr() const
{
	return mPtr;
}

//------------------------------------------------------------------------------
//
template<typename T, typename ALLOCATOR>
T* AutoPtr<T, ALLOCATOR>::givePtr()
{
	T* p = mPtr;
	mPtr = NULL;
	return p;
}

//------------------------------------------------------------------------------
//
template<typename T, typename ALLOCATOR> template<class U>
bool AutoPtr<T, ALLOCATOR>::operator == (const AutoPtr<U, ALLOCATOR> &rhs) const
{	return ptr() == rhs.ptr(); }

//------------------------------------------------------------------------------
//
template<typename T, typename ALLOCATOR> template<class U>
bool AutoPtr<T, ALLOCATOR>::operator == (const U *rhs) const
{	return ptr() == rhs;	}

//------------------------------------------------------------------------------
//
template<typename T, typename ALLOCATOR>
bool AutoPtr<T, ALLOCATOR>::operator == (const T *rhs) const
{	return ptr() == rhs;	}

//------------------------------------------------------------------------------
//	
template<typename T, typename ALLOCATOR> template <class LhsT>
LhsT* AutoPtr<T, ALLOCATOR>::dynamicCast()
{
	ASSERT(mPtr != NULL);
	return dynamic_cast<LhsT*>(mPtr);
}
//------------------------------------------------------------------------------
//	
template<typename T, typename ALLOCATOR> template <class LhsT>
LhsT* AutoPtr<T, ALLOCATOR>::staticCast()
{
	ASSERT(mPtr != NULL);
	ASSERT(dynamicCast<LhsT>() != nullptr);
	return static_cast<LhsT*>(mPtr);
}

/*template<typename T, typename ALLOCATOR>
AutoPtr<T, ALLOCATOR>::AutoPtrParam AutoPtr<T, ALLOCATOR>::asParam()
{
	return AutoPtrParam(this);
}
*/
template<typename T, typename ALLOCATOR>
AutoPtr<T, ALLOCATOR>::AutoPtrParam::AutoPtrParam(AutoPtr<T, ALLOCATOR> *autoPtr)
:
	_autoPtr(autoPtr),
	_param(autoPtr->ptr())
{}

template<typename T, typename ALLOCATOR>
AutoPtr<T, ALLOCATOR>::AutoPtrParam::operator T** ()
{
	return &_param;
}

template<typename T, typename ALLOCATOR>
AutoPtr<T, ALLOCATOR>::AutoPtrParam::AutoPtrParam(AutoPtrParam &rhs)
:
	_param(rhs._param),
	_autoPtr(rhs._autoPtr)
{
	rhs._autoPtr = NULL;
}

template<typename T, typename ALLOCATOR>
typename AutoPtr<T, ALLOCATOR>::AutoPtrParam& AutoPtr<T, ALLOCATOR>::AutoPtrParam::operator=(typename AutoPtr<T, ALLOCATOR>::AutoPtrParam &rhs)
{
	_param = rhs._param;
	_autoPtr = rhs._autoPtr;
	rhs._autoPtr = NULL;
	return *this;
}

template<typename T, typename ALLOCATOR>
AutoPtr<T, ALLOCATOR>::AutoPtrParam::~AutoPtrParam()
{
	if (_autoPtr)
		*_autoPtr = _param;
}



//==============================================================================
//	FREE FUNCTIONS
//==============================================================================

//------------------------------------------------------------------------------
//	
template <class T, class U, class ALLOCATOR>
bool operator == (const T *lhs, const AutoPtr<U, ALLOCATOR> &rhs)
{
	return rhs == lhs;
}

//------------------------------------------------------------------------------
//	
template <class T, class U, class ALLOCATOR>
bool operator != (const T *lhs, const AutoPtr<U, ALLOCATOR> &rhs)
{
	return rhs != lhs;
}



END_GENERIC_NAMESPACE


#endif // __GENERIC_MEMORY_AUTOPTR_INLINE_H__
