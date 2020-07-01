#pragma once

#include "Utils.h"

#include "minitrace.h"

#include <vector>

class FileInfoWriter
{
public:
	virtual void WriteFileInfo(const std::vector<FileInfo>& files, const Filters& filters) = 0;
};