#pragma once

#include "FileInfo.h"

#include <vector>

class FileInfoReader
{
public:
	virtual void ReadFileInfo(const std::string& folderName, std::vector<FileInfo>& outFiles) = 0;
};