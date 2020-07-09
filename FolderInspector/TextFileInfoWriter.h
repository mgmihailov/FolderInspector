#pragma once

#include <fstream>
#include <sstream>

#include "FileInfoWriter.h"

constexpr int INDENT_SPACES = 2;

class TextFileInfoWriter : public FileInfoWriter
{
public:
	TextFileInfoWriter(const std::string& outputDir);

	void WriteFileInfo(const std::vector<FileInfo>& files, const Filters& filters);

private:
	std::string m_OutputDir;
	std::ofstream m_OutputStream;

	size_t m_MaxLineLength;
	size_t m_MaxFileNameLength;
};