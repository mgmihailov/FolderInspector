#pragma once

#include <string>
#include <unordered_map>

#include <sys/stat.h>

#include "../Utils.h"


const std::string ATTR_REG = { "reg" };
const std::string ATTR_DIR = { "dir" };
const std::string ATTR_CHR = { "chr" };
const std::string ATTR_BLK = { "blk" };
const std::string ATTR_FIFO = { "fifo" };
const std::string ATTR_LNK = { "lnk" };
const std::string ATTR_SOCK = { "sock" };
const std::string ATTR_UID = { "uid" };
const std::string ATTR_GID = { "gid" };
const std::string ATTR_VTX = { "vtx" };
const std::string ATTR_RUSR = { "rusr" };
const std::string ATTR_WUSR = { "wusr" };
const std::string ATTR_XUSR = { "xusr" };
const std::string ATTR_RGRP = { "rgrp" };
const std::string ATTR_WGRP = { "wgrp" };
const std::string ATTR_XGRP = { "xgrp" };
const std::string ATTR_ROTHR = { "rothr" };
const std::string ATTR_WOTHR = { "wothr" };
const std::string ATTR_XOTHR = { "xothr" };

const std::unordered_map<std::string, mode_t> AttrArgsToFlags = {
	{ ATTR_REG, S_IFREG },
	{ ATTR_DIR, S_IFDIR },
	{ ATTR_CHR, S_IFCHR },
	{ ATTR_BLK, S_IFBLK },
	{ ATTR_FIFO, S_IFIFO },
	{ ATTR_LNK, S_IFLNK },
	{ ATTR_SOCK, S_IFSOCK },
	{ ATTR_UID, S_ISUID },
	{ ATTR_GID, S_ISGID },
	{ ATTR_VTX, S_ISVTX },
	{ ATTR_RUSR, S_IRUSR },
	{ ATTR_WUSR, S_IWUSR },
	{ ATTR_XUSR, S_IXUSR },
	{ ATTR_RGRP, S_IRGRP },
	{ ATTR_WGRP, S_IWGRP },
	{ ATTR_XGRP, S_IXGRP },
	{ ATTR_ROTHR, S_IROTH },
	{ ATTR_WOTHR, S_IWOTH },
	{ ATTR_XOTHR, S_IXOTH },
};

const mode_t DefaultIncludeAttributes = 0;

const mode_t DefaultExcludeAttributes = 0;

const mode_t AllFileAttributes = 0;

void ParseAttributes(const InspectorFilters& filters, std::unordered_map<unsigned int, bool>& outInclExclAttribs);

