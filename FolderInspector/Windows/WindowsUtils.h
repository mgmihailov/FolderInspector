#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

#include "../Utils.h"

const std::string ATTR_ARCH = { "arch" };
const std::string ATTR_COMPR = { "compr" };
const std::string ATTR_DIR = { "dir" };
const std::string ATTR_ENC = { "enc" };
const std::string ATTR_HIDDEN = { "hidden" };
const std::string ATTR_INTSTR = { "intstr" };
const std::string ATTR_REG = { "reg" };
const std::string ATTR_NOTIDX = { "notidx" };
const std::string ATTR_OFFLN = { "offln" };
const std::string ATTR_UCHG = { "uchg" };
const std::string ATTR_DISTR = { "distr" };
const std::string ATTR_NOTCTL = { "notlcl" };
const std::string ATTR_LNK = { "lnk" };
const std::string ATTR_SPARSE = { "sparse" };
const std::string ATTR_SYS = { "sys" };
const std::string ATTR_TEMP = { "temp" };

const std::unordered_map<std::string, DWORD> AttrArgsToFlags = {
	{ATTR_ARCH, FILE_ATTRIBUTE_ARCHIVE},
	{ATTR_COMPR, FILE_ATTRIBUTE_COMPRESSED},
	{ATTR_DIR, FILE_ATTRIBUTE_DIRECTORY},
	{ATTR_ENC, FILE_ATTRIBUTE_ENCRYPTED},
	{ATTR_HIDDEN, FILE_ATTRIBUTE_HIDDEN},
	{ATTR_INTSTR, FILE_ATTRIBUTE_INTEGRITY_STREAM},
	{ATTR_REG, FILE_ATTRIBUTE_NORMAL},
	{ATTR_NOTIDX, FILE_ATTRIBUTE_NOT_CONTENT_INDEXED},
	{ATTR_OFFLN, FILE_ATTRIBUTE_OFFLINE},
	{ATTR_UCHG, FILE_ATTRIBUTE_READONLY},
	{ATTR_DISTR, FILE_ATTRIBUTE_RECALL_ON_DATA_ACCESS},
	{ATTR_NOTCTL, FILE_ATTRIBUTE_RECALL_ON_OPEN},
	{ATTR_LNK, FILE_ATTRIBUTE_REPARSE_POINT},
	{ATTR_SPARSE, FILE_ATTRIBUTE_SPARSE_FILE},
	{ATTR_SYS, FILE_ATTRIBUTE_SYSTEM},
	{ATTR_TEMP, FILE_ATTRIBUTE_TEMPORARY}
};

const DWORD DefaultIncludeAttributes = AttrArgsToFlags.at(ATTR_ARCH) | AttrArgsToFlags.at(ATTR_REG)
| AttrArgsToFlags.at(ATTR_NOTIDX) | AttrArgsToFlags.at(ATTR_UCHG) | AttrArgsToFlags.at(ATTR_DIR);

const DWORD DefaultExcludeAttributes = AttrArgsToFlags.at(ATTR_COMPR) | AttrArgsToFlags.at(ATTR_ENC)
| AttrArgsToFlags.at(ATTR_HIDDEN) | AttrArgsToFlags.at(ATTR_INTSTR)
| AttrArgsToFlags.at(ATTR_OFFLN) | AttrArgsToFlags.at(ATTR_DISTR) | AttrArgsToFlags.at(ATTR_NOTCTL)
| AttrArgsToFlags.at(ATTR_LNK) | AttrArgsToFlags.at(ATTR_SPARSE) | AttrArgsToFlags.at(ATTR_SYS)
| AttrArgsToFlags.at(ATTR_TEMP);

const DWORD AllFileAttributes = DefaultIncludeAttributes | DefaultExcludeAttributes;

void ParseAttributes(const Filters& filters, DWORD& outIncludeAttribs, DWORD& outExcludeAttribs);