#include <iostream>

#include "WindowsFileInfoReader.h"
#include "TextFileInfoWriter.h"
#include "FolderInspector.h"

int main(int argc, char** argv)
{
	mtr_init("trace.json");

	FolderInspector folderInspector(new WindowsFileInfoReader(), new TextFileInfoWriter("D:\\"));
	Filters filters;

	filters.IncludeAttributes.push_back("dir");
	filters.IncludeAttributes.push_back("sys");
	folderInspector.InspectFolder("D:\\folder_inspector_test", filters);

	mtr_shutdown();

	return 0;
}