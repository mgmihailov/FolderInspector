#pragma once

#include "Utils.h"

#include "minitrace.h"

#include <vector>

class FileInfoReader
{
public:
	virtual bool EnumDir(const std::string& folderName, std::vector<FileInfo>& outFiles) = 0;
};
