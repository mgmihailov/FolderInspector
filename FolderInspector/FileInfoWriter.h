#pragma once

#include "FileInfo.h"

#include "minitrace.h"

#include <vector>

class FileInfoWriter
{
public:
	virtual void WriteFileInfo(const std::vector<FileInfo>& files) = 0;
};