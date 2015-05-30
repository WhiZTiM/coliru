#include <cstdio>

int main(){
  int a = 0;
  printf("%ld\n", sizeof (a) + 1);
  printf("%ld\n", sizeof (a + 999) + 1);
}