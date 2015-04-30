#include <stdio.h>

void
hello(const int x) {
  printf("yay: %i\n", x);
}

#define hello(i) \
  hello(i * 2)

int main(void) {
  hello(9);    // macro call
  (hello)(9);  // function call
}