#include <stdlib.h>
#include <stdio.h>

int main() {
  unsigned n = 10;
  int (*a)[n] = NULL; // `a` is a pointer to a VLA 

  unsigned i = 0;
  sizeof a[i++];  
  printf("%d\n", i);
}