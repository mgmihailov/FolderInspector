#include <stdarg.h>

#include "../Utils.h"
#include "LinuxUtils.h"

void ParseAttributes(const InspectorFilters& filters, mode_t& outIncludeAttribs, mode_t& outExcludeAttribs)
{
}

void FormatString(char* buffer, size_t bufferLength, const char* format, ...)
{
    (void)bufferLength;
    va_list args;
    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);
}