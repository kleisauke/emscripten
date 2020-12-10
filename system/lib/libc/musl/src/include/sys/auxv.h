#ifndef SYS_AUXV_H
#define SYS_AUXV_H

#ifdef __EMSCRIPTEN__
#include "../../../../../../include/libc/sys/auxv.h"
#else
#include "../../../include/sys/auxv.h"
#endif

#include <features.h>

hidden unsigned long __getauxval(unsigned long);

#endif
