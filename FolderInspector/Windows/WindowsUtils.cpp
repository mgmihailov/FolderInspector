#include "WindowsUtils.h"

void ParseAttributes(const InspectorFilters& filters, DWORD& outIncludeAttribs, DWORD& outExcludeAttribs)
{
	outIncludeAttribs = 0;
	outExcludeAttribs = 0;

	if ((filters.AreIncludeAttribsEmpty() && filters.AreExcludeAttribsEmpty()))
	{
		outIncludeAttribs = DefaultIncludeAttributes;
		outExcludeAttribs = DefaultExcludeAttributes;
	}
	else
	{
		for (const auto& attr : filters.GetIncludeAttribs())
		{
			auto it = AttrArgsToFlags.find(attr);
			if (it != AttrArgsToFlags.end())
			{
				outIncludeAttribs |= AttrArgsToFlags.at(attr);
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
				outExcludeAttribs |= AttrArgsToFlags.at(attr);
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