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
#ifndef __ITL_ITERATOR_H__
#define __ITL_ITERATOR_H__

//==============================================================================
// FILE Iterator.h
//==============================================================================
// We have to use a special type of iterators since we do not iterate over
// real data.  For instance, when iterating over a pixmap rows, these
// rows are light objects created and destroyed as needed.  The traditional
// iterators generally assumes that references to remporary content is ok
// since they expect the iterator to iterate over existing data. For instance:
//
//  return &*(iter + 1)
//
// is expected to work on a traditionnal iterator.  This is also how the
// boost iterators are made.  In our case, &*(iter+1) is not valid:
//
//  {
//      RowRef row = *(iter + 1);     // OK, but we *create* a row reference
//      RowRef *rowPtr = &row;		  // OK
//      return rowPtr;                // Not OK since row will be destroyed
//  }
//
// The same thing appplies to the std::reverse_iterator which we cannot use.
// reverse_iterator can be created from a normal iterator, but it always
// returns iter-1 when it is referenced.  This is to facilitate the construction
// of rbegin() and rend() from begin() and end() (i.e. rend() returns begin(), 
// not begin()-1 as one might expect)
//------------------------------------------------------------------------------

//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================
#include <iterator>
#include "TypeInfo.h"
#include <Enseed/Generic/Devel/Debug.h>

#ifdef ITL_NAMESPACE
namespace ITL_NAMESPACE {
#endif

//==============================================================================
// CLASS IteratorManip
//==============================================================================
template<class ITERATORTYPE>
class IteratorManip
{
public:
	template<class T>
	static void increment(T &iter)
	{ iter.increment(); }

	template<class T>
	static void decrement(T &iter)
	{ iter.decrement(); }

	template<class T>
	static void advance(T &iter, int nb)
	{ iter.advance(nb); }
};

//------------------------------------------------------------------------------
// CLASS IteratorManip<std::forward_iterator_tag>
//------------------------------------------------------------------------------
template<>
class IteratorManip<std::forward_iterator_tag>
{
public:
	template<class T>
	static void increment(T &iter)
	{ iter.increment(); }
};

//------------------------------------------------------------------------------
// CLASS IteratorManip<std::bidirectional_iterator_tag>
//------------------------------------------------------------------------------
template<>
class IteratorManip<std::bidirectional_iterator_tag>
{
public:
	template<class T>
	static void increment(T &iter)
	{ iter.increment(); }

	template<class T>
	static void decrement(T &iter)
	{ iter.decrement(); }
};

//------------------------------------------------------------------------------
// CLASS IteratorManip<std::random_access_iterator_tag>
//------------------------------------------------------------------------------
template<>
class IteratorManip<std::random_access_iterator_tag>
{
public:
	template<class T>
	static void increment(T &iter)
	{ iter.advance(1); }

	template<class T>
	static void decrement(T &iter)
	{ iter.advance(-1); }

	template<class T>
	static void advance(T &iter, int nb)
	{ iter.advance(nb); }
};

//==============================================================================
// CLASS IteratorBaseConst
//==============================================================================
template<typename DERIVED, typename NONCONSTCONTENTTYPE, typename PTRTYPE, typename CONSTPTRTYPE, typename REFTYPE, typename CONSTREFTYPE, typename ITERATORTYPE>
class IteratorBaseConst
{
public:
	// defined for stl and co.
	typedef ITERATORTYPE iterator_category;
	typedef NONCONSTCONTENTTYPE value_type;
	typedef const NONCONSTCONTENTTYPE const_value_type;

	typedef typename TypeInfo<NONCONSTCONTENTTYPE>::difference_type difference_type;

	typedef CONSTPTRTYPE const_pointer;
	typedef CONSTREFTYPE const_reference;

	typedef REFTYPE reference;
	typedef PTRTYPE pointer;

private:
	IteratorBaseConst(const IteratorBaseConst&);
	IteratorBaseConst& operator=(const IteratorBaseConst&);

protected:
	IteratorBaseConst()
	{}

	const DERIVED& derived() const
	{	
		return *static_cast<const DERIVED*>(this); 
	}

	DERIVED& derived()
	{	
		DERIVED &d = *static_cast<DERIVED*>(this);
		return d;
	}

public:
	const_reference operator*() const
	{	return derived().dereference();	}

	const_pointer operator->() const
	{	return &derived().dereference();	}

	DERIVED operator++(int)
	{
		DERIVED prev = derived();
		IteratorManip<iterator_category>::increment(derived());
		return prev; 
	}

	DERIVED operator--(int)
	{	
		DERIVED prev = derived();
		IteratorManip<iterator_category>::decrement(derived());
		return prev; 
	}

	DERIVED operator+(int skipNb) const
	{
		DERIVED iter = derived();
		IteratorManip<iterator_category>::advance(iter, skipNb);
		return iter;
	}

	DERIVED operator-(int skipNb) const
	{
		DERIVED iter = derived();
		IteratorManip<iterator_category>::advance(iter, -skipNb);
		return iter;
	}

	bool operator==(const DERIVED& rhs) const
	{	return derived().equals(rhs);	}

	bool operator!=(const DERIVED& rhs) const
	{	return !derived().equals(rhs);	}

	bool operator<(const DERIVED& rhs) const
	{	return derived().distance_to(rhs) > 0;	}

	bool operator<=(const DERIVED& rhs) const
	{	return derived().distance_to(rhs) >= 0;	}

	bool operator>(const DERIVED& rhs) const
	{	return derived().distance_to(rhs) < 0;	}

	bool operator>=(const DERIVED& rhs) const
	{	return derived().distance_to(rhs) <= 0;	}

	DERIVED& operator++()
	{
		IteratorManip<iterator_category>::increment(derived());
		return derived();
	}

	DERIVED& operator--()
	{
		IteratorManip<iterator_category>::decrement(derived());
		return derived();
	}

	DERIVED& operator+=(int skipNb)
	{
		IteratorManip<iterator_category>::advance(derived(), skipNb);
		return derived();
	}

	DERIVED& operator-=(int skipNb)
	{
		IteratorManip<iterator_category>::advance(derived(), -skipNb);
		return derived();
	}

	difference_type operator-(const DERIVED &rhs) const
	{	return rhs.distance_to(derived()); }
};

//==============================================================================
// CLASS IteratorBaseNonConst
//==============================================================================
template<typename DERIVED, typename VALUETYPE, typename PTRTYPE, typename CONSTPTRTYPE, typename REFTYPE, typename CONSTREFTYPE, typename ITERATORTYPE>
class IteratorBaseNonConst: public IteratorBaseConst<DERIVED, VALUETYPE, PTRTYPE, CONSTPTRTYPE, REFTYPE, CONSTREFTYPE, ITERATORTYPE>
{
private:
	typedef IteratorBaseConst<DERIVED, VALUETYPE, PTRTYPE, CONSTPTRTYPE, REFTYPE, CONSTREFTYPE, ITERATORTYPE> _Super;

public:
	IteratorBaseNonConst() {}

	typedef typename _Super::reference reference;
	typedef typename _Super::pointer pointer;

	using _Super::operator*;
	reference operator*()
	{	return _Super::derived().dereference();	}

	using _Super::operator->;
	pointer operator->()
	{	return &_Super::derived().dereference();	}
};

//==============================================================================
// CLASS IteratorBaseConstSelector
//==============================================================================
// assume non-const by default
template<typename DERIVED, typename CONTENTTYPE, typename PTRTYPE, typename CONSTPTRTYPE, typename REFTYPE, typename CONSTREFTYPE, typename ITERATORTYPE>
class IteratorBaseConstSelector: public IteratorBaseNonConst<DERIVED, CONTENTTYPE, PTRTYPE, CONSTPTRTYPE, REFTYPE, CONSTREFTYPE, ITERATORTYPE>
{
private:
	typedef IteratorBaseNonConst<DERIVED, CONTENTTYPE, PTRTYPE, CONSTPTRTYPE, REFTYPE, CONSTREFTYPE, ITERATORTYPE> _Super;

public:
	IteratorBaseConstSelector()  {}
};

//------------------------------------------------------------------------------
// CLASS IteratorBaseConstSelector - for const cases
//------------------------------------------------------------------------------
template<typename DERIVED, typename CONTENTTYPE, typename PTRTYPE, typename CONSTPTRTYPE, typename REFTYPE, typename CONSTREFTYPE, typename ITERATORTYPE>
class IteratorBaseConstSelector<DERIVED, const CONTENTTYPE, PTRTYPE, CONSTPTRTYPE, REFTYPE, CONSTREFTYPE, ITERATORTYPE>: public IteratorBaseConst<DERIVED, CONTENTTYPE, PTRTYPE, CONSTPTRTYPE, REFTYPE, CONSTREFTYPE, ITERATORTYPE>
{
private:
	typedef IteratorBaseConst<DERIVED, CONTENTTYPE, PTRTYPE, CONSTPTRTYPE, REFTYPE, CONSTREFTYPE, ITERATORTYPE> _Super;

public:
	IteratorBaseConstSelector() {}

private:
	IteratorBaseConstSelector(const IteratorBaseConstSelector&);
	IteratorBaseConstSelector& operator=(const IteratorBaseConstSelector&);
};

//==============================================================================
// CLASS IteratorBase
//==============================================================================
template<typename DERIVED, typename CONTENTTYPE, typename PTRTYPE=typename TypeInfo<CONTENTTYPE>::pointer, typename CONSTPTRTYPE=typename TypeInfo<CONTENTTYPE>::const_pointer, typename REFTYPE=typename TypeInfo<CONTENTTYPE>::reference, typename CONSTREFTYPE=typename TypeInfo<CONTENTTYPE>::const_reference, typename ITERATORTYPE=std::random_access_iterator_tag>
class IteratorBase: public IteratorBaseConstSelector<DERIVED, CONTENTTYPE, PTRTYPE, CONSTPTRTYPE, REFTYPE, CONSTREFTYPE, ITERATORTYPE>
{
private:
	typedef IteratorBaseConstSelector<DERIVED, CONTENTTYPE, PTRTYPE, CONSTPTRTYPE, REFTYPE, CONSTREFTYPE, ITERATORTYPE> _Super;

public:
	IteratorBase() {}
private:
	IteratorBase(const IteratorBase&);
	IteratorBase& operator=(const IteratorBase&);
};


//==============================================================================
// CLASS ReverseIteratorAdaptor
//==============================================================================
// We cannot use the std::reverse_iterator since it expects references to be actual references.
// In our case, we are doing a logical iteration rather than a physical iteration and the
// iterator is holding temporary objects.  Doing &*iter on a temporary iterator fails in our
// case.  So we reimplement a reverse_iterator that doesn't take such references.
template<class ITER>
class ReverseIteratorAdaptor
{
public:
	typedef typename ITER::value_type value_type;
	typedef typename ITER::const_value_type const_value_type;

	typedef typename ITER::pointer pointer;
	typedef typename ITER::reference reference;

	typedef typename ITER::const_pointer const_pointer;
	typedef typename ITER::const_reference const_reference;

public:
	ReverseIteratorAdaptor(const ITER &iter) : _iter(iter), _prev(iter) {}

	template<class RHS_ITER> friend class ReverseIteratorAdaptor;

	template<class RHS_ITER>
	ReverseIteratorAdaptor(const ReverseIteratorAdaptor<RHS_ITER> &iter) : _iter(iter._iter), _prev(iter._prev) {}

	bool operator != (const ReverseIteratorAdaptor &rhs)
	{	return _iter != rhs._iter; }

	ReverseIteratorAdaptor& operator++()
	{	--_iter; return *this; }
	
	ReverseIteratorAdaptor& operator--()
	{	++_iter; return *this; }

	reference operator*()
	{
		_prev = _iter;
		--_prev;
		return *_prev;
	}

	pointer operator->()
	{	
		_prev = _iter;
		--_prev;
		return &*_prev;
	}

	ReverseIteratorAdaptor operator-(int skipNb) const
	{
		ReverseIteratorAdaptor iter = *this;
		iter -= skipNb;
		return iter;
	}

	ReverseIteratorAdaptor operator+(int skipNb) const
	{
		ReverseIteratorAdaptor iter = *this;
		iter += skipNb;
		return iter;
	}

	ReverseIteratorAdaptor& operator-=(int skipNb)
	{
		_iter += skipNb;
		return *this;
	}

	ReverseIteratorAdaptor& operator+=(int skipNb)
	{
		_iter -= skipNb;
		return *this;
	}

private:
	ITER _prev; // we have to keep a reference to _rev when we return
				// the address of its content. This is why we cannot use
				// std::reverse_iterator
	ITER _iter;
};

#ifdef ITL_NAMESPACE
}
#endif

#endif // __ITL_PIXELITERATOR_H__
