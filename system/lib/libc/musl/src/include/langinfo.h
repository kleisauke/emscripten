#ifndef LANGINFO_H
#define LANGINFO_H

#ifdef __EMSCRIPTEN__
#include "../../../../../include/libc/langinfo.h"
#else
#include "../../include/langinfo.h"
#endif

char *__nl_langinfo_l(nl_item, locale_t);

#endif
