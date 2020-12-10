/*
 * Copyright 2020 The Emscripten Authors.  All rights reserved.
 * Emscripten is available under two separate licenses, the MIT license and the
 * University of Illinois/NCSA Open Source License.  Both these licenses can be
 * found in the LICENSE file.
 */

#include <nl_types.h>
#include <stdio.h>

// See: https://www.gnu.org/software/libc/manual/html_node/Common-Usage.html#How-does-to-this-allow-to-develop
#define MainSet 0x1    /* hello.msg:4 */
#define MainHello 0x1    /* hello.msg:5 */

int main(int argc, char **argv) {
  nl_catd catdesc = catopen("hello.cat", 0);
  if (catdesc != (nl_catd)-1) {
    printf("%s", catgets(catdesc, MainSet, MainHello, "Hello, world!\n"));
    return catclose(catdesc);
  }
  return 1;
}
