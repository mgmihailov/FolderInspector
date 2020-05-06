#pragma once

#include <fstream>
#include <sstream>

#include "FileInfoWriter.h"

constexpr int INDENT_SPACES = 2;

class TextFileInfoWriter : public FileInfoWriter
{
public:
	TextFileInfoWriter(const char* outputDir);

	void WriteFileInfo(const std::vector<FileInfo>& files);

private:
	std::string m_OutputDir;
	std::ofstream m_OutputStream;

	int m_MaxLineLength;
	int m_MaxFileNameLength;
};