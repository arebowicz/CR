#include "oneElementStack.h"

static int buffer = EOF;

int add(int c) {
  return buffer = c;
}

int delete() {
  int tmp = buffer;
  buffer = EOF;
  return tmp;
}

int value() {
  return buffer;
}