#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

#include <Windows.h>

std::unordered_map<std::string, DWORD> ArgsToFlags = {
	{"arch", FILE_ATTRIBUTE_ARCHIVE},
	{"compr", FILE_ATTRIBUTE_COMPRESSED},
	{"dir", FILE_ATTRIBUTE_DIRECTORY},
	{"enc", FILE_ATTRIBUTE_ENCRYPTED},
	{"hidden", FILE_ATTRIBUTE_HIDDEN},
	{"intstr", FILE_ATTRIBUTE_INTEGRITY_STREAM},
	{"reg", FILE_ATTRIBUTE_NORMAL},
	{"notidx", FILE_ATTRIBUTE_NOT_CONTENT_INDEXED},
	{"offln", FILE_ATTRIBUTE_OFFLINE},
	{"uchg", FILE_ATTRIBUTE_READONLY},
	{"distr", FILE_ATTRIBUTE_RECALL_ON_DATA_ACCESS},
	{"notlcl", FILE_ATTRIBUTE_RECALL_ON_OPEN},
	{"lnk", FILE_ATTRIBUTE_REPARSE_POINT},
	{"sparse", FILE_ATTRIBUTE_SPARSE_FILE},
	{"sys", FILE_ATTRIBUTE_SYSTEM},
	{"temp", FILE_ATTRIBUTE_TEMPORARY}
};

DWORD DefaultIncludeAttributes = ArgsToFlags["arch"] | ArgsToFlags["reg"]
	| ArgsToFlags["notidx"] | ArgsToFlags["uchg"] | ArgsToFlags["dir"];

DWORD DefaultExcludeAttributes = ArgsToFlags["compr"] | ArgsToFlags["enc"]
	| ArgsToFlags["hidden"] | ArgsToFlags["intstr"]
	| ArgsToFlags["offln"] | ArgsToFlags["distr"] | ArgsToFlags["notlcl"]
	| ArgsToFlags["lnk"] | ArgsToFlags["sparse"] | ArgsToFlags["sys"]
	| ArgsToFlags["temp"];

DWORD AllFileAttributes = DefaultIncludeAttributes | DefaultExcludeAttributes;

void ParseAttributes(const Filters& filters, DWORD& outIncludeAttribs, DWORD& outExcludeAttribs)
{
	outIncludeAttribs = 0;
	outExcludeAttribs = 0;

	if ((filters.IncludeAttributes.empty() && filters.ExcludeAttributes.empty()))
	{
		outIncludeAttribs = DefaultIncludeAttributes;
		outExcludeAttribs = DefaultExcludeAttributes;
	}
	else
	{
		for (const auto& attr : filters.IncludeAttributes)
		{
			auto it = ArgsToFlags.find(attr);
			if (it != ArgsToFlags.end())
			{
				outIncludeAttribs |= ArgsToFlags[attr];
			}
			else
			{
				std::cout << "Attribute \"" << attr << "\" to be included is either invalid or not supported for this platform!" << std::endl;
			}
		}

		for (const auto& attr : filters.ExcludeAttributes)
		{
			auto it = ArgsToFlags.find(attr);
			if (it != ArgsToFlags.end())
			{
				outExcludeAttribs |= ArgsToFlags[attr];
			}
			else
			{
				std::cout << "Attribute \"" << attr << "\" to be excluded is either invalid or not supported for this platform!" << std::endl;
			}
		}

		DWORD duplicateAttribsExcludeMask = outIncludeAttribs & outExcludeAttribs;
		outIncludeAttribs &= ~outExcludeAttribs;
		outExcludeAttribs &= ~duplicateAttribsExcludeMask;

		if (outIncludeAttribs == 0)
		{
			if (outExcludeAttribs != 0)
			{
				outIncludeAttribs = AllFileAttributes & ~outExcludeAttribs;
			}
			else
			{
				outIncludeAttribs = DefaultIncludeAttributes;
				outExcludeAttribs = DefaultExcludeAttributes;
			}
		}
	}
}