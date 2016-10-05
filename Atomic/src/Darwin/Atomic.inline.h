/*******************************************************************************
Copyright 2006-2010 Enseed inc.

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
#ifndef __SEED_ASYNC_SRC_DARWIN_ATOMIC_INLINE_H__
#define __SEED_ASYNC_SRC_DARWIN_ATOMIC_INLINE_H__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "../../Atomic.h"
#include <libkern/OSAtomic.h>

//==============================================================================
//	CLASS Atomic
//==============================================================================
BEGIN_GENERIC_NAMESPACE
inline sint32 Atomic::decrement(volatile sint32 *aValue)
{	return OSAtomicDecrement32Barrier(aValue); }

inline sint32 Atomic::increment(volatile sint32 *aValue)
{	return OSAtomicIncrement32Barrier(aValue); }

END_GENERIC_NAMESPACE

#endif // __SEED_ASYNC_SRC_DARWIN_ATOMIC_INLINE_H__
