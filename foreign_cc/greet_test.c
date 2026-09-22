#include <stdio.h>
#include <string.h>

#include "greet.h"

int main(void) {
  char buf[64];
  int n = greet("Bazel", buf, sizeof buf);
  if (n != 13 || strcmp(buf, "Hello, Bazel!") != 0) {
    fprintf(stderr, "unexpected greeting: %d %s\n", n, buf);
    return 1;
  }
  puts(buf);
  return 0;
}
