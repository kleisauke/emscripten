# Copyright 2020 The Emscripten Authors.  All rights reserved.
# Emscripten is available under two separate licenses, the MIT license and the
# University of Illinois/NCSA Open Source License.  Both these licenses can be
# found in the LICENSE file.

"""Runs the pthreads test from the upstream posixtest suite in:
   ./tests/third_party/posixtestsuite
See
   https://github.com/juj/posixtestsuite

Verify that it runs properly in musl:
   cd ./tests/third_party/posixtestsuite
   docker run -v $(pwd):/app -w /app -it alpine:latest \
      apk add build-base && \
      POSIX_TARGET=conformance/interfaces/pthread_join make LDFLAGS='-pthread'

Where [INTERFACE_DIR] is for e.g.: pthread_join
"""

import glob
import os

from runner import RunnerCore, path_from_root
from tools import config
from tools.shared import EMCC
import test_posixtest_browser

testsuite_root = path_from_root('tests', 'third_party', 'posixtestsuite')


class posixtest(RunnerCore):
  """Run the suite under node (and in parallel)

  This class get populated dynamically below.
  """
  pass


def filter_tests(all_tests):
  pthread_tests = [t for t in all_tests if t.startswith('pthread_')]
  # filter out some tests we don't support
  pthread_tests = [t for t in pthread_tests if not t.startswith('pthread_atfork')]
  pthread_tests = [t for t in pthread_tests if not t.startswith('pthread_sigmask')]
  return pthread_tests


def get_pthread_tests():
  # For now, we don't require the submodule to exist.  In this case we just report
  # no tests
  pthread_test_root = os.path.join(testsuite_root, 'conformance', 'interfaces')
  if not os.path.exists(pthread_test_root):
    print('posixtestsuite not found (run git submodule update --init?)')
    return []
  pthread_tests = filter_tests(os.listdir(pthread_test_root))
  pthread_tests = [os.path.join(pthread_test_root, t) for t in pthread_tests]
  return pthread_tests


engine = config.NODE_JS + ['--experimental-wasm-threads', '--experimental-wasm-bulk-memory']

# Mark certain tests as not passing
disabled = {
  'test_pthread_attr_setscope_5_1': 'internally skipped (PTS_UNTESTED)',
  # TODO(kleisauke): Could we mimic the scheduling policy somehow?
  'test_pthread_attr_setinheritsched_2_3': 'scheduling policy/parameters unsupported',
  'test_pthread_attr_setinheritsched_2_4': 'scheduling policy/parameters unsupported',
  'test_pthread_attr_setschedparam_1_3': 'scheduling policy/parameters unsupported',
  'test_pthread_attr_setschedparam_1_4': 'scheduling policy/parameters unsupported',
  'test_pthread_create_3_2': 'scheduling policy/parameters unsupported',
  'test_pthread_getschedparam_1_3': 'scheduling policy/parameters unsupported',
  # TODO(kleisauke): Did we cause a regression in the following tests?
  'test_pthread_cond_signal_1_1': 'fails with a nonzero exit code (flaky)',
  'test_pthread_cond_timedwait_2_6': 'fails with: "The child did not own the mutex inside the cleanup handler" (PTS_FAIL)',
  'test_pthread_cond_wait_2_3': 'fails with: "The child did not own the mutex inside the cleanup handler" (PTS_FAIL)',
}


def make_test(name, testfile, browser):

  def f(self):
    if name in disabled:
      self.skipTest(disabled[name])
    args = ['-I' + os.path.join(testsuite_root, 'include'),
            # TODO(kleisauke): Run with ASan. Note that this requires matching signatures, i.e:
            # void *thread_func() -> void *thread_func(void *unused)
            # void *a_thread_func() -> void *a_thread_func(void *unused)
            # void *a_thread_function() -> void *a_thread_function(void *unused)
            # void a_cleanup_func() -> void a_cleanup_func(void *unused)
            # etc, etc.
            #'-O0',
            #'-g3',
            #'-fsanitize=address',
            '-Werror',
            '-Wno-format-security',
            '-Wno-int-conversion',
            '-sUSE_PTHREADS',
            '-sEXIT_RUNTIME',
            '-sTOTAL_MEMORY=256mb',
            '-sPTHREAD_POOL_SIZE=40']
    if browser:
      # Only are only needed for browser tests of the was btest
      # injects headers using `-include` flag.
      args += ['-Wno-macro-redefined', '-D_GNU_SOURCE']
      self.btest(testfile, args=args, expected='exit:0')
    else:
      self.run_process([EMCC, testfile, '-o', 'test.js'] + args)
      self.run_js('test.js', engine=engine)

  return f


for testdir in get_pthread_tests():
  basename = os.path.basename(testdir)
  for test_file in glob.glob(os.path.join(testdir, '*.c')):
    if not os.path.basename(test_file)[0].isdigit():
      continue
    test_suffix = os.path.splitext(os.path.basename(test_file))[0]
    test_suffix = test_suffix.replace('-', '_')
    test_name = 'test_' + basename + '_' + test_suffix
    setattr(posixtest, test_name, make_test(test_name, test_file, browser=False))
    setattr(test_posixtest_browser.posixtest_browser, test_name, make_test(test_name, test_file, browser=True))
