#pragma once

#include <string>

class FileInfoReader;
class FileInfoWriter;

class FolderInspector
{
public:
	FolderInspector();
	FolderInspector(FileInfoReader* reader, FileInfoWriter* writer);

	void InspectFolder(const std::string& name);

private:
	FileInfoReader* m_FileInfoReader;
	FileInfoWriter* m_FileInfoWriter;

};