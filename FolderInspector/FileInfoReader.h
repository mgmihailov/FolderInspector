#pragma once

#include "Utils.h"

#include "minitrace.h"


class FileInfoReader
{
public:
	virtual bool EnumDir(const std::string& folderName, std::vector<FileInfo>& outFiles, const Filters& filters) = 0;
};
