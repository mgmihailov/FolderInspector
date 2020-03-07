#include <iostream>

#include "WindowsFileInfoReader.h"

void WindowsFileInfoReader::ReadFileInfo(const std::string& folderName, std::vector<FileInfo>& outFiles)
{
	WIN32_FIND_DATA fileData{ 0 };
	HANDLE searchHandle = FindFirstFile(folderName.c_str(), &fileData);
	if (searchHandle == INVALID_HANDLE_VALUE)
	{
		return;
	}
	std::string wildcard = folderName + "/*";
	searchHandle = FindFirstFile(wildcard.c_str(), &fileData);
	BOOL foundNextFile = 0;
	while (searchHandle != INVALID_HANDLE_VALUE)
	{
		foundNextFile = FindNextFile(searchHandle, &fileData);
		if (foundNextFile)
		{
			if ((fileData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) == 0 &&
				strcmp(fileData.cFileName, "..") != 0)
			{
				TIME_ZONE_INFORMATION timeZoneInfo{ 0 };
				GetTimeZoneInformation(&timeZoneInfo);
				TimeInfo dateCreated = FileTimeToTimeInfo(&fileData.ftCreationTime, &timeZoneInfo);
				TimeInfo dateLastModified = FileTimeToTimeInfo(&fileData.ftLastWriteTime, &timeZoneInfo);

				auto fileSize = (fileData.nFileSizeHigh * (static_cast<DWORD64>(MAXDWORD) + 1)) + fileData.nFileSizeLow;

				outFiles.push_back(FileInfo(fileData.cFileName, fileSize / 1024, dateCreated, dateLastModified));
				bool isDirectory = (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
				if (!isDirectory)
				{
					
				}
			}
		}
		else
		{
			FindClose(searchHandle);
			break;
		}
	}

	return;
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