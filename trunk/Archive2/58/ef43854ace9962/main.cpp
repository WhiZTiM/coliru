#include <iostream>
#include <functional>
#include <vector>

struct A {};
class B {};

int main() {
    std::cout << std::is_same<struct A, A>::value
              << std::is_same<class A, A>::value
              << std::is_same<struct B, B>::value
              << std::is_same<class B, B>::value;
}