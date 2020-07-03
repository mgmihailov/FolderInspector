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
	, int level
	, bool isDir)
		: FileName(fileName)
		, FileSize(fileSize)
		, DateCreated(dateCreated)
		, DateLastModified(dateLastModified)
		, Level(level)
		, IsDir(isDir)
{}

Filters::Filters()
{}

bool Filters::ShouldSkipExtension(const std::string& ext) const
{
	auto itInclude = IncludeExtensions.find(ext);
	auto itExclude = ExcludeExtensions.find(ext);
	return ((!IncludeExtensions.empty() && itInclude == IncludeExtensions.end()) ||
				(itInclude != IncludeExtensions.end() && !itInclude->second)) ||
			(itExclude != ExcludeExtensions.end() && itExclude->second);
}

bool Filters::AreIncludeAttribsEmpty() const
{
	return IncludeAttributes.empty();
}

bool Filters::AreExcludeAttribsEmpty() const
{
	return ExcludeAttributes.empty();
}

const std::vector<std::string>& Filters::GetIncludeAttribs() const
{
	return IncludeAttributes;
}

const std::vector<std::string>& Filters::GetExcludeAttribs() const
{
	return ExcludeAttributes;
}

void Filters::AddAttribsToInclude(const std::vector<std::string>& includeAttribs)
{
	for (auto attr : includeAttribs)
	{
		IncludeAttributes.push_back(attr);
	}
}

void Filters::AddAttribsToExclude(const std::vector<std::string>& excludeAttribs)
{
	for (auto attr : excludeAttribs)
	{
		ExcludeAttributes.push_back(attr);
	}
}

void Filters::AddExtensionsToInclude(const std::vector<std::string>& includeExtensions)
{
	for (auto ext : includeExtensions)
	{
		IncludeExtensions[ext] = true;
	}
}

void Filters::AddExtensionsToExclude(const std::vector<std::string>& excludeExtensions)
{
	for (auto ext : excludeExtensions)
	{
		ExcludeExtensions[ext] = true;
	}
}