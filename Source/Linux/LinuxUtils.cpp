#include <iostream>
#include <stdarg.h>

#include "LinuxUtils.h"


void ParseAttributes(const InspectorFilters& filters, std::unordered_map<unsigned int, bool>& outInclExclAttribs)
{
	for (const auto& attr : filters.GetIncludeAttribs())
	{
		auto it = AttrArgsToFlags.find(attr);
		if (it != AttrArgsToFlags.end())
		{
			outInclExclAttribs[it->second] = true;
		}
		else
		{
			std::cout << "Attribute \"" << attr << "\" to be included is either invalid or not supported for this platform!" << std::endl;
		}
	}

	for (const auto& attr : filters.GetExcludeAttribs())
	{
		auto it = AttrArgsToFlags.find(attr);
		if (it != AttrArgsToFlags.end())
		{
			if (!outInclExclAttribs.erase(it->second))
			{
				outInclExclAttribs[it->second] = false;
			}
		}
		else
		{
			std::cout << "Attribute \"" << attr << "\" to be excluded is either invalid or not supported for this platform!" << std::endl;
		}
	}
}

void FormatString(char* buffer, size_t bufferLength, const char* format, ...)
{
    (void)bufferLength;
    va_list args;
    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);
}

