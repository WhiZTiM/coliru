#include <typeinfo>
#include <iostream>

template <size_t N>
struct A
{
} ;

template <>
struct A<10>
{
    int x ;
} ;


int main()
{
    constexpr int x1 = 10 ;
    constexpr int x1b = 10 ;
    constexpr int x1c = 20 ;
    volatile int x2 = 10 ;
    const double d1 = 1.1 ;
   
   
   
    std::cout << typeid( A<11> ).name() << "\n" 
              << typeid( A<10> ).name() << "\n" ;
    
    auto f1 = [=] () { return x2 * 20 ; } ;
    
    std::cout << typeid( f1 ).name() << "\n" ;
    std::cout << f1() << "\n" ;
}