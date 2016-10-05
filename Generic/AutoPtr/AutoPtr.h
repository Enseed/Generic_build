/*******************************************************************************
 Copyright 2009 Enseed inc.
 
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
#ifndef __GENERIC_MEMORY_AUTOPTR_H__
#define __GENERIC_MEMORY_AUTOPTR_H__

#include "../Base/Base.h"

/**
 *	\file 		AutoPtr.h
 *	\brief 		Automatic pointer class
 *	\ingroup	sd::Memory
 */

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================

BEGIN_GENERIC_NAMESPACE

/*!
 *	Automatic pointer class.  Use an AutoPtr to make sure the pointer is being
 *	deleted when it goes out of scope.
 *
 *	Typical usage:
 *	\code
 *		{
 *			AutoPtr<Obj> o = new Obj;
 *		} // o is deleted
 *	\endcode
 *
 *	AutoPtr can be returned from a function to enforce AutoPtr usage and
 *	explicitly tell the caller that he is responsible for deleting the object:
 *	\code
 *		AutoPtr<Obj> CreateObj();
 *		{
 *			return new Obj;
 *		}
 *	\endcode
 *
 *	The pointer wrapped inside the AutoPtr has only one owner.  If you wish to
 *	reference the pointer with another AutoPtr, ownership must be transferred:
 *	\code
 *		AutoPtr<Obj> o1 = new Obj;
 *		Obj* o2 = o1.givePtr();  // o1 will now be NULL
 *	\endcode
 *
 *	To force the AutoPtr to delete the object, set it to null:
 *	\code
 *		AutoPtr<Obj> o1 = new Obj;
 *		o1 = NULL; // deletes the object
 *	\endcode
 */

//==============================================================================
//	CLASS AutoPtr
//==============================================================================
template<typename T>
class DefaultAllocator
{
public:
	static void free(T *obj) { delete obj; }
};

template<typename T, typename ALLOCATOR=DefaultAllocator<T> >
class AutoPtr
{
public:
	class AutoPtrParam
	{
	public:
		AutoPtrParam(AutoPtr<T, ALLOCATOR> *autoPtr);
		AutoPtrParam(AutoPtrParam &rhs);
		AutoPtrParam& operator=(AutoPtrParam &rhs);
		~AutoPtrParam();
		operator T** ();

	private:
//		AutoPtrParam(const AutoPtrParam &rhs);
//		AutoPtrParam& operator=(const AutoPtrParam &rhs);

	private:
		AutoPtr<T, ALLOCATOR> *_autoPtr;
		T* _param;
	};

public:
	AutoPtr();

private:
	// private, use .give explicitely instead
	/*!	Will transfer ownership:
	 *	\code
	 *		AutoPtr<Obj> o1 = new Obj;
	 *		AutoPtr<Obj> o2(o1);
	 *		ASSERT(o1 == NULL);
	 */
	AutoPtr(AutoPtr<T, ALLOCATOR> &autoPtr);


private:
	// private, use .give explicitely instead
	/*!	Will transfer ownership:
	 *	\code
	 *		AutoPtr<Obj> o1 = new Obj;
	 *		AutoPtr<BaseObj> o2(o1);
	 *		ASSERT(o1 == NULL);
	 */
	template <typename RhsT, typename RhsALLOCATOR>
	AutoPtr(AutoPtr<RhsT, RhsALLOCATOR> &autoPtr);

public:
	AutoPtr(T *ptr);


	~AutoPtr();

private:
	// private, use .give explicitly instead
	/*!	Will transfer ownership:
	 *	\code
	 *		AutoPtr<Obj> o1 = new Obj;
	 *		AutoPtr<Obj> o2 = o1;
	 *		ASSERT(o1 == NULL);
	 */
	AutoPtr& operator = (AutoPtr<T, ALLOCATOR> &autoPtr);

private:
	// private, use .give explicitely instead
	/*!	Will transfer ownership:
	 *	\code
	 *		AutoPtr<Obj> o1 = new Obj;
	 *		AutoPtr<BaseObj> o2 = o1;
	 *		ASSERT(o1 == NULL);
	 */
	template <typename RhsT, typename RhsALLOCATOR>
	AutoPtr& operator = (AutoPtr<RhsT, RhsALLOCATOR> &autoPtr);

public:
	AutoPtr& operator = (T *ptr);

	T* operator -> () const;
	T& operator * () const;

	//! Obtain inner pointer (does not transfer ownership)
	T* ptr() const;

	typedef void (AutoPtr<T, ALLOCATOR>::*bool_type)() const;
	void bool_type_result() const {}
	operator bool_type () const
	{
		return ptr() ? &AutoPtr<T, ALLOCATOR>::bool_type_result : nullptr;
	}

	template<class U>
	bool operator == (const AutoPtr<U, ALLOCATOR> &rhs) const;

	template<class U>
	bool operator == (const U *rhs) const;

	bool operator == (const T *rhs) const;

	template<class U>
	bool operator != (const AutoPtr<U, ALLOCATOR> &rhs) const
	{	return !operator==(rhs);	}

	template<class U>
	bool operator != (const U *rhs) const
	{	return !operator==(rhs);	}

	bool operator != (const T *rhs) const
	{	return !operator==(rhs);	}

	bool operator < (const AutoPtr<T, ALLOCATOR> &rhs)
	{	return ptr() < rhs.ptr(); }

	//! Transfer ownership
	T* givePtr();

	template <class LhsT>
	LhsT* dynamicCast();

	template <class LhsT>
	LhsT* staticCast();

	AutoPtrParam setFromParam()
	{
		return AutoPtrParam(this);
	}

	void reset();
private:
	T *mPtr;
};


END_GENERIC_NAMESPACE


#include "src/AutoPtr.inline.h"

#endif // __GENERIC_MEMORY_AUTOPTR_H__
