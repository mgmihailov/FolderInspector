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
	bool IsDir;

	FileInfo();

	FileInfo(const char* fileName
		, unsigned long long fileSize
		, TimeInfo dateCreated
		, TimeInfo dateLastModified
		, int level
		, bool isDir);
};

class Filters
{
public:
	Filters();

	bool ShouldSkipExtension(const std::string& ext) const;
	bool AreIncludeAttribsEmpty() const;
	bool AreExcludeAttribsEmpty() const;
	const std::vector<std::string>& GetIncludeAttribs() const;
	const std::vector<std::string>& GetExcludeAttribs() const;

	void AddAttribsToInclude(const std::vector<std::string>& includeAttribs);
	void AddAttribsToExclude(const std::vector<std::string>& excludeAttribs);
	void AddExtensionsToInclude(const std::vector<std::string>& includeExtensions);
	void AddExtensionsToExclude(const std::vector<std::string>& excludeExtensions);

private:
	std::vector<std::string> IncludeAttributes;
	std::vector<std::string> ExcludeAttributes;
	std::unordered_map<std::string, bool> IncludeExtensions;
	std::unordered_map<std::string, bool> ExcludeExtensions;

};