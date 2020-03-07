#pragma once

#include "FileInfo.h"

#include <vector>

class FileInfoWriter
{
public:
	virtual void WriteFileInfo(const std::vector<FileInfo>& files) = 0;
};