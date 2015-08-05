#include <stdio.h>

#define LFSR_bit(prev) (((prev >> 0) ^ (prev >> 2) ^ (prev >> 3) ^ (prev >> 5)) & 1)
#define LFSR(prev)     ((prev >> 1) | (LFSR_bit(prev) << 15))

enum test { Foo = RANDOM, 
            Bar = LFSR(Foo) };  
            
template <int lfsr>
struct random
{
  enum { value = lfsr };
  typedef random<LFSR(lfsr)> Next;
};

int main(void)
{
  enum test foo = Foo;
  enum test bar = Bar;
  printf("foo = %d, bar = %d\n", foo, bar);
  printf("%d %d %d\n", random<RANDOM>::value, 
                       random<RANDOM>::Next::value,
                       random<RANDOM>::Next::Next::value); 
} 