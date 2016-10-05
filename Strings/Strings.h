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
#ifndef __GENERIC_TEXT_STRINGS_H__
#define __GENERIC_TEXT_STRINGS_H__

#include <iterator>
#include <algorithm>
#include <codecvt>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <cstdarg>
#include <sstream>
#include <Generic/Base/Base.h>
#include <Generic/Base/Types.h>

BEGIN_GENERIC_NAMESPACE

class Strings
{
public:
	static std::string format(const char *fstring, ...)
	{
		char msg[4096];

		va_list args;
		va_start(args, fstring);
		std::vsprintf(msg, fstring, args);
		va_end(args);

		return std::string(msg);
	}

	static std::vector<std::string> splitstr(const std::string &str)
	{
		std::vector<std::string> vec;
		std::string cur;
		for (std::string::const_iterator iter = str.begin(); iter != str.end(); ++iter)
		{
			if (::isspace(*iter))
			{
				if (!cur.empty())
				{
					vec.push_back(cur);
					cur.clear();
				}
			}
			else
			{
				cur.push_back(*iter);
			}
		}

		if (!cur.empty())
			vec.push_back(cur);

		return vec;
	}

	static std::vector<std::string> splitstr(const std::string &str, char sep)
	{
		return splitstr(str, sep, true, 0);
	}

	static std::vector<std::string> splitstr(const std::string &str, char sep, bool skipEmpty, int nbSplit)
	{
		std::vector<std::string> vec;
		std::string cur;
		for (std::string::const_iterator iter = str.begin(); iter != str.end(); ++iter)
		{
			if (*iter == sep)
			{
				if (!cur.empty() || !skipEmpty)
				{
					vec.push_back(cur);
					cur.clear();
					if (nbSplit == vec.size())
					{
						// copy the remaining
						std::string endStr;
						endStr.insert(endStr.begin(), iter+1, str.end());
						if (!endStr.empty())
							vec.push_back(endStr);
						return vec;
					}
				}
			}
			else
			{
				cur.push_back(*iter);
			}
		}

		if (!cur.empty())
			vec.push_back(cur);

		return vec;
	}


	// split from the end
	static std::vector<std::string> rsplitstr(const std::string &str, char sep, bool skipEmpty, int nbSplit)
	{
		std::vector<std::string> vec;
		std::string cur;
		for (std::string::const_reverse_iterator iter = str.rbegin(); iter != str.rend(); ++iter)
		{
			if (*iter == sep)
			{
				if (!cur.empty() || !skipEmpty)
				{
					vec.insert(vec.begin(), cur);
					cur.clear();
					if (nbSplit == vec.size())
					{
						// copy the remaining
						std::string endStr;
						endStr.insert(endStr.begin(), iter+1, str.rend());
						std::reverse(endStr.begin(), endStr.end());
						if (!endStr.empty())
							vec.insert(vec.begin(), endStr);
						return vec;
					}
				}
			}
			else
			{
				cur.insert(cur.begin(), *iter);
			}
		}

		if (!cur.empty())
			vec.insert(vec.begin(), cur);

		return vec;
	}

	static std::string tolower(const std::string &aString)
	{
		std::string lcName;
		std::transform(aString.begin(), aString.end(), std::back_inserter(lcName), std::ptr_fun(::tolower));
		return lcName;
	}

	static std::string toupper(const std::string &aString)
	{
		std::string ucName;
		std::transform(aString.begin(), aString.end(), std::back_inserter(ucName), std::ptr_fun(::toupper));
		return ucName;
	}
	
	// parse comma separated string, supporting quotes
	static std::vector<std::string> parseArgumentString(const std::string &args)
	{
		std::vector<std::string> vec;
		std::string cur;
		bool isEscaped = false;
		char isInQuote = 0;

		for (std::string::const_iterator iter = args.begin(); iter != args.end(); ++iter)
		{
			if (isEscaped)
			{
				switch(*iter)
				{
				case('\\'):
					cur.push_back('\\');
					break;
				case('r'):
					cur.push_back('\r');
					break;
				case('n'):
					cur.push_back('\n');
					break;
				case('\''):
					cur.push_back('\'');
					break;
				case('"'):
					cur.push_back('\"');
					break;

				isEscaped = false;
				}
			}
			else
			{
				switch(*iter)
				{
				case('\\'):
					isEscaped = true;
					break;
				case(','):
					if (isInQuote)
					{
						cur.push_back(*iter);
					}
					else
					{
						vec.push_back(cur);
						cur.clear();
					}
					break;
				case('\''):
					if (isInQuote)
					{
						isInQuote = 0;
					}
					else
					{
						isInQuote = '\'';
					}
					break;
				case('\"'):
					if (isInQuote)
					{
						isInQuote = 0;
					}
					else
					{
						isInQuote = '\"';
					}
					break;
				default:
					cur.push_back(*iter);
				}
			}
		}
		vec.push_back(cur);
		return vec;
	}

	static std::u32string toUTF32(const std::string &iUtf8)
	{
		// https://social.msdn.microsoft.com/Forums/en-US/8f40dcd8-c67f-4eba-9134-a19b9178e481/vs-2015-rc-linker-stdcodecvt-error?forum=vcgeneral
		// This gets around a bug in microsoft STL
		//typedef std::codecvt<char32_t, char, std::mbstate_t> facet_type;
		//std::wstring_convert<facet_type, char32_t> convert;
		typedef std::codecvt<unsigned int, char, std::mbstate_t> facet_type;
		std::wstring_convert<facet_type, unsigned int> convert;
		std::u32string utf32 = reinterpret_cast<std::u32string&>(convert.from_bytes(iUtf8));
		return utf32;
	}


	static std::wstring toUTF16(const std::string &iUtf8)
	{
		typedef std::codecvt<wchar_t,char,std::mbstate_t> facet_type;
		std::wstring_convert<facet_type, wchar_t> convert;
		std::wstring utf16 = convert.from_bytes(iUtf8);
		return utf16;
	}

	static std::string toUTF8(const std::wstring &iUtf16)
	{
		typedef std::codecvt_utf8<wchar> facet_type;
		std::wstring_convert<facet_type, wchar> convert;
		std::string utf8 = convert.to_bytes(iUtf16);
		return utf8;
	}

	static std::string toUTF8(const std::u32string &iUtf32)
	{
		typedef std::codecvt_utf8<char32_t> facet_type;
		std::wstring_convert<facet_type, char32_t> convert;
		std::string utf8 = convert.to_bytes(iUtf32);
		return utf8;
	}

	static std::string trim(const std::string &iStr)
	{
		std::string wStr = iStr;
		boost::trim(wStr);
		return wStr;
	}

	static std::string::iterator findClosing(std::string::iterator iter, std::string::iterator strEnd, const char *openBracket = "([{", const char *closeBracket = ")]}")
	{
		std::deque<char> wLevels;
		while (iter != strEnd)
		{
			char wC = *iter;
			const char *wFound = strchr(openBracket, wC);
			if (wFound != nullptr)
			{
				wLevels.push_back(wC);
			}
			wFound = strchr(closeBracket, wC);
			if (wFound != nullptr && !wLevels.empty())
			{
				wLevels.pop_back();
			}

			if (wLevels.empty())
				return iter;

			++iter;
		}
	}

	static std::vector<std::string> splitTop(const std::string &iString, const char *openBracket, const char *closeBracket, const char *separator)
	{
		std::deque<char> wLevels;
		std::vector<std::string> wSplit;
		auto strStart = iString.begin();
		for(auto iter = iString.begin(); iter != iString.end(); ++iter)
		{
			char wC = *iter;
			const char *wFound = strchr(openBracket, wC);
			if (wFound != nullptr)
			{
				wLevels.push_back(wC);
			}
			wFound = strchr(closeBracket, wC);
			if (wFound != nullptr && !wLevels.empty())
			{
				wLevels.pop_back();
			}

			wFound = strchr(separator, wC);
			if (wFound != nullptr && wLevels.empty())
			{
				std::string str(strStart, iter);
				wSplit.push_back(str);
				strStart = iter+1;
			}
		}

		if (strStart != iString.end())
		{
			std::string str(strStart, iString.end());
			wSplit.push_back(str);
		}


		return wSplit;
	}


	template<class T>
	static std::string toString(T x)
	{
		std::stringstream str;
		str << x;
		return str.str();
	}

	template<class T>
	static std::string join(const char *separator, T start, T end)
	{
		std::stringstream strm;
		bool first = false;
		T iter = start;
		while (iter != end)
		{
			if (!first)
			{
				strm << ",";
			}
			else
			{
				first = false;
			}
			strm << *iter;
			++iter;
		}
		return strm.str();
	}

	static bool beginsWith(const std::string &str, const std::string &pattern, bool caseSensitive = true)
	{
		if (caseSensitive)
			return boost::starts_with(str, pattern);
		else
			return boost::istarts_with(str, pattern);
	}

	static bool endsWith(const std::string &str, const std::string &pattern, bool caseSensitive = true)
	{
		if (caseSensitive)
			return boost::ends_with(str, pattern);
		else
			return boost::iends_with(str, pattern);
	}
};

END_GENERIC_NAMESPACE

#endif // ] __GENERIC_TEXT_STRINGS_H__
