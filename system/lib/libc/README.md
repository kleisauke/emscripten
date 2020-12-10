This folder contains the musl version of libc at `/musl`. The upstream version can be found at http://www.musl-libc.org/.
Most of the source comes from musl 1.2.1, with some exceptions listed below.

Some changes have been made to the version that was taken from upstream, including:

 * Emscripten-specific changes (from before this readme existed). These should be marked with `XXX EMSCRIPTEN` in the source, or ifdefed with `#if __EMSCRIPTEN__`. They are mostly in pthreads code and hopefully temporary.
 * Apply [patch](https://www.openwall.com/lists/musl/2020/11/19/1/1) for [CVE-2020-28928](https://www.openwall.com/lists/musl/2020/11/19/1) (if applicable).
 * Switch to using the wasi `fd_write` syscall instead of `writev`.
 * Simplify stdout stream handling: do not support seeking, terminal handling, etc., as it just increases code size and Emscripten doesn't have those features anyhow.
 * Setting `_POSIX_REALTIME_SIGNALS` and `_POSIX_SPAWN` macros to -1, to exclude unsupported functions.
