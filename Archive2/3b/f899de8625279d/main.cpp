#include <iostream>
#include <type_traits>

class A {
  public:
    A() = default;
    A(const A&) = delete;
};

int main()
{
    std::cout << std::boolalpha << std::is_trivially_copyable<A>::value << std::endl;

}