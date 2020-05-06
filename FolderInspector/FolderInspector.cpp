#include "FolderInspector.h"

#include "FileInfoReader.h"
#include "FileInfoWriter.h"

FolderInspector::FolderInspector()
	: m_FileInfoReader(nullptr)
	, m_FileInfoWriter(nullptr)
{
}

FolderInspector::FolderInspector(FileInfoReader* reader, FileInfoWriter* writer)
	: m_FileInfoReader(reader)
	, m_FileInfoWriter(writer)
{
}

void FolderInspector::InspectFolder(const std::string& folderName)
{
	std::vector<FileInfo> files;
	files.reserve(900000);
	if (m_FileInfoReader->EnumDir(folderName, files))
	{
		m_FileInfoWriter->WriteFileInfo(files);
	}
}