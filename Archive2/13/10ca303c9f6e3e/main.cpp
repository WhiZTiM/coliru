#include <stdlib.h>

int main()
{
  int n[1][2][3][4];   
    
  size_t i;
  size_t count = sizeof(n) / sizeof(*n);
  int *p = n;
  for( i = 0; i < count; i++ )
  {
    p[i] = -3;
  }
}