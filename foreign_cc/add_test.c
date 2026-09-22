#include <stdio.h>

#include "add.h"

int main(void) {
  if (add(2, 3) != 5 || add(-1, 1) != 0) {
    fprintf(stderr, "add() is broken\n");
    return 1;
  }
  printf("add(2, 3) = %d\n", add(2, 3));
  return 0;
}
