#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

static void test_malloc_free(bool reassign_abc) {  
  int d = 32;
  int *abc = &d;
  d = 56;
  
  abc = malloc(sizeof(int));
  printf("%p\n", abc);
  
  *abc = 666;

  if (reassign_abc) {
    abc = &d;
  }
  
  printf("%p\n", abc);
  free(abc);
}



int main() {
    //test_malloc_free(false);
    test_malloc_free(true);
}
