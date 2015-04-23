#include <iostream>
#include <memory>
#include <utility>
 
struct A {
    A(int&& n) { std::cout << "rvalue overload, n=" << n << "\n"; }
    A(int& n)  { std::cout << "lvalue overload, n=" << n << "\n"; }
};
 
template<class T, class U>
std::unique_ptr<T> make_unique(U&& u)
{
    std::cout << type_id(u).name; << std::endl;
    return std::unique_ptr<T>(new T(std::forward<U>(u)));
}
 
int main()
{
    std::unique_ptr<A> p1 = make_unique<A>(2); // rvalue
    int i = 1;
    std::unique_ptr<A> p2 = make_unique<A>(std::move(i)); // lvalue
}