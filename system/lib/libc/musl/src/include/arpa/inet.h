#ifndef ARPA_INET_H
#define ARPA_INET_H

#ifdef __EMSCRIPTEN__
#include "../../../../../../include/libc/arpa/inet.h"
#else
#include "../../../include/arpa/inet.h"
#endif

hidden int __inet_aton(const char *, struct in_addr *);

#endif
