#ifndef UNISTD_H
#define UNISTD_H

#ifdef __EMSCRIPTEN__
#include "../../../../../include/libc/unistd.h"
#else
#include "../../include/unistd.h"
#endif

extern char **__environ;

hidden int __dup3(int, int, int);
hidden int __mkostemps(char *, int, int);
hidden int __execvpe(const char *, char *const *, char *const *);
hidden int __aio_close(int);
hidden off_t __lseek(int, off_t, int);

#endif
