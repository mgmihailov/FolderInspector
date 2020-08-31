#include <sys/stat.h>

#include <dirent.h>
#include <string.h>
#include <iostream>

#include "LinuxFileInfoReader.h"


bool LinuxFileInfoReader::EnumDir(const std::string& folderName, std::vector<FileInfo>& outFiles, const InspectorFilters& filters)
{
	std::vector<DIR*> dirHandles;
	bool shouldOpenDir = true;
	dirent* entry = nullptr;

	// TODO: Move path sanitazing and validation to a separate function
	std::string dirName = folderName;
	if (dirName.length() != 1 &&
		dirName[dirName.length() - 1] == '/')
	{
		dirName = dirName.substr(0, dirName.length() - 1);
	}
	do
	{
		if (shouldOpenDir)
		{
			shouldOpenDir = false;
			DIR* dir = opendir(dirName.c_str());
			if (!dir)
			{
				std::cout << "Failed to open directory \""
					<< dirName << "\". Got error: "
					<< strerror(errno) << "." << std::endl;
				continue;
			}
			else
			{
				dirHandles.push_back(dir);
			}
		}
		else
		{
			int lastError = errno;
			entry = readdir(dirHandles.back());
			if (!entry)
			{
				if (errno == lastError)
				{
					int res = closedir(dirHandles.back());
					if (res == -1)
					{
						std::cout << "Failed to close directory."\
							" Got error: " << strerror(errno) << "."
							<< std::endl;
					}
					dirHandles.pop_back();
					dirName = dirName.substr(0,
						dirName.find_last_of("/"));
				}
				else
				{
					std::cout << "Failed to read dir entry."\
						"Got error: " << strerror(errno) << "."
						<< std::endl;
				}
				continue;
			}

			if ((strcmp(".", entry->d_name) == 0) ||
				(strcmp("..", entry->d_name) == 0))
			{
				continue;
			}

			struct stat outStat;
			std::string fullName = dirName
				+ (dirName[dirName.length() - 1] == '/'
				? "" : "/") + entry->d_name;
			int res = lstat(fullName.c_str(), &outStat);
			if (res == -1)
			{
				std::cout << "Failed to obtain info for entry \""
					<< fullName.c_str() << "\". Got error: "
					<< strerror(errno) << "." << std::endl;
				continue;
			}

			if ((outStat.st_mode & S_IFMT) == S_IFDIR)
			{
				dirName = dirName
					+ (dirName[dirName.length() - 1] == '/'
					? "" : "/") + entry->d_name;
				shouldOpenDir = true;
				continue;
			}
		}

		std::cout << "entry name: \"" << (entry ? entry->d_name : dirName) << "\"" << std::endl;
	} while(!dirHandles.empty());

	return true;
}

FileInfoReader* CreateFileInfoReader()
{
	return new LinuxFileInfoReader();
}
