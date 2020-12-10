#ifndef STDLIB_H
#define STDLIB_H

#ifdef __EMSCRIPTEN__
#include "../../../../../include/libc/stdlib.h"
#else
#include "../../include/stdlib.h"
#endif

hidden int __putenv(char *, size_t, char *);
hidden void __env_rm_add(char *, char *);
hidden int __mkostemps(char *, int, int);
hidden int __ptsname_r(int, char *, size_t);
hidden char *__randname(char *);

#endif
