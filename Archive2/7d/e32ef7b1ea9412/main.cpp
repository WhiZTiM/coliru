#include <iostream>
#include <type_traits>

template <typename... Args>
struct head {};

template <typename Head, typename... Args>
struct head<Head, Args...>
{
    using type = Head;
};

template <typename T>
struct A : T
{    
    template <typename... Args>
    A(Args&&... params) : T(std::forward<Args>(params)...), x(0) {
        std::cout << "Member 'x' was default constructed\n"; 
    }

    template <typename O, typename... Args, typename = typename std::enable_if<std::is_constructible<int, O>::value>::type>
    A(O& z, Args&&... params) : T(std::forward<Args>(params)...), x(z) {
        std::cout << "Member 'x' was constructed from arguments\n"; 
    }

    int x;
};

struct B
{
    B(const char*) {}
};

int main()
{
    double x = 3.0;
    A<B> yy(x, "test");    
}