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
#ifndef __GENERIC_MEMORY_SRC_COUNTPTR_INLINE_H__
#define __GENERIC_MEMORY_SRC_COUNTPTR_INLINE_H__

#include "../CountPtr.h"

namespace seed {

template<typename T, typename ALLOCATOR>
CountPtr<T, ALLOCATOR>::CountPtr()
:
	_refStruct(nullptr)
{}


template<typename T, typename ALLOCATOR>
CountPtr<T, ALLOCATOR>::CountPtr(const SoftCountPtr<T, ALLOCATOR> &aSoftCountPtr)
:
	_refStruct(nullptr)
{
	if (aSoftCountPtr._refStruct && aSoftCountPtr._refStruct->retain())
	{
		_refStruct = aSoftCountPtr._refStruct;
	}
}

template<typename T, typename ALLOCATOR>
CountPtr<T, ALLOCATOR>::CountPtr(const CountPtr<T, ALLOCATOR> &aCountPtr)
:
	_refStruct(nullptr)
{
	if (aCountPtr._refStruct && aCountPtr._refStruct->retain())
	{
		_refStruct = aCountPtr._refStruct;
	}
}

template<typename T, typename ALLOCATOR>
template <typename RhsT>
CountPtr<T, ALLOCATOR>::CountPtr(const CountPtr<RhsT, ALLOCATOR> &aCountPtr)
:
	_refStruct(nullptr)
{
	if (aCountPtr._refStruct && aCountPtr._refStruct->retain())
	{
		_refStruct = aCountPtr._refStruct;
	}
}

template<typename T, typename ALLOCATOR>
CountPtr<T, ALLOCATOR>::CountPtr(T *ptr)
:
	_refStruct(nullptr)
{
	if (ptr)
	{
		_refStruct = new CountPtrRefStruct<T, ALLOCATOR>(ptr);
	}

}

template<typename T, typename ALLOCATOR>
CountPtr<T, ALLOCATOR>::~CountPtr()
{
	if (_refStruct)
		_refStruct->release();
}

template<typename T, typename ALLOCATOR>
CountPtr<T, ALLOCATOR>& CountPtr<T, ALLOCATOR>::operator = (const CountPtr<T, ALLOCATOR> &rhs)
{
	if (_refStruct == rhs._refStruct)
		return *this;

	if (_refStruct)
		_refStruct->release();

	_refStruct = rhs._refStruct;

	if (_refStruct)
		_refStruct->retain();
	return *this;
}

template<typename T, typename ALLOCATOR>
template <typename RhsT>
CountPtr<T, ALLOCATOR>& CountPtr<T, ALLOCATOR>::operator = (const CountPtr<RhsT, ALLOCATOR> &rhs)
{
	if (_refStruct == rhs._refStruct)
		return;

	if (_refStruct)
		_refStruct->release();

	_refStruct = rhs._refStruct;

	if (_refStruct)
		_refStruct->retain();
}

template<typename T, typename ALLOCATOR>
CountPtr<T, ALLOCATOR>& CountPtr<T, ALLOCATOR>::operator = (T *aPtr)
{
	if (_refStruct)
	{
		_refStruct->release();
		_refStruct = nullptr;
	}

	if (aPtr)
	{
		_refStruct = new CountPtrRefStruct<T, ALLOCATOR>(aPtr);
	}

	return *this;
}

template<typename T, typename ALLOCATOR>
void CountPtr<T, ALLOCATOR>::reset()
{
	if (_refStruct)
	{
		_refStruct->release();
		_refStruct = nullptr;
	}
}

template<typename T, typename ALLOCATOR>
T* CountPtr<T, ALLOCATOR>::operator -> () const
{
	ASSERT(_refStruct);
	ASSERT(_refStruct->_ptr);
	return _refStruct->_ptr;
}

template<typename T, typename ALLOCATOR>
T& CountPtr<T, ALLOCATOR>::operator * () const
{
	ASSERT(_refStruct);
	ASSERT(_refStruct->_ptr);
	return *_refStruct->_ptr;
}

template<typename T, typename ALLOCATOR>
T* CountPtr<T, ALLOCATOR>::ptr() const
{
	if (!_refStruct)
		return nullptr;

	return _refStruct->_ptr;
}


template<typename T, typename ALLOCATOR> template<class U>
bool CountPtr<T, ALLOCATOR>::operator == (const CountPtr<U, ALLOCATOR> &rhs) const
{	return ptr() == rhs.ptr();	}

template<typename T, typename ALLOCATOR> template<class U>
bool CountPtr<T, ALLOCATOR>::operator == (const U *rhs) const
{	return ptr() == rhs;	}

template<typename T, typename ALLOCATOR>
bool CountPtr<T, ALLOCATOR>::operator == (const T *rhs) const
{	return ptr() == rhs;	}

template<typename T, typename ALLOCATOR>
T* CountPtr<T, ALLOCATOR>::givePtr()
{
	if (!_refStruct)
		return nullptr;

	ASSERT(_refStruct->_hasOwnership);
	// FIXME: make this thread safe - it's an logical error to ask
	// twice for ownership, so it should not occur that we request
	// it in two threads, but still...

	_refStruct->_hasOwnership = false;
	return _refStruct->_ptr;
}

template<typename T, typename ALLOCATOR>
template <class LhsT>
LhsT* CountPtr<T, ALLOCATOR>::dynamicCast()
{
	return dynamic_cast<LhsT*>(_refStruct->_ptr);
}

template<typename T, typename ALLOCATOR>
template <class LhsT>
LhsT* CountPtr<T, ALLOCATOR>::staticCast()
{
	return static_cast<LhsT*>(_refStruct->_ptr);
}

template<class T, class ALLOCATOR>
template < class LhsT, class LhsTALLOCATOR>
CountPtr<T, ALLOCATOR>::operator CountPtr<LhsT, LhsTALLOCATOR>()
{
	static_assert(std::is_base_of<LhsT, T>::value,
		"LhsT must be a descendant of T"
		);

	CountPtr<LhsT> lhs;

	lhs._refStruct = reinterpret_cast<sd::CountPtrRefStruct<LhsT, LhsTALLOCATOR>*>(_refStruct);

	if (lhs._refStruct)
		_refStruct->retain();

	return lhs;
}





template<typename T, typename ALLOCATOR>
SoftCountPtr<T, ALLOCATOR>::SoftCountPtr()
:
	_refStruct(nullptr)
{}

template<typename T, typename ALLOCATOR>
SoftCountPtr<T, ALLOCATOR>::SoftCountPtr(const SoftCountPtr<T, ALLOCATOR> &aSoftCountPtr)
:
	_refStruct(nullptr)
{
	_refStruct = aSoftCountPtr._refStruct;

	if (_refStruct)
		_refStruct->softRetain();
}

template<typename T, typename ALLOCATOR>
template <typename RhsT>
SoftCountPtr<T, ALLOCATOR>::SoftCountPtr(const SoftCountPtr<RhsT, ALLOCATOR> &aSoftCountPtr)
:
	_refStruct(nullptr)
{
	_refStruct = aSoftCountPtr._refStruct;

	if (_refStruct)
		_refStruct->softRetain();
}

template<typename T, typename ALLOCATOR>
SoftCountPtr<T, ALLOCATOR>::SoftCountPtr(const CountPtr<T, ALLOCATOR> &aCountPtr)
:
	_refStruct(nullptr)
{
	_refStruct = aCountPtr._refStruct;

	if (_refStruct)
		_refStruct->softRetain();
}

template<typename T, typename ALLOCATOR>
template <typename RhsT>
SoftCountPtr<T, ALLOCATOR>::SoftCountPtr(const CountPtr<RhsT, ALLOCATOR> &aCountPtr)
:
	_refStruct(nullptr)
{
	_refStruct = aCountPtr._refStruct;

	if (_refStruct)
		_refStruct->softRetain();
}

template<typename T, typename ALLOCATOR>
SoftCountPtr<T, ALLOCATOR>::~SoftCountPtr()
{
	if (_refStruct)
		_refStruct->softRelease();
}

template<typename T, typename ALLOCATOR>
SoftCountPtr<T, ALLOCATOR>& SoftCountPtr<T, ALLOCATOR>::operator = (const SoftCountPtr<T, ALLOCATOR> &aSoftCountPtr)
{
	if (aSoftCountPtr._refStruct == _refStruct)
		return *this;

	if (_refStruct)
		_refStruct->softRelease();

	_refStruct = aSoftCountPtr._refStruct;

	if (_refStruct)
		_refStruct->softRetain();
	return *this;
}

template<typename T, typename ALLOCATOR>
template <typename RhsT>
SoftCountPtr<T, ALLOCATOR>& SoftCountPtr<T, ALLOCATOR>::operator = (const SoftCountPtr<RhsT, ALLOCATOR> &aSoftCountPtr)
{
	if (aSoftCountPtr._refStruct == _refStruct)
		return *this;

	if (_refStruct)
		_refStruct->softRelease();

	_refStruct = aSoftCountPtr._refStruct;

	if (_refStruct)
		_refStruct->softRetain();

	return *this;
}

template<typename T, typename ALLOCATOR>
SoftCountPtr<T, ALLOCATOR>& SoftCountPtr<T, ALLOCATOR>::operator = (const CountPtr<T, ALLOCATOR> &aCountPtr)
{
	if (aCountPtr._refStruct == _refStruct)
		return *this;

	if (_refStruct)
		_refStruct->softRelease();

	_refStruct = aCountPtr._refStruct;

	if (_refStruct)
		_refStruct->softRetain();

	return *this;
}

template<typename T, typename ALLOCATOR>
template <typename RhsT>
SoftCountPtr<T, ALLOCATOR>& SoftCountPtr<T, ALLOCATOR>::operator = (const CountPtr<RhsT, ALLOCATOR> &aCountPtr)
{
	if (aCountPtr._refStruct == _refStruct)
		return *this;

	if (_refStruct)
		_refStruct->softRelease();

	_refStruct = aCountPtr._refStruct;

	if (_refStruct)
		_refStruct->softRetain();

	return *this;
}

template<typename T, typename ALLOCATOR>
CountPtr<T, ALLOCATOR> SoftCountPtr<T, ALLOCATOR>::countPtr() const
{
	return CountPtr<T, ALLOCATOR>(*this);
}


//==============================================================================
//	FREE FUNCTIONS
//==============================================================================

//------------------------------------------------------------------------------
//	
template <class T, class U, class ALLOCATOR>
bool operator == (const T *lhs, const CountPtr<U, ALLOCATOR> &rhs)
{
	return rhs == lhs;
}

//------------------------------------------------------------------------------
//	
template <class T, class U, class ALLOCATOR>
bool operator != (const T *lhs, const CountPtr<U, ALLOCATOR> &rhs)
{
	return rhs != lhs;
}




} // namespace seed

#endif // __GENERIC_MEMORY_SRC_COUNTPTR_INLINE_H__
