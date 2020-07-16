#include <iostream>

#include "Windows/WindowsUtils.h"
#include "Windows/WindowsFileInfoReader.h"
#include "TextFileInfoWriter.h"
#include "FolderInspector.h"

const char ARG_DIRECTORY[]          = { "--dir" };
const char ARG_INCLUDE_ATTRIBUTES[] = { "--include-attrs" };
const char ARG_EXCLUDE_ATTRIBUTES[] = { "--exclude-attrs" };
const char ARG_INCLUDE_EXTENSIONS[] = { "--include-exts" };
const char ARG_EXCLUDE_EXTENSIONS[] = { "--exclude-exts" };
const char ARG_OUTPUT_DIRECTORY[]   = { "--output-dir" };

void PrintUsage()
{
	std::cout << "Usage: FolderInspector.exe --dir=<directory_to_inspect> [--include-attrs=<attr1>,<attr2>,...,<attrN>] "\
		"[--exclude-attrs=<attr1>,<attr2>,...,<attrN>] [--include-exts=<ext1>,<ext2>,...,<extN>] "\
		"[--exclude-exts=<ext1>,<ext2>,...,<extN>] [--output-dir=<directory>]" << std::endl << std::endl;

	//TODO: Add a description of what each attribute means
	std::cout << "Available attributes:" << std::endl;
	for (const auto& attr : AttrArgsToFlags)
	{
		std::cout << attr.first <<std::endl;
	}
	std::cout << std::endl;
}

void ParseListOfValues(char* args, std::vector<std::string>& outVals)
{
	std::stringstream values(args);
	std::string value;
	while (std::getline(values, value, ','))
	{
		outVals.push_back(value);
	}
}

void ParseArguments(int countArgs, char** args, InspectorOptions& outOptions)
{
	if ((countArgs == 2 && strcmp(args[1], "--help") == 0) ||
		countArgs < 2)
	{
		PrintUsage();
		return;
	}

	for (int i = 1; i < countArgs; ++i)
	{
		if (strncmp(args[i], ARG_DIRECTORY, sizeof(ARG_DIRECTORY) - 1) == 0)
		{
			outOptions.DirectoryToInspect = strchr(args[i], '=') + 1;
		}
		else if (strncmp(args[i], ARG_INCLUDE_ATTRIBUTES, sizeof(ARG_INCLUDE_ATTRIBUTES) - 1) == 0)
		{
			std::vector<std::string> attribs;
			ParseListOfValues(strchr(args[i], '=') + 1, attribs);
			outOptions.Filters.AddAttribsToInclude(attribs);
		}
		else if (strncmp(args[i], ARG_EXCLUDE_ATTRIBUTES, sizeof(ARG_EXCLUDE_ATTRIBUTES) - 1) == 0)
		{
			std::vector<std::string> attribs;
			ParseListOfValues(strchr(args[i], '=') + 1, attribs);
			outOptions.Filters.AddAttribsToExclude(attribs);
		}
		else if (strncmp(args[i], ARG_INCLUDE_EXTENSIONS, sizeof(ARG_INCLUDE_EXTENSIONS) - 1) == 0)
		{
			std::vector<std::string> exts;
			ParseListOfValues(strchr(args[i], '=') + 1, exts);
			outOptions.Filters.AddExtensionsToInclude(exts);
		}
		else if (strncmp(args[i], ARG_EXCLUDE_EXTENSIONS, sizeof(ARG_EXCLUDE_EXTENSIONS) - 1) == 0)
		{
			std::vector<std::string> exts;
			ParseListOfValues(strchr(args[i], '=') + 1, exts);
			outOptions.Filters.AddExtensionsToExclude(exts);
		}
		else if (strncmp(args[i], ARG_OUTPUT_DIRECTORY, sizeof(ARG_OUTPUT_DIRECTORY) - 1) == 0)
		{
			outOptions.OutputDir = strchr(args[i], '=') + 1;
		}
		else
		{
			std::cout << "Invalid argument: " << args[i] << "!" << std::endl;
			PrintUsage();
		}
	}
}

int main(int argc, char** argv)
{
	mtr_init("trace.json");

	InspectorOptions options;
	ParseArguments(argc, argv, options);

	FolderInspector folderInspector(options);
	folderInspector.InspectFolder(options.DirectoryToInspect, options.Filters);

	mtr_shutdown();

	return 0;
}