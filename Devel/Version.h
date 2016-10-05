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
#ifndef __MATH_VERSION__
#define __MATH_VERSION__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include <string>
#include "../Base/Types.h"
#include <string>
#include <cstring>

namespace seed {

//==============================================================================
//	CLASS Version
//==============================================================================
class Version
{
public:
	class BuildID
	{
	public:
		static long long get()
		{
			static const char *sMonthName[] = 
			{
				"Jan",	"Feb",	"Mar",
				"Apr",	"May", "Jun",
				"Jul",	"Aug",	"Sep",
				"Oct",	"Nov",	"Dec"
			};

			const char *date = __DATE__;
			const char *time = __TIME__;

			char mon[1024];
			int year;
			int day;

			sscanf(date, "%s %d %d", mon, &day, &year);

			int hour,min,sec;
			sscanf(time, "%d:%d:%d", &hour, &min, &sec);

			int monNumber;
			for (monNumber = 0; monNumber < 12; ++monNumber)
				if (strcmp(sMonthName[monNumber], mon) == 0)
					break;

			if (monNumber == 12)	printf("error parsing month for build g\n");

			long long idVal = 0;

			idVal *= 60;
			idVal += sec;

			idVal *= 15;
			idVal += monNumber;

			idVal *= 25;
			idVal += hour;

			idVal *= 1000;
			idVal += year-2000;

			idVal *= 40;
			idVal += day;

			idVal *= 60;
			idVal += min;

			return idVal;
		}

		static void testId(long long idVal)
		{
			int sec, min, hour, day, mon, year;

			min = idVal % 60;
			idVal /= 60;

			day = idVal % 40;
			idVal /= 40;

			year = idVal % 1000;
			idVal /= 1000;

			hour = idVal % 25;
			idVal /= 25;

			mon = idVal % 15;
			idVal /= 15;

			sec = idVal % 60;

			printf("%d/%d/%d at %d:%02d:%02d\n", day, mon+1, year+2000, hour, min, sec);
		}

		static std::string idAsString(long long idVal)
		{
			static const char charMap[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
			static const int charMapSize = sizeof(charMap)/sizeof(charMap[0]);

			std::string stringId = "";
			int i = 0;
			while (idVal > 0)
			{
				if (i >= 4)
				{
					stringId = "-" + stringId;
					i = 0;
				}

				int c = idVal % charMapSize;
				stringId = charMap[c] + stringId;
				idVal = idVal / charMapSize;
				++i;
			}
			return stringId;
		}

		static long long stringAsId(const std::string &stringId)
		{
			static const char charMap[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
			static const int charMapSize = sizeof(charMap)/sizeof(charMap[0]);

			long long idVal = 0;
			for (int i = 0; i < (int)stringId.length(); ++i)
			{
				for (int j = 0; j < charMapSize; ++j)
				{
					if (stringId.c_str()[i] == charMap[j])
					{
						idVal *= charMapSize;
						idVal += j;
						break;
					}
				}
			}
			return idVal;
		}
	};


public:
	// fits a full version inside an 32bit integer
	class VersionInt
	{
	public:
		VersionInt()
		:
			_version()
		{}

		VersionInt(const VersionInt &rhs)
		{	_version = rhs._version;	}

		explicit VersionInt(const Version &rhs)
		:
			_version(((rhs.release() & 0xFF) << 24) | ((rhs.subVersion() & 0xFF)<< 16) | ((rhs.revision() & 0xFF)<< 8) | (rhs.bugFix() & 0xFF))
		{}

		static VersionInt fromInt32(uint32 briefVersion)
		{
			VersionInt version;
			version._version = briefVersion;
			return version;
		}

	private:
		// private to avoid confusion with VersionInt::fromInt32()
		VersionInt(uint8 release); 

	public:
		VersionInt(uint8 release, uint8 subVersion)
		:
			_version((release << 24) | (subVersion << 16))
		{}

		VersionInt(uint8 release, uint8 subVersion, uint8 revision)
		:
			_version((release << 24) | (subVersion << 16) | (revision << 8))
		{}

		VersionInt(uint8 release, uint8 subVersion, uint8 revision, uint8 bugFix)
		:
			_version((release << 24) | (subVersion << 16) | (revision << 8) | bugFix)
		{}

		uint32 asInt32() const { return _version; }
		uint8 release() const { return _version >> 24; }
		uint8 subVersion() const { return _version >> 16 & 0xFF; }
		uint8 revision() const { return _version >> 8 & 0xFF; }
		uint8 bugFix() const { return _version & 0xFF; }

	private:
		uint32 _version;
	};

	static int currentRevision() 
	{
		static int rev = 0;
		
		if (!rev)
		{
			char buf[2048];
			sscanf("$Rev: 3719 $", "%s %d", buf, &rev);
		}
		return rev;
	}
		
	static std::string currentRevisionDate() 
	{
		return "$Date: 2010-03-29 02:30:30 -0400 (Mon, 29 Mar 2010) $";
	}

	
	Version(const std::string &versionStr)
	:
		mRelease(0),
		mSubVersion(0),
		mRevision(0),
		mBugFix(0)
	{
		std::string::size_type pos, oldPos = 0;
		pos = versionStr.find(".", 0);
		if (pos == std::string::npos)
		{
			if (oldPos < versionStr.length())
			{
				std::string releaseStr(versionStr, oldPos);
				sscanf(releaseStr.c_str(), "%d", &mRelease);
			}

			return;
		}
			
		std::string releaseStr(versionStr, oldPos, pos);
		sscanf(releaseStr.c_str(), "%d", &mRelease);
		oldPos = pos + 1;
			
		pos = versionStr.find(".", oldPos);
		if (pos == std::string::npos)
		{
			if (oldPos < versionStr.length())
			{
				std::string subVersionStr(versionStr, oldPos);
				sscanf(subVersionStr.c_str(), "%d", &mSubVersion);
			}

			return;
		}
			
		std::string subVersionStr(versionStr, oldPos, pos);
		sscanf(subVersionStr.c_str(), "%d", &mSubVersion);
		oldPos = pos + 1;

		pos = versionStr.find(".", oldPos);
		if (pos == std::string::npos)
		{
			if (oldPos < versionStr.length())
			{
				std::string revisionStr(versionStr, oldPos);
				sscanf(revisionStr.c_str(), "%d", &mRevision);
			}
				
			return;
		}

		std::string revisionStr(versionStr, oldPos, pos);
		sscanf(revisionStr.c_str(), "%d", &mRevision);
		oldPos = pos + 1;

		if (oldPos < versionStr.length())
		{
			std::string bugFixStr(versionStr, oldPos);
			sscanf(bugFixStr.c_str(), "%d", &mBugFix);
		}
	}
		
	explicit Version(const VersionInt &intVersion)
	:
		mRelease(intVersion.release()),
		mSubVersion(intVersion.subVersion()),
		mRevision(intVersion.revision()),
		mBugFix(intVersion.bugFix())
	{}
		
	Version(int release, int subVersion)
	:
		mRelease(release),
		mSubVersion(subVersion),
		mRevision(0),
		mBugFix(0)
	{}

	Version(int release, int subVersion, int revision)
	:
		mRelease(release),
		mSubVersion(subVersion),
		mRevision(revision),
		mBugFix(0)
	{}

	Version(int release, int subVersion, int revision, int bugFix)
	:
		mRelease(release),
		mSubVersion(subVersion),
		mRevision(revision),
		mBugFix(bugFix)
	{}

	int release() const		{	return mRelease;	}
	int subVersion() const	{	return mSubVersion;	}
	int revision() const	{	return mRevision;	}
	int bugFix() const 		{	return mBugFix;		}

	void setRelease(int release)		{	mRelease = release;			}
	void setSubVersion(int subVersion)	{	mSubVersion = subVersion;	}
	void setRevision(int revision)		{	mRevision = revision;		}
	void setBugFix(int bugFix)			{	mBugFix = bugFix;			}
		
	uint32 toInt() const
	{
		return uint32( (mRelease << 24)    | 
					   (mSubVersion << 16) |
					   (mRevision << 8)    |
					   (mBugFix) );
	}
		
	std::string toString() const
	{
		char versionString[64];
		if (mBugFix)			{	sprintf(versionString, "%d.%d.%d.%d", mRelease, mSubVersion, mRevision, mBugFix);	}
		else if (mRevision)		{	sprintf(versionString, "%d.%d.%d", mRelease, mSubVersion, mRevision);	}
		else	 				{	sprintf(versionString, "%d.%d", mRelease, mSubVersion);	}

		return versionString;
	}

	bool operator < (const Version &rhs) const
	{
		return toInt() < rhs.toInt();
	}

	bool operator <= (const Version &rhs) const
	{
		return toInt() <= rhs.toInt();
	}

	bool operator > (const Version &rhs) const
	{
		return toInt() > rhs.toInt();
	}

	bool operator >= (const Version &rhs) const
	{
		return toInt() >= rhs.toInt();
	}

	bool operator == (const Version &rhs) const
	{
		return toInt() == rhs.toInt();
	}

	bool operator != (const Version &rhs) const
	{
		return toInt() != rhs.toInt();
	}

private:
	int mRelease;
	int mSubVersion;
	int mRevision;
	int mBugFix;
};

} // namespace seed

#endif // __MATH_VERSION__
