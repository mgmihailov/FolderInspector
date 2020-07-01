#include "Utils.h"

TimeInfo::TimeInfo()
	: Day(0)
	, Month(0)
	, Year(0)
	, Hours(0)
	, Minutes(0)
{
}

FileInfo::FileInfo()
	: FileSize(0)
	, Level(0)
{
}

FileInfo::FileInfo(const char* fileName
	, unsigned long long fileSize
	, TimeInfo dateCreated
	, TimeInfo dateLastModified
	, int level)
		: FileName(fileName)
		, FileSize(fileSize)
		, DateCreated(dateCreated)
		, DateLastModified(dateLastModified)
		, Level(level)
{}

Filters::Filters()
{}