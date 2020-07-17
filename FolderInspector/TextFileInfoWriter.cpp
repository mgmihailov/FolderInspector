#include <algorithm>
#include <iomanip>

#include "TextFileInfoWriter.h"

const size_t LINE_LENGTH_WO_FILENAME = 59;

TextFileInfoWriter::TextFileInfoWriter(const std::string& outputDir)
: m_OutputDir(outputDir)
, m_MaxLineLength(0)
, m_MaxFileNameLength(0)
{
	std::string outputFile = m_OutputDir + "output.txt";
	m_OutputStream.open(outputFile, std::ios::trunc);
}

void TextFileInfoWriter::WriteFileInfo(const std::vector<FileInfo>& files, const InspectorFilters& filters)
{
	long long totalBytes = 0;
	long totalFolders = 0;
	long totalFiles = 0;
	std::for_each(files.begin(), files.end(), [&](const FileInfo& first)
		{
			size_t currentFileNameLength = first.FileName.length() + first.Level * (size_t)INDENT_SPACES;
			if (currentFileNameLength > m_MaxFileNameLength)
			{
				m_MaxFileNameLength = currentFileNameLength;
			}

			size_t currentMaxLineLength = currentFileNameLength + LINE_LENGTH_WO_FILENAME;
			if (currentMaxLineLength > m_MaxLineLength)
			{
				m_MaxLineLength = currentMaxLineLength;
			}

			totalBytes += first.FileSize;
			totalFolders += first.IsDir;
			totalFiles += !first.IsDir;
		}
	);
	char* buffer = new char[m_MaxLineLength];
	std::for_each(files.begin(), files.end(), [&](const FileInfo& info)
		{
			int fileNameWidth = info.Level ? int(m_MaxFileNameLength - info.Level * (size_t)INDENT_SPACES) : 0;
			FormatString(buffer, m_MaxLineLength, "%-s%-*s | %.*llu KB | %02u-%02u-%4u %02u:%02u | %02u-%02u-%4u %02u:%02u |"
				, std::string(info.Level * (size_t)INDENT_SPACES, ' ').c_str(), fileNameWidth, info.FileName.c_str()
				, 12, static_cast<unsigned long long>(ceil(info.FileSize / 1024.0))
				, info.DateCreated.Day
				, info.DateCreated.Month
				, info.DateCreated.Year
				, info.DateCreated.Hours
				, info.DateCreated.Minutes
				, info.DateLastModified.Day
				, info.DateLastModified.Month
				, info.DateLastModified.Year
				, info.DateLastModified.Hours
				, info.DateLastModified.Minutes);
			m_OutputStream << buffer << std::endl;
		}
	);
	delete[] buffer;

	m_OutputStream << std::endl << "Total bytes: " << totalBytes << " bytes" << std::endl;
	m_OutputStream << "Total folders: " << totalFolders << " folders" << std::endl;
	m_OutputStream << "Total files: " << totalFiles << " files" << std::endl;
}