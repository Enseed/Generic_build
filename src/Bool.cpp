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
//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "../Bool.h"
#include <sstream>
#include <string.h>

namespace seed {

/*
 INLINED
std::string Bool::serialize(bool var)
{
	if (var) return "true";
	else	return "false";
}

bool Bool::deSerialize(const std::string &str)
{
	// how many ways are there to say no...?
	if (str.find_first_not_of(" \t\n\r") == std::string::npos || str == "0" ||
		str == "false"	|| str == "False"	|| str == "FALSE" || 
		str == "no" 	|| str == "No"		|| str == "NO" || 
		str == "null"	|| str == "Null" 	|| str == "NULL" ||
		str == "nil" 	|| str == "Nil"		|| str == "NIL")
	{
		return false;
	}
	
	// we assume that anything else is true
	return true;
}
*/

} // namespace seed


