/*******************************************************************************
 Copyright 2011 Enseed inc.
 
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
#ifndef __GENERIC_WINDEBUG__
#define __GENERIC_WINDEBUG__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "../Base/Base.h"

#ifdef __cplusplus
#include <Generic/Base/TString.h>

#ifdef TARGET_DEBUG
#define CHECK_GLE(_fname) do {CheckGLE(#_fname, __FILE__, __LINE__);}while (0);
#define PRINT_WERR(_fname, hr) do {PrintWErr(hr, #_fname, __FILE__, __LINE__);}while (0);
#else 
#define CHECK_GLE(_fname) do {}while (0);
#define PRINT_WERR(hr)  do {}while (0);
#endif 

static inline std::string GetWindowsErrorStr(HRESULT hr)
{
	// Retrieve the system error message for the last-error code
	LPVOID lpMsgBuf;

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		hr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &lpMsgBuf,
		0, NULL );

	std::string str = (TCHAR*)lpMsgBuf;

	LocalFree(lpMsgBuf);

	return str;
}

static inline void PrintWErr(HRESULT hr, const char *aFunctionName, const char *aFileName, int aLineNb)
{
	std::string errStr = GetWindowsErrorStr(hr);
	printf("[%s:%d] Windows Error: %s returned (%d) %s", aFileName, aLineNb, aFunctionName, hr, errStr.c_str());
}

static inline void CheckGLE(const char *aFunctionName, const char *aFileName, int aLineNb)
{
	HRESULT hr = ::GetLastError();
	if (FAILED(hr))
	{
		PrintWErr(hr, aFunctionName, aFileName, aLineNb);
	}
}

#endif // __cplusplus

#endif // __GENERIC_WINDEBUG__
