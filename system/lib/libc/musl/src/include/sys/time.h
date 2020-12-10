#ifndef SYS_TIME_H
#define SYS_TIME_H

#ifdef __EMSCRIPTEN__
#include "../../../../../../include/libc/sys/time.h"
#else
#include "../../../include/sys/time.h"
#endif

hidden int __futimesat(int, const char *, const struct timeval [2]);

#endif
