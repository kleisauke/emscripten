#ifndef ERRNO_H
#define ERRNO_H

#ifdef __EMSCRIPTEN__
#include "../../../../../include/libc/errno.h"
#else
#include "../../include/errno.h"
#endif

#ifdef __GNUC__
__attribute__((const))
#endif
hidden int *___errno_location(void);

#undef errno
#define errno (*___errno_location())

#endif
