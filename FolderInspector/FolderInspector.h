#pragma once

#include "FileInfoReader.h"
#include "FileInfoWriter.h"

#include <vector>

class FolderInspector
{
public:
	FolderInspector()
		: m_FileInfoReader(nullptr)
		, m_FileInfoWriter(nullptr)
	{
	}

	FolderInspector(FileInfoReader* reader, FileInfoWriter* writer)
		: m_FileInfoReader(reader)
		, m_FileInfoWriter(writer)
	{
	}

	void InspectFolder(const std::string& name)
	{
		std::vector<FileInfo> files;
		m_FileInfoReader->ReadFileInfo(name, files);
		m_FileInfoWriter->WriteFileInfo(files);
	}

private:
	FileInfoReader* m_FileInfoReader;
	FileInfoWriter* m_FileInfoWriter;

};