#include <type_traits>
#include <iostream>

template<class T>
std::enable_if_t<std::is_same<int, T>::value> f(T) { std::cout<<"1\n"; }

template<class T>
std::enable_if_t<!std::is_same<int, T>::value> f(T) { std::cout<<"2\n"; }

int main() {
    f(0);
    f('x');
}