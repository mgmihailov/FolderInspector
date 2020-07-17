#pragma once

const std::unordered_map<std::string, mode_t> AttrArgsToFlags;

const mode_t DefaultIncludeAttributes = 0;

const mode_t DefaultExcludeAttributes = 0;

const mode_t AllFileAttributes = 0;

void ParseAttributes(const InspectorFilters& filters, mode_t& outIncludeAttribs, mode_t& outExcludeAttribs);