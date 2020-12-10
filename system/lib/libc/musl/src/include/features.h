#ifndef FEATURES_H
#define FEATURES_H

#ifdef __EMSCRIPTEN__
#include "../../../../../include/libc/features.h"
#else
#include "../../include/features.h"
#endif

#define weak __attribute__((__weak__))
#define hidden __attribute__((__visibility__("hidden")))
#define weak_alias(old, new) \
	extern __typeof(old) new __attribute__((__weak__, __alias__(#old)))

#endif
