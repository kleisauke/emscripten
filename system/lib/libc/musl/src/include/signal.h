#ifndef SIGNAL_H
#define SIGNAL_H

#ifdef __EMSCRIPTEN__
#include "../../../../../include/libc/signal.h"
#else
#include "../../include/signal.h"
#endif

hidden int __sigaction(int, const struct sigaction *, struct sigaction *);

hidden void __block_all_sigs(void *);
hidden void __block_app_sigs(void *);
hidden void __restore_sigs(void *);

hidden void __get_handler_set(sigset_t *);

#endif
