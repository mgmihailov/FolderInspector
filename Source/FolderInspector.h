#pragma once

#include <string>
#include <vector>

#include "Utils.h"

class FileInfoReader;
class FileInfoWriter;


struct InspectorOptions
{
	std::string DirectoryToInspect;
	InspectorFilters Filters;
	std::string OutputDir;
};

class FolderInspector
{
public:
	FolderInspector();
	FolderInspector(InspectorOptions options);

	void InspectFolder(const std::string& name);
	void InspectFolder(const std::string& name, const InspectorFilters& filters);

private:
	FileInfoReader* m_FileInfoReader;
	FileInfoWriter* m_FileInfoWriter;

};

FileInfoReader* CreateFileInfoReader();