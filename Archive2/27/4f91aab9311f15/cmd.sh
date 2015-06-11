echo '#include <stdio.h>

int main(void) {
  puts("hello, world!");
  printf("N = %d\n", N);
  return 0;
}
' > a.c && gcc -DN=346 -O2 -Wall -Wextra a.c && ./a.out