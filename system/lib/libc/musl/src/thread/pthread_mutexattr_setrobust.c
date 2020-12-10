#include "pthread_impl.h"
#ifndef __EMSCRIPTEN__ // XXX Emscripten revert musl commit 5994de4e02a05c19a6bddadcfb687ab2e7511bd6
#include "syscall.h"

static pthread_once_t check_robust_once;
static int check_robust_result;

static void check_robust()
{
	void *p;
	size_t l;
	check_robust_result = -__syscall(SYS_get_robust_list, 0, &p, &l);
}
#endif

int pthread_mutexattr_setrobust(pthread_mutexattr_t *a, int robust)
{
	if (robust > 1U) return EINVAL;
#ifndef __EMSCRIPTEN__ // XXX Emscripten revert musl commit 5994de4e02a05c19a6bddadcfb687ab2e7511bd6
	if (robust) {
		pthread_once(&check_robust_once, check_robust);
		if (check_robust_result) return check_robust_result;
		a->__attr |= 4;
		return 0;
	}
#endif
	a->__attr &= ~4;
#ifdef __EMSCRIPTEN__ // XXX Emscripten revert musl commit 5994de4e02a05c19a6bddadcfb687ab2e7511bd6
	a->__attr |= robust*4;
#endif
	return 0;
}
