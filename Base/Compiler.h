/*******************************************************************************
 Copyright 2008 Enseed inc.
 
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
#ifndef __GENERIC_BASE_COMPILER__
#define __GENERIC_BASE_COMPILER__

#define MK_COUNTOF(_array) sizeof(_array)/sizeof(*_array)

// just to keep track of the global variables
#define MK_GLOBAL

#ifdef __GNUC__

// welcome gcc

#define GENERIC_WARN_UNUSED_RESULT __attribute__ ((warn_unused_result))
#define GENERIC_CURRENT_FUNCTION_NAME __PRETTY_FUNCTION__
#define GENERIC_PREFETCH_READ(ptr)	__builtin_prefetch((ptr), 0)
#define GENERIC_PREFETCH_WRITE(ptr)	__builtin_prefetch((ptr), 1)
#define GENERIC_DEBUG_IN_COLORS

#elif _MSC_VER

#ifndef WIN32
#define WIN32
#endif // WIN32

#ifdef _M_X64
#ifndef _WIN64
#define _WIN64
#endif // _WIN64
#define WIN64
#define X64
#endif

// welcome Microsoft Visual c++
#define GENERIC_PREFETCH(ptr)	PreFetchCacheLine(PF_NON_TEMPORAL_LEVEL_ALL, ptr);
#define GENERIC_PREFETCH_READ(ptr) MK_PREFETCH(ptr)
#define GENERIC_WARN_UNUSED_RESULT
#define GENERIC_CURRENT_FUNCTION_NAME __FUNCTION__

#define __STR2__(x) #x
#define __STR1__(x) __STR2__(x)
#define __LOC__ __FILE__ "("__STR1__(__LINE__)") : Warning Msg: "


//#pragma warning (default: 4619) // windows and stl don't like

//#pragma warning (disable: 4820) // W4 'bytes' bytes padding added after construct 'member_name'
//#pragma warning (disable: 4668) // W4 'symbol' is not defined as a preprocessor macro, replacing with '0' for 'directives'
#pragma warning (disable: 4996) // W3 'function': was declared deprecated
//#pragma warning (disable: 4127) // W4 conditional expression is constant
//#pragma warning (disable: 4365) // W4 'action' : conversion from 'type_1' to 'type_2', signed/unsigned mismatch

//#pragma warning (disable: 4571) // BOOST: W4 Informational: catch(...) semantics changed since Visual C++ 7.1; structured exceptions (SEH) are no longer caught
//#pragma warning (disable: 4061) // BOOST: W4 enumerator 'identifier' in switch of enum 'enumeration' is not explicitly handled by a case label

//#pragma warning (disable: 4350) // 

//#pragma warning (default: 4062) // enumerator 'identifier' in switch of enum 'enumeration' is not handled
//#pragma warning (default: 4191) // perhaps later...
//#pragma warning (default: 4263) // 'function' : member function does not override any base class virtual member function
//#pragma warning (default: 4264) // 'virtual_function' : no override available for virtual member function from base 'class'; function is hidden
//#pragma warning (default: 4265) // 'class' : class has virtual functions, but destructor is not virtual
//#pragma warning (default: 4287) // 'operator' : unsigned/negative constant mismatch
//#pragma warning (default: 4296) // 'operator' : expression is always false
//#pragma warning (default: 4412) // 'function' : function signature contains type 'type'; C++ objects are unsafe to pass between pure code and mixed or native.
//#pragma warning (default: 4514) // 'function' : unreferenced inline function has been removed
//#pragma warning (default: 4545) // expression before comma evaluates to a function which is missing an argument list
//#pragma warning (default: 4546) // function call before comma missing argument list 
//#pragma warning (default: 4547)  // 'operator' : operator before comma has no effect; expected operator with side-effect
//#pragma warning (default: 4549) // 'operator' : operator before comma has no effect; did you intend 'operator'?
//#pragma warning (default: 4536) // 'type name' : type-name exceeds meta-data limit of 'limit' characters
//#pragma warning (default: 4625) // 'derived class' : copy constructor could not be generated because a base class copy constructor is inaccessible
//#pragma warning (default: 4626)
//#pragma warning (default: 4640) // enable one day
//#pragma warning (default: 4928) // illegal copy-initialization; more than one user-defined conversion has been implicitly applied
//#pragma warning (default: 4946) // reinterpret_cast used between related classes: 'class1' and 'class2'


//#define snprintf _snprintf
#define stricmp _stricmp
#define strcasecmp stricmp
#define strncasecmp _strnicmp
#ifndef nullptr
#if defined(__cplusplus) && __cplusplus < 199711L
#define nullptr NULL
#endif
#endif // ] nullptr

#endif

#endif // __GENERIC_BASE_COMPILER__
