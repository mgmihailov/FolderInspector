#include <iostream>

#include "WindowsFileInfoReader.h"
#include "TextFileInfoWriter.h"
#include "FolderInspector.h"

int main(int argc, char** argv)
{
	FolderInspector folderInspector(new WindowsFileInfoReader(), new TextFileInfoWriter("D:\\"));
	folderInspector.InspectFolder("D:\\Movies");

	return 0;
}