#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "FileInfoReader.h"

class WindowsFileInfoReader : public FileInfoReader
{
public:
	bool EnumDir(const std::string& folderName, std::vector<FileInfo>& outFiles, const Filters& filters);

private:
	TimeInfo FileTimeToTimeInfo(PFILETIME fileTime, PTIME_ZONE_INFORMATION timeZoneInfo);
	void ExtendFolderPath(const char* folderName);
	void BacktrackFolderPath();

	bool m_IsCurrentEntryDir;
	std::string m_PreviousPath;
	std::string m_CurrentPath;
	std::vector<HANDLE> m_DirHandles;
};