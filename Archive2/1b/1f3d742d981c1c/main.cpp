#include <iostream>
#include <type_traits>

template<typename T> struct check_{ typedef T type; };
/*template <typename T >
void f(T t, typename check_<decltype(t+1)>::type* = 0)
{
    std::cout << "satisfies" << std::endl;
}    
*/
template <typename T >
auto f(T t) -> decltype(t+1, void())
{
    std::cout << "satisfies" << std::endl;
} 
template <typename T>
void f(T t )
{
    std::cout << "doesn't satisfy" << std::endl;
}    

struct A{
     
};

int main()
{
    
    A a;
    f(a);
   // f(1);
    
}
