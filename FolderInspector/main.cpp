#include <iostream>

#include "WindowsFileInfoReader.h"
#include "TextFileInfoWriter.h"
#include "FolderInspector.h"

int main(int argc, char** argv)
{
	mtr_init("trace.json");

	FolderInspector folderInspector(new WindowsFileInfoReader(), new TextFileInfoWriter("D:\\"));
	//folderInspector.InspectFolder("D:\\Games"); // 38156 entries
	folderInspector.InspectFolder("C:");
	//folderInspector.InspectFolder("D:\\folder_inspector_test");

	mtr_shutdown();

	return 0;
}