#include <stdio.h>

#include "mul.h"

int main(void) {
  if (mul(6, 7) != 42 || mul(-2, 3) != -6) {
    fprintf(stderr, "mul() is broken\n");
    return 1;
  }
  printf("mul(6, 7) = %d\n", mul(6, 7));
  return 0;
}
