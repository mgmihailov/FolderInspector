#include <iostream>

#include "WindowsFileInfoReader.h"
#include "TextFileInfoWriter.h"
#include "FolderInspector.h"

int main(int argc, char** argv)
{
	mtr_init("trace.json");

	FolderInspector folderInspector(new WindowsFileInfoReader(), new TextFileInfoWriter("D:\\"));
	folderInspector.InspectFolder("D:\\Movies");

	mtr_shutdown();

	return 0;
}