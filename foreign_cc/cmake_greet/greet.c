#include "greet.h"

#include <stdio.h>

int greet(const char *name, char *buf, int buf_size) {
  return snprintf(buf, (size_t)buf_size, "Hello, %s!", name);
}
