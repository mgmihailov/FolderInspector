#pragma once

#include "../FileInfoReader.h"

class LinuxFileInfoReader : public FileInfoReader
{
public:
	bool EnumDir(const std::string& folderName, std::vector<FileInfo>& outFiles, const Filters& filters);
};