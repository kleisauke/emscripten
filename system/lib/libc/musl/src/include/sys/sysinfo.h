#ifndef SYS_SYSINFO_H
#define SYS_SYSINFO_H

#ifdef __EMSCRIPTEN__
#include "../../../../../../include/libc/sys/sysinfo.h"
#else
#include "../../../include/sys/sysinfo.h"
#endif
#include <features.h>

hidden int __lsysinfo(struct sysinfo *);

#endif
