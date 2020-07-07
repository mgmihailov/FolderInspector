#include <iostream>

#include "Windows/WindowsFileInfoReader.h"
#include "TextFileInfoWriter.h"
#include "FolderInspector.h"

int main(int argc, char** argv)
{
	mtr_init("trace.json");

	FolderInspector folderInspector(new WindowsFileInfoReader(), new TextFileInfoWriter("D:\\"));
	Filters filters;

	std::vector<std::string> extsToExclude{"mp3", "png"};
	filters.AddExtensionsToExclude(extsToExclude);
	folderInspector.InspectFolder("D:\\folder_inspector_test", filters);

	mtr_shutdown();

	return 0;
}