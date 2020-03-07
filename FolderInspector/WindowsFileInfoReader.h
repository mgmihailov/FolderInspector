#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "FileInfoReader.h"

class WindowsFileInfoReader : public FileInfoReader
{
public:
	void ReadFileInfo(const std::string& folderName, std::vector<FileInfo>& outFiles);

private:
	TimeInfo FileTimeToTimeInfo(PFILETIME fileTime, PTIME_ZONE_INFORMATION timeZoneInfo);

};