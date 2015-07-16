#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
  int i;
  long int rr;
  double   dd;
  double arr[10] = {55.550,55.551,55.552,55.553,55.554,55.555,55.556,55.557,55.558,55.559};
  printf("\n\nTest1");
  for(i=0;i<10;i++)
  {
    dd = 100 * arr[i];
    rr = (long int)dd;
    printf("\n 100 * %10.4lf == %10.4lf >>>>> %ld",arr[i], dd, rr);
  }
  printf("\n\nTest2");
  for(i=0;i<10;i++)
  {
    printf("\n 100 * %10.4lf == %10.4lf >>>>> %ld",arr[i], 100 * arr[i],                    (long int)(100 * arr[i]));
  }
  return 0;
}