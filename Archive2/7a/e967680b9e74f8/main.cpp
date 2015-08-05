#include <stdio.h>

enum test { Foo = RANDOM, Bar }; 

int main(void)
{
  enum test foo = Foo;
  enum test bar = Bar;
  printf("foo = %d, bar = %d\n", foo, bar);
}