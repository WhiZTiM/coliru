#include <stdio.h>

typedef struct 
{
  int a, b;
} S;

S foo(void)
{
  return {1, 2};
}

int main(void)
{
  const S s = foo();
  if((s.a == 1) && (s.b == 2))
  {
    printf("Result is correct!");
  }
  else
  {
    printf("Result is not correct!");
  }
  return 0;
}