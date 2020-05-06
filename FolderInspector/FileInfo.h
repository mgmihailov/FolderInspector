#pragma once

#include <string>

struct TimeInfo
{
	unsigned Day;
	unsigned Month;
	unsigned Year;
	unsigned Hours;
	unsigned Minutes;

	TimeInfo()
		: Day(0)
		, Month(0)
		, Year(0)
		, Hours(0)
		, Minutes(0)
	{
	}
};

struct FileInfo
{
	std::string FileName;
	unsigned long long FileSize;
	TimeInfo DateCreated;
	TimeInfo DateLastModified;
	int Level;
	bool IsDir;

	FileInfo()
		: FileSize(0)
		, Level(0)
		, IsDir(false)
	{
	}

	FileInfo(const char* fileName
		, unsigned long long fileSize
		, TimeInfo dateCreated
		, TimeInfo dateLastModified
		, int level
		, bool isDir)
			: FileName(fileName)
			, FileSize(fileSize)
			, DateCreated(dateCreated)
			, DateLastModified(dateLastModified)
			, Level(level)
			, IsDir(isDir)
	{}
};