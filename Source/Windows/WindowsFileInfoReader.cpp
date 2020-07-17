#include "../Windows/WindowsFileInfoReader.h"
#include "WindowsUtils.h"

#include <algorithm>


bool WindowsFileInfoReader::EnumDir(const std::string& folderName, std::vector<FileInfo>& outFiles, const InspectorFilters& filters)
{
	WIN32_FIND_DATA fileData{ 0 };
	m_CurrentPath = folderName + "\\*";
	m_IsCurrentEntryDir = true;
	BOOL foundFile = false;

	DWORD includeAttributeFilters;
	DWORD excludeAttributeFilters;
	ParseAttributes(filters, includeAttributeFilters, excludeAttributeFilters);

	do
	{
		if (m_IsCurrentEntryDir)
		{
			HANDLE handle = FindFirstFile(m_CurrentPath.c_str(), &fileData);

			if (handle == INVALID_HANDLE_VALUE)
			{
				BacktrackFolderPath();
				m_IsCurrentEntryDir = false;
				continue;
			}

			m_DirHandles.push_back(handle);
			m_IsCurrentEntryDir = false;
		}
		else
		{
			if (!FindNextFile(m_DirHandles.back(), &fileData))
			{
				BacktrackFolderPath();
				if (GetLastError() != ERROR_NO_MORE_FILES)
				{
					CloseHandle(m_DirHandles.back());
				}
				m_DirHandles.pop_back();
				continue;
			}
		}

		if ((strcmp("..", fileData.cFileName) == 0) || (strcmp(".", fileData.cFileName) == 0))
		{
			continue;
		}

		if (((fileData.dwFileAttributes & excludeAttributeFilters) != 0) ||
			((fileData.dwFileAttributes & includeAttributeFilters) == 0))
		{
			continue;
		}

		m_IsCurrentEntryDir = (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
		if (m_IsCurrentEntryDir)
		{
			ExtendFolderPath(fileData.cFileName);
		}
		else
		{
			std::string nameStr = fileData.cFileName;
			auto extStart = nameStr.find_last_of(".");
			if (extStart != std::string::npos)
			{
				std::string ext = nameStr.substr(extStart + 1);
				if (filters.ShouldSkipExtension(ext))
				{
					continue;
				}
			}
		}

		TIME_ZONE_INFORMATION timeZoneInfo{ 0 };
		GetTimeZoneInformation(&timeZoneInfo);

		LARGE_INTEGER li;
		li.LowPart = fileData.nFileSizeLow;
		li.HighPart = fileData.nFileSizeHigh;

		FileInfo info;
		outFiles.emplace_back(fileData.cFileName
			, li.QuadPart
			, FileTimeToTimeInfo(&fileData.ftCreationTime, &timeZoneInfo)
			, FileTimeToTimeInfo(&fileData.ftLastWriteTime, &timeZoneInfo)
			, static_cast<int>(m_DirHandles.size())
			, m_IsCurrentEntryDir);

	} while (!m_DirHandles.empty());

	return GetLastError() == ERROR_NO_MORE_FILES;
}

TimeInfo WindowsFileInfoReader::FileTimeToTimeInfo(PFILETIME fileTime, PTIME_ZONE_INFORMATION timeZoneInfo)
{
	SYSTEMTIME utcSystemTime{ 0 };
	SYSTEMTIME localSystemTime{ 0 };

	FileTimeToSystemTime(fileTime, &utcSystemTime);
	SystemTimeToTzSpecificLocalTime(timeZoneInfo, &utcSystemTime, &localSystemTime);

	TimeInfo outTimeInfo;
	outTimeInfo.Day = localSystemTime.wDay;
	outTimeInfo.Month = localSystemTime.wMonth;
	outTimeInfo.Year = localSystemTime.wYear;
	outTimeInfo.Hours = localSystemTime.wHour;
	outTimeInfo.Minutes = localSystemTime.wMinute;
	return outTimeInfo;
}

void WindowsFileInfoReader::ExtendFolderPath(const char* folderName)
{
	m_CurrentPath = m_CurrentPath.substr(0, m_CurrentPath.length() - 1) + folderName + "\\*";
}

void WindowsFileInfoReader::BacktrackFolderPath()
{
	m_CurrentPath = m_CurrentPath.substr(0, m_CurrentPath.length() - 2);
	m_CurrentPath = m_CurrentPath.substr(0, m_CurrentPath.find_last_of("\\")) + "\\*";
}

FileInfoReader* CreateFileInfoReader()
{
	return new WindowsFileInfoReader();
}