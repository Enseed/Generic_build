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
#ifndef __GENERIC_BASE_PATH__
#define __GENERIC_BASE_PATH__

#include <string>
#include <vector>

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
namespace seed {

class PathStyle
{
public:
	typedef enum
	{
		STYLE_POSIX,
		STYLE_WINDOWS,
		STYLE_MACLEGACY
	} Type;
};

class PathUtils
{
public:
	template<int STYLE>	inline static const char* separator();
	template<int STYLE>	inline static const char separatorChar()
	{	return separator<STYLE>()[0]; }

	template<int Style>	inline static bool isPathRelative(const std::string &aPath);
};

template<> inline const char* PathUtils::separator<PathStyle::STYLE_POSIX>()		{	return "/";	 }
template<> inline const char* PathUtils::separator<PathStyle::STYLE_WINDOWS>()		{	return "\\"; }
template<> inline const char* PathUtils::separator<PathStyle::STYLE_MACLEGACY>()	{	return ":";	 }

template<> inline bool PathUtils::isPathRelative<PathStyle::STYLE_POSIX>(const std::string &aPath)
{
	if (aPath.empty())
		return true;

	if (aPath[0] == separatorChar<PathStyle::STYLE_POSIX>())
		return false;

	return true;
}

template<> inline bool PathUtils::isPathRelative<PathStyle::STYLE_WINDOWS>(const std::string &aPath)
{
	if (aPath.empty())
		return true;

	if (aPath[0] == separatorChar<PathStyle::STYLE_WINDOWS>()) // e.g. "\\servername\..."
		return false;

	if (aPath.find(":") != std::string::npos) // e.g. "C:\"
		return false;

	return true;
}

template<> inline bool PathUtils::isPathRelative<PathStyle::STYLE_MACLEGACY>(const std::string &aPath);

template<int STYLE>
class _TPath
{
public:
	_TPath()
	:
		_path()
	{}

	typedef enum
	{
		PATH_ABSOLUTE,
		PATH_RELATIVE
	} PathType;

	static const char* separator() { return PathUtils::separator<STYLE>(); }

	explicit _TPath(const char *path)
	:
		_path(path)
	{}

	explicit _TPath(const std::string &path)
	:
		_path(path)
	{}

	_TPath(const _TPath &rhs)
	:
		_path(rhs._path)
	{}

	_TPath& operator=(const _TPath &rhs)
	{
		_path = rhs._path;
		return *this;
	}

	bool operator < (const _TPath &rhs) const
	{	return _path < rhs._path; }

	bool operator <= (const _TPath &rhs) const
	{	return _path <= rhs._path; }
	bool operator > (const _TPath &rhs) const
	{	return _path > rhs._path; }

	bool operator >= (const _TPath &rhs) const
	{	return _path >= rhs._path; }
	bool operator != (const _TPath &rhs) const
	{	return _path != rhs._path; }

	template<class T>
	bool operator==(const T &rhs)  const { return _path == rhs; }

	bool operator==(const _TPath &rhs) const { return _path == rhs._path; }
	void append(const char *path)
	{
		if (!_path.empty() && _path[_path.length()-1] == separator()[0])
			_path += path;
		else
			_path += std::string(separator()) + std::string(path);
	}

	void append(const std::string &path)
	{
		append(path.c_str());
	}

	void append(const _TPath &path)
	{
		append(path.str());
	}

	static bool findReplace(std::string *str, const std::string &find, const std::string &replace)
	{
		std::string::size_type pos = str->rfind(find);
		if (pos == std::string::npos)
			return false;

		if (pos == 0)
			return false; // this is a network path starting with "\\"

		*str = str->substr(0, pos) + replace + str->substr(pos + find.length());
		return true;
	}

	_TPath parent() const
	{
		std::string parPath = _path;

		// make sure there are no trailing separators
		std::string doubleSep = std::string(separator()) + std::string(separator());
		while (findReplace(&parPath, doubleSep, separator()))
		{}

		// find last occurrence of separator
		std::string::size_type lastSep = parPath.rfind(separator());
		if (lastSep == std::string::npos)
			return _TPath("");

		if (lastSep == parPath.length()-1)
		{
			// last char is separator
			parPath = parPath.substr(0, lastSep);
			lastSep = parPath.rfind(separator());
			if (lastSep == std::string::npos)
				return _TPath("");
		}

		return _TPath(parPath.substr(0, lastSep+1));
	}

	_TPath location() const
	{
		std::string parPath = _path;

		// make sure there are no trailing separators
		std::string doubleSep = std::string(separator()) + std::string(separator());
		while (findReplace(&parPath, doubleSep, separator()))
		{
		}

		// find last occurrence of separator
		std::string::size_type lastSep = parPath.rfind(separator());
		if (lastSep == std::string::npos)
			return _TPath("");

		return _TPath(parPath.substr(0, lastSep + 1));
	}


	_TPath pathByAppending(const char *path) const
	{
		_TPath retPath(_path);
		retPath.append(path);
		return retPath;
	}


	_TPath pathByAppending(const std::string &path) const
	{
		return pathByAppending(path.c_str());
	}
	_TPath pathByAppending(const _TPath &relativePath) const
	{
		return pathByAppending(relativePath.str());
	}

	_TPath operator + (const char *path) const
	{
		return pathByAppending(path);
	}

	_TPath operator + (const std::string path) const
	{
		return pathByAppending(path);
	}

	_TPath operator + (const _TPath &relativePath) const
	{
		return pathByAppending(relativePath);
	}

	_TPath& operator += (const char *path)
	{
		append(path);
		return *this;
	}

	_TPath operator += (const std::string &path)
	{
		append(path);
		return *this;
	}

	_TPath operator += (const _TPath &relativePath)
	{
		append(relativePath);
		return *this;
	}
	std::string fileName() const
	{
		std::string::size_type pos = _path.rfind(separator());
		if (pos == std::string::npos)
			return _path;

		std::string name = _path.substr(pos+1);
		if (name.empty())
		{
			name = parent().fileName();
			if (name.empty())
				name = _path;
		}
		return name;
	}

	std::string fileExtension() const
	{
		std::string name = fileName();
		std::string::size_type pos = name.rfind(".");
		if (pos == std::string::npos)
			return "";

		std::string ext = name.substr(pos+1);
		std::transform(ext.begin(), ext.end(), ext.begin(), (int (*)(int))tolower);
		return ext;
	}

	std::string fileNameWithoutExtension() const
	{
		std::string name = fileName();

		std::string::size_type pos = name.rfind(".");
		if (pos == std::string::npos)
			return name;

		return name.substr(0, pos);
	}
	void set(const char *path)
	{ _path = path; }

	void set(const std::string &path)
	{ _path = path; }

	void set(const _TPath &path)
	{ _path = path._path; }

	const std::string& str() const 
	{ return _path; }

	bool isNull() const { return empty(); }
	bool empty() const
	{
		return _path.empty();
	}

	static _TPath implode(const std::vector<std::string> &details)
	{
		return implode(details.begin(), details.end());
	}

	template<class ITER>
	static _TPath implode(ITER begin, const ITER &end)
	{
		if (begin == end)
			return _TPath();

		_TPath path = _TPath(*begin);
		while (++begin != end)
			path += *begin;

		return _TPath(path);
	}

	std::vector<std::string> explode() const
	{
		std::vector<std::string> details;
		std::string leftOver = _path;
		while (!leftOver.empty())
		{
			std::string::size_type firstDelimiterPos = leftOver.find(separator());
			if (firstDelimiterPos == std::string::npos)
			{
				details.push_back(leftOver);
				leftOver.clear();
			}
			else if (firstDelimiterPos == 0)
			{
				// skip
				leftOver = leftOver.substr(1);
			}
			else
			{
				std::string leftPart = leftOver.substr(0, firstDelimiterPos);
				details.push_back(leftPart);
				leftOver = leftOver.substr(firstDelimiterPos);
			}
		}
		return details;
	}

	bool isRelative() const
	{
		return PathUtils::isPathRelative<STYLE>(_path);
	}

	bool isAbsolute() const
	{
		return !isRelative();
	}

	_TPath generateIndexName(int index) const
	{
		std::stringstream indexStr;
		indexStr << index;

		// check if there is an extension
		std::string ext = fileExtension();
		if (ext.empty())
		{
			// case "file" -> "file.1"
			return parent() + (fileName() + "." + indexStr.str());
		}


		_TPath noExtPath = parent() + fileNameWithoutExtension();
		std::string oldIndexExt = noExtPath.fileExtension();
		// check if there is already an index
		if (oldIndexExt.empty())
		{
			// no index, but we have an extension, check if it's numeric extension
			int oldIndex;
			if (sscanf(ext.c_str(), "%d", &oldIndex) == 1)
			{
				// it is, replace it
				// case "file.1" -> "file.2"
				return parent() + (fileNameWithoutExtension() + "." + indexStr.str());
			}

			// it's not - it's a real extension
			// case "file.txt" -> "file.1.txt"
			return parent() + (fileNameWithoutExtension() + "." + indexStr.str() + "." + ext);
		}

		// we have an index extension, make sure it's numerical
		int oldIndex;
		if (sscanf(oldIndexExt.c_str(), "%d", &oldIndex) == 1)
		{
			// it is, change it
			// case "file.1.txt" -> "file.2.txt"
			return noExtPath.parent() + (noExtPath.fileNameWithoutExtension() + "." + indexStr.str() + "." + ext);
		}

		// it's not numerical, see if the other extension was
		if (sscanf(ext.c_str(), "%d", &oldIndex) == 1)
		{
			// it is, replace it
			// case "file.abc.1" -> "file.abc.2"
			return parent() + (fileNameWithoutExtension() + "." + indexStr.str());
		}

		// it's not - it's a real extension
		// case "file.abc.txt" -> "file.abc.1.txt"
		return parent() + (fileNameWithoutExtension() + "." + indexStr.str() + "." + ext);
	}



private:
	std::string _path;
};

typedef _TPath<PathStyle::STYLE_WINDOWS> WindowsPath;
typedef _TPath<PathStyle::STYLE_POSIX> PosixPath;
typedef _TPath<PathStyle::STYLE_MACLEGACY> MacLegacyPath;

#ifdef _WIN32
typedef WindowsPath Path;
#else
typedef PosixPath Path;
#endif

} // namespace seed

namespace sd = seed;

#endif // __GENERIC_BASE_PATH__
