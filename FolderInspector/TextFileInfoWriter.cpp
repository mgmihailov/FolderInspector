#include "TextFileInfoWriter.h"

#include <algorithm>
#include <iomanip>
#include <fstream>

void TextFileInfoWriter::WriteFileInfo(const std::vector<FileInfo>& files)
{
	size_t maxWidth = std::max_element(files.begin(), files.end(), [](const FileInfo& first, const FileInfo& second)
		{
			return first.FileName.size() < second.FileName.size();
		})->FileName.size();

	std::string outputFile = m_OutputDir + "output.txt";
	std::ofstream output(outputFile, std::ios::trunc);
	std::for_each(files.begin(), files.end(), [&output, &maxWidth](const FileInfo& info)
		{
			output.fill(' ');
			output << std::setw(maxWidth) << std::left << info.FileName << " | ";
			output.fill('0');
			output << std::internal;
			output << std::setw(12) << info.FileSize << " KB | ";
			output << std::setw(2) << info.DateCreated.Day << "-";
			output << std::setw(2) << info.DateCreated.Month << "-";
			output << std::setw(4) << info.DateCreated.Year << " ";
			output << std::setw(2) << info.DateCreated.Hours << ":";
			output << std::setw(2) << info.DateCreated.Minutes << " | ";
			output << std::setw(2) << info.DateLastModified.Day << "-";
			output << std::setw(2) << info.DateLastModified.Month << "-";
			output << std::setw(4) << info.DateLastModified.Year << " ";
			output << std::setw(2) << info.DateCreated.Hours << ":";
			output << std::setw(2) << info.DateCreated.Minutes << " | " << std::endl;
		});

	output.close();
}