#include <typeinfo>
#include <iostream>

template<class T, class U>
auto add(T t, U u) -> decltype(t + u) // Return type is type of operator+(T,U)
{
    return t + u;
}
 
int main()
{
    auto a = 1 + 2;
    std::cout << "type of a: " << typeid(a).name() << " result: " << a << '\n';
    
    auto b = add(11, 22);
    std::cout << "type of b: " << typeid(b).name() << " result: " << b << '\n';
}