#include <cstdio>

int main(){
  int a = 0;
  printf("%zu\n", sizeof (a) + 1);
  printf("%zu\n", sizeof (a + 999) + 1);
}