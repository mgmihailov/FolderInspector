#include <iostream>
#include <stdarg.h>

#include "../Utils.h"
#include "LinuxUtils.h"

void ParseAttributes(const InspectorFilters& filters, mode_t& outIncludeAttribs, mode_t& outExcludeAttribs)
{
	for (const auto& attr : filters.GetIncludeAttribs())
	{
		auto it = AttrArgsToFlags.find(attr);
		if (it != AttrArgsToFlags.end())
		{
			outIncludeAttribs |= it->second;
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
			outExcludeAttribs |= it->second;
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

