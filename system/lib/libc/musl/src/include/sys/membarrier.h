#ifndef SYS_MEMBARRIER_H
#define SYS_MEMBARRIER_H

#ifdef __EMSCRIPTEN__
#include "../../../../../../include/libc/sys/membarrier.h"
#else
#include "../../../include/sys/membarrier.h"
#endif
#include <features.h>

hidden int __membarrier(int, int);

#endif
