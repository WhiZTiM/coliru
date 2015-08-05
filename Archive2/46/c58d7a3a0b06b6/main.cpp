#include <stdio.h>
#include <tuple>

#define LFSR_bit(prev) (((prev >> 0) ^ (prev >> 2) ^ (prev >> 3) ^ (prev >> 5)) & 1)
#define LFSR(prev)     ((prev >> 1) | (LFSR_bit(prev) << 15))

enum test { Foo = RANDOM, 
            Bar = LFSR(Foo) };  
            
template <int lfsr>
struct Random
{
  enum { value = lfsr };
  typedef Random<LFSR(lfsr)> Next;
};

template <int I>
struct TypeMap;

template <>    
struct TypeMap<0> { 
    typedef int type;      
};

template <>    
struct TypeMap<1> { 
    typedef char type;      
};

template <>    
struct TypeMap<2> { 
    typedef float type;      
};

template <>    
struct TypeMap<3> { 
    typedef double type;      
};

template <int seed>
struct FourTuple
{ 
  typedef typename TypeMap<LFSR(seed) % 4>::type First;
  typedef typename TypeMap<LFSR(LFSR(seed)) % 4>::type Second;
  typedef typename TypeMap<LFSR(LFSR(LFSR(seed))) % 4>::type Third;
  typedef typename TypeMap<LFSR(LFSR(LFSR(LFSR(seed)))) % 4>::type Fourth;
  
  typedef std::tuple<First, Second, Third, Fourth> type;
};


int main(void)
{
  enum test foo = Foo;
  enum test bar = Bar;
  printf("foo = %d, bar = %d\n", foo, bar);
  printf("%d %d %d\n", Random<RANDOM>::value, 
                       Random<RANDOM>::Next::value,
                       Random<RANDOM>::Next::Next::value); 
  auto tuple = FourTuple<RANDOM>::type();
} 