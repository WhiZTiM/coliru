#include <iostream>

#define COUNT_ARGS(...)     PP_NARG_IMPL(__VA_ARGS__,PP_RSEQ_N()) 
#define PP_NARG_IMPL(...)   PP_ARG_N(__VA_ARGS__) 
#define PP_ARG_N( _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...) N 
#define PP_RSEQ_N() 10,9,8,7,6,5,4,3,2,1,0 

int main()
{
  std::cout << COUNT_ARGS(a,b,c,d);
}