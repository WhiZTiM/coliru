#include <tuple>
#include <cstdio>


void func( int x1, int x2,int  x3, int x4)
{
  std::tuple<int,int,int,int> t{x1,x2,x3,x4};
  
  int a, b, c, d; // in real context these names would be meaningful
  std::tie(a, b, c, d) = t;
  
  printf( "%d %d %d %d\n", std::get<0>(t), std::get<1>(t), std::get<2>(t), std::get<3>(t) ) ;
}


int main()
{
    func( 10, 20, 50, 100 ) ;
}