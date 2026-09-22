/* Adapted from rules_cc_autoconf examples/simple/simple_test.c (MIT). */
#include "cc_autoconf/config.h"

#include <stdio.h>
#include <string.h>

#if !defined(HAVE_MALLOC) || !defined(HAVE_FREE)
#error "expected HAVE_MALLOC and HAVE_FREE to be defined"
#endif
#if !defined(HAVE_STDIO_H) || !defined(HAVE_STDLIB_H) || !defined(HAVE_STRING_H)
#error "expected HAVE_STDIO_H, HAVE_STDLIB_H, HAVE_STRING_H to be defined"
#endif
#if defined(HAVE_THIS_HEADER_DOES_NOT_EXIST_H)
#error "a header that does not exist must not be reported as present"
#endif

#include <stdlib.h>

int main(void) {
  void *p = malloc(16);
  if (p == NULL) return 1;
  free(p);
  if (strcmp(PACKAGE_NAME, "bcr_smoke_test") != 0) {
    fprintf(stderr, "PACKAGE_NAME = %s\n", PACKAGE_NAME);
    return 1;
  }
  if (strcmp(PACKAGE_VERSION, "0.1.0") != 0) {
    fprintf(stderr, "PACKAGE_VERSION = %s\n", PACKAGE_VERSION);
    return 1;
  }
  printf("%s %s: autoconf checks OK\n", PACKAGE_NAME, PACKAGE_VERSION);
  return 0;
}
