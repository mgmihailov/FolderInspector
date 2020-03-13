#include <iostream>

#include "WindowsFileInfoReader.h"

void WindowsFileInfoReader::ReadFileInfo(const std::string& folderName, std::vector<FileInfo>& outFiles)
{
	WIN32_FIND_DATA fileData{ 0 };
	HANDLE currentHandle = FindFirstFile(folderName.c_str(), &fileData);

	if (currentHandle == INVALID_HANDLE_VALUE)
	{
		return;
	}

	std::string wildcard = folderName + "/*";
	std::vector<HANDLE> handleQueue;
	currentHandle = FindFirstFile(wildcard.c_str(), &fileData);
	BOOL foundNextFile = 0;
	while (true)
	{
		if (currentHandle == INVALID_HANDLE_VALUE)
		{
			break;
		}

		foundNextFile = FindNextFile(currentHandle, &fileData);
		if (foundNextFile == 0)
		{
			FindClose(currentHandle);
			if (!handleQueue.empty())
			{
				currentHandle = handleQueue.back();
				handleQueue.pop_back();
				wildcard = wildcard.substr(0, wildcard.find("/*"));
				wildcard = wildcard.substr(0, wildcard.find_last_of("/"));
				continue;
			}
			else
			{
				break;
			}
		}

		if ((fileData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) == 0 &&
			strcmp(fileData.cFileName, "..") != 0)
		{
			TIME_ZONE_INFORMATION timeZoneInfo{ 0 };
			GetTimeZoneInformation(&timeZoneInfo);

			TimeInfo dateCreated = FileTimeToTimeInfo(&fileData.ftCreationTime, &timeZoneInfo);
			TimeInfo dateLastModified = FileTimeToTimeInfo(&fileData.ftLastWriteTime, &timeZoneInfo);
			auto fileSize = (fileData.nFileSizeHigh * (static_cast<DWORD64>(MAXDWORD) + 1)) + fileData.nFileSizeLow;

			outFiles.push_back(FileInfo(fileData.cFileName, fileSize / 1000, dateCreated, dateLastModified));

			if ((fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
			{
				wildcard = wildcard.substr(0, wildcard.find("/*"));
				wildcard = wildcard + "/" + fileData.cFileName + "/*";
				handleQueue.push_back(currentHandle);
				currentHandle = FindFirstFile(wildcard.c_str(), &fileData);
			}
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

