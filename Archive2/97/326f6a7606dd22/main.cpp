#include <tuple>
#include <iostream>

template<typename I>
struct A {};

template<typename I, typename... T>
void f(A<I>, std::tuple<T*...>) { std::cout << "0\n"; }

template<typename... T>
void f(A<int>, std::tuple<T*...>) { std::cout << "1\n"; }

int main()
{
    f(A<int>{}, std::tuple<char*, int*, float*>{});
}