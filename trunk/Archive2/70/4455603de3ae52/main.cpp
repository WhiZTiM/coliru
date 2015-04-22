#include <stdlib.h>

void bitwise_and(
    char*       __restrict__  result,
    const char* __restrict__  lhs,
    const char* __restrict__  rhs,
    size_t                    length)
{
  for(size_t i = 0; i < length; ++i)
  {
    *result++ = *lhs++ & *rhs++;
  }
}

int main()
{}
