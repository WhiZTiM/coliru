#include <iostream>
#include <vector>
#include <algorithm>
#include <type_traits>


template <typename It>
bool process(It first , It last )
{
  // std::cout << "Typeid :" << typeid( const decltype(*begin) &).name( ) << '\n' ;
   
  return  std::all_of( first, last, 
                       [](  typename std::add_const<decltype(*first)>::type &i )
                       { 
                            return i % 2 == 0; 
                       } 
                     ) ;
}


int main ()
{

    std::vector<int> v { 2,4,6,8 } ;

    std::cout << "Are all even ? " << process(v.begin() , v.end() );

}

