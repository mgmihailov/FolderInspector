#pragma once

const std::unordered_map<std::string, mode_t> AttrArgsToFlags;

const mode_t DefaultIncludeAttributes;

const mode_t DefaultExcludeAttributes;

const mode_t AllFileAttributes;

void ParseAttributes(const Filters& filters, mode_t& outIncludeAttribs, mode_t& outExcludeAttribs);