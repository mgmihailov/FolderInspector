#pragma once

#include <string>
#include <unordered_map>

struct TimeInfo
{
	unsigned Day;
	unsigned Month;
	unsigned Year;
	unsigned Hours;
	unsigned Minutes;

	TimeInfo();
};

struct FileInfo
{
	std::string FileName;
	unsigned long long FileSize;
	TimeInfo DateCreated;
	TimeInfo DateLastModified;
	int Level;

	FileInfo();

	FileInfo(const char* fileName
		, unsigned long long fileSize
		, TimeInfo dateCreated
		, TimeInfo dateLastModified
		, int level);
};

struct Filters
{
	std::vector<std::string> IncludeAttributes;
	std::vector<std::string> ExcludeAttributes;
	std::unordered_map<std::string, bool> ExtensionFilters;

	Filters();
};