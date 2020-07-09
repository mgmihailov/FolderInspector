#include "FolderInspector.h"

#include "FileInfoReader.h"
#include "FileInfoWriter.h"

// TODO: Add an option for the type of writer to create
#include "TextFileInfoWriter.h"

#define INITIAL_ENTRIES_COUNT 200000

FolderInspector::FolderInspector()
	: m_FileInfoReader(nullptr)
	, m_FileInfoWriter(nullptr)
{
}

FolderInspector::FolderInspector(InspectorOptions options)
	: m_FileInfoReader(CreateFileInfoReader())
	, m_FileInfoWriter(new TextFileInfoWriter(options.OutputDir))
{
}

void FolderInspector::InspectFolder(const std::string& folderName)
{
	Filters defaultFilters;
	InspectFolder(folderName, defaultFilters);
}

void FolderInspector::InspectFolder(const std::string& folderName, const Filters& filters)
{
	std::vector<FileInfo> files;
	files.reserve(INITIAL_ENTRIES_COUNT);
	if (m_FileInfoReader->EnumDir(folderName, files, filters))
	{
		m_FileInfoWriter->WriteFileInfo(files, filters);
	}
}