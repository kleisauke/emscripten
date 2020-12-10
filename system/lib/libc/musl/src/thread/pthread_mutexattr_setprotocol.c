#include "pthread_impl.h"
#ifndef __EMSCRIPTEN__ // XXX Emscripten PI mutexes are unsupported (reverts musl commit 54ca677983d47529bab8752315ac1a2b49888870)
#include "syscall.h"

static pthread_once_t check_pi_once;
static int check_pi_result;

static void check_pi()
{
	volatile int lk = 0;
	check_pi_result = -__syscall(SYS_futex, &lk, FUTEX_LOCK_PI, 0, 0);
}
#endif

int pthread_mutexattr_setprotocol(pthread_mutexattr_t *a, int protocol)
{
#ifdef __EMSCRIPTEN__ // XXX Emscripten PI mutexes are unsupported (reverts musl commit 54ca677983d47529bab8752315ac1a2b49888870)
	if (protocol) return ENOTSUP;
	return 0;
#else
	switch (protocol) {
	case PTHREAD_PRIO_NONE:
		a->__attr &= ~8;
		return 0;
	case PTHREAD_PRIO_INHERIT:
		pthread_once(&check_pi_once, check_pi);
		if (check_pi_result) return check_pi_result;
		a->__attr |= 8;
		return 0;
	case PTHREAD_PRIO_PROTECT:
		return ENOTSUP;
	default:
		return EINVAL;
	}
#endif
}
