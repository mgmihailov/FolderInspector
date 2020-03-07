#pragma once

#include "FileInfoWriter.h"

#include <sstream>

class TextFileInfoWriter : public FileInfoWriter
{
public:
	TextFileInfoWriter(const char* outputDir)
		: m_OutputDir(outputDir)
	{
	}

	void WriteFileInfo(const std::vector<FileInfo>& files);

private:
	std::string m_OutputDir;
};