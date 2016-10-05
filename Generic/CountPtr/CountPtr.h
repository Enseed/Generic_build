
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
#ifndef __GENERIC_MEMORY_COUNTPTR_H__
#define __GENERIC_MEMORY_COUNTPTR_H__

/**
 *	\file 		CountPtr.h
 *	\brief 		Reference counted pointer class
 *	\ingroup	seed::Memory
 */

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include <Generic/Base/Base.h>
#include <Generic/Atomic/Atomic.h>
#include <Generic/Devel/Debug.h>
#include <atomic>

BEGIN_GENERIC_NAMESPACE

/*!
 *	Reference counted pointer class.  Use an CountPtr to make sure the pointer is being
 *	deleted when the number of CountPtr pointing to it reaches 0.
 *
 *  Not to be confused with the ShdPtr, the reference count is kept in the CountPtr 
 *  instead of in the ShdObj.  Consequently, this would fail:
 *
 *	\code
 *		{
 *			CountPtr<Obj> o1 = new Obj; // o1 has a ref count of 1
 *			CountPtr<Obj> o2 = o1.ptr(); // o1 still has a ref count of 1
 *		} // o2 is deleted, o1 is deleted -> crash.
 *	\endcode
 *
 *
 *	Typical usage is for when the object does not support reference count.
 *  This is similar to the boost::shared_ptr.
 *  Can be used for automatic deletion in containers, where the AutoPtr
 *  would fail, e.g.
 *
 *	\code
 *		{
 *			std::vector< CountPtr<Obj> > someVect;
 *		} // All of someVect is released
 *	\endcode
 *
 *	The pointer wrapped inside the CountPtr has multiple owners.  You can still
 *  steal ownership of the pointer using givePtr().  After giving the ownership,
 *  CountPtr will not delete the pointer even when the reference count reaches 0.
 *  Giving the ownership more than once is a logical error and will assert in
 *  debug mode.
 *
 *	\code
 *		CountPtr<Obj> o1 = new Obj;
 *		Obj* o2 = o1.givePtr();  // o1 will not delete the object
 *		Obj* o3 = o1.givePtr();  // will assert at run time
 *	\endcode
 *
 *	To release a CountPtr simply set it to null:
 *	\code
 *		CountPtr<Obj> o1 = new Obj;
 *		o1 = NULL; // releases a reference
 *	\endcode
 */

//==============================================================================
//	CLASS CountPtr
//==============================================================================
template<typename T>
class CountPtrDefaultAllocator
{
public:
	static void free(T *obj) { delete obj; }
};


// we use a ref count structure to hold the pointer so we
// can have soft references on the pointer - meaning they
// do now hold a an actual reference on the objet, but they
// keep a pointer to it.  In the event where the object is
// deleted, the structure remains with a null pointer for
// these soft references.
template<typename T, typename ALLOCATOR>
struct CountPtrRefStruct
{
	CountPtrRefStruct(T *aPtr)
	:
		_ptr(aPtr),
		_refCount(1),
		_structRefCount(1),
		_hasOwnership(true)
	{}

	bool retain()
	{
		softRetain();

		// careful here: there's a possibility that as we try to reference
		// the pointer, it's being released.  Imagine two scenarios:
		//
		// 1. A holds the last reference
		//    countPtr() is called on a soft reference
		//    A is destroyed just before we managed to get the reference
		//    A will destroy the object
		//    We end up with a CountPtr with a ref count of 1 pointing to an invalid object
		//
		// 2. A holds the last reference
		//	  A is destroyed just after we managed to get the reference
		//    A will not destroy the object
		//    We end up with a CountPtr with a ref count of 1 pointing to a valid object
		//
		// The only way to distinguish between the two is to check for the previous
		// value of the reference count before it was incremented.  If we went back
		// to 1 from 0, then the object is deleted.  If the previous value was 1, then
		// we're safe.

		if (_refCount.fetch_add(1) <= 0)
		{
			_refCount.fetch_sub(1);
			softRelease();
			return false;
		}
		return true;
	}

	void softRetain()
	{
		_structRefCount.fetch_add(1);
	}

	bool release()
	{
		if (_refCount.fetch_sub(1) == 0)
		{
			if (_hasOwnership)
				ALLOCATOR::free(_ptr);
			_ptr = nullptr;
		}

		return softRelease();
	}

	bool softRelease()
	{
		if (_structRefCount.fetch_sub(1) == 0)
		{
			ASSERT(_refCount == 0);
			delete this;
			return true;
		}
		return false;
	}

	volatile std::atomic_int_fast32_t _refCount;
	volatile std::atomic_int_fast32_t _structRefCount;
	T *_ptr;
	bool _hasOwnership;
};


template<typename T, typename ALLOCATOR>
class SoftCountPtr;

template<typename T, typename ALLOCATOR=CountPtrDefaultAllocator<T> >
class CountPtr
{
public:
	friend class SoftCountPtr<T, ALLOCATOR>;

	class CountPtrParam
	{
	public:
		CountPtrParam(CountPtr<T, ALLOCATOR> *countPtr);
		CountPtrParam(const CountPtrParam &rhs);
		CountPtrParam& operator=(const CountPtrParam &rhs);
		~CountPtrParam();
		operator T** ();

	private:
//		CountPtrParam(const CountPtrParam &rhs);
//		CountPtrParam& operator=(const CountPtrParam &rhs);

	private:
		CountPtr<T, ALLOCATOR> *_countPtr;
		T* _param;
	};

public:
	CountPtr();

	CountPtr(const CountPtr<T, ALLOCATOR> &countPtr);
	CountPtr(const SoftCountPtr<T, ALLOCATOR> &aSoftCountPtr);

	template <typename RhsT>
	CountPtr(const CountPtr<RhsT, ALLOCATOR> &countPtr);

	explicit CountPtr(T *ptr);
	void reset();

public:
	~CountPtr();

public:
	CountPtr& operator = (const CountPtr<T, ALLOCATOR> &countPtr);

	template <typename RhsT>
	CountPtr& operator = (const CountPtr<RhsT, ALLOCATOR> &countPtr);

	CountPtr& operator = (T *ptr);

public:
	T* operator -> () const;
	T& operator * () const;

	//! Obtain inner pointer (does affect ref count)
	T* ptr() const;

	typedef void (CountPtr<T, ALLOCATOR>::*bool_type)() const;
	void bool_type_result() const {}

	operator bool_type () const
	{
		return ptr() ? &CountPtr<T, ALLOCATOR>::bool_type_result : NULL;
	}

	bool operator < (const CountPtr<T, ALLOCATOR> &rhs)
	{	return ptr() < rhs.ptr(); }

	template<class U>
	bool operator == (const CountPtr<U, ALLOCATOR> &rhs) const;

	template<class U>
	bool operator == (const U *rhs) const;

	bool operator == (const T *rhs) const;

	template<class U>
	bool operator != (const CountPtr<U, ALLOCATOR> &rhs) const
	{	return !operator==(rhs);	}

	template<class U>
	bool operator != (const U *rhs) const
	{	return !operator==(rhs);	}

	bool operator != (const T *rhs) const
	{	return !operator==(rhs);	}

	//! Transfer ownership
	T* givePtr();

	template <class LhsT>
	LhsT* dynamicCast();

	template <class LhsT>
	LhsT* staticCast();

	template <typename LhsT, typename LhsTALLOCATOR>
	operator CountPtr<LhsT, LhsTALLOCATOR>();

	CountPtrParam setFromParam()
	{
		return CountPtrParam(this);
	}

	template<typename, typename> friend class CountPtr;

private:
	CountPtrRefStruct<T, ALLOCATOR> *_refStruct;
};



template<typename T, typename ALLOCATOR=CountPtrDefaultAllocator<T> >
class SoftCountPtr
{
public:
	friend class CountPtr<T, ALLOCATOR>;
	SoftCountPtr();

	SoftCountPtr(const SoftCountPtr<T, ALLOCATOR> &aSoftCountPtr);

	template <typename RhsT>
	SoftCountPtr(const SoftCountPtr<RhsT, ALLOCATOR> &aSoftCountPtr);

	SoftCountPtr(const CountPtr<T, ALLOCATOR> &aCountPtr);

	template <typename RhsT>
	SoftCountPtr(const CountPtr<RhsT, ALLOCATOR> &aCountPtr);

public:
	~SoftCountPtr();

public:
	SoftCountPtr& operator = (const SoftCountPtr<T, ALLOCATOR> &aSoftCountPtr);

	template <typename RhsT>
	SoftCountPtr& operator = (const SoftCountPtr<RhsT, ALLOCATOR> &aSoftCountPtr);

	SoftCountPtr& operator = (const CountPtr<T, ALLOCATOR> &aCountPtr);

	template <typename RhsT>
	SoftCountPtr& operator = (const CountPtr<RhsT, ALLOCATOR> &aCountPtr);

public:
	// Do perform any operation on the pointer, you must first
	// convert to a CountPtr...
	CountPtr<T, ALLOCATOR> countPtr() const;

	//T* operator -> () const;
	//T& operator * () const;
	//T* ptr() const;
	//operator bool () const;

private:
	CountPtrRefStruct<T, ALLOCATOR> *_refStruct;
};


END_GENERIC_NAMESPACE


#include "src/CountPtr.inline.h"

#endif // __GENERIC_MEMORY_COUNTPTR_H__
