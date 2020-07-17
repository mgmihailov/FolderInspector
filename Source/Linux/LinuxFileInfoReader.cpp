#include "LinuxFileInfoReader.h"

bool LinuxFileInfoReader::EnumDir(const std::string& folderName, std::vector<FileInfo>& outFiles, const InspectorFilters& filters)
{
  return true;
}

FileInfoReader* CreateFileInfoReader()
{
	return new LinuxFileInfoReader();
}