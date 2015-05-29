#include <iostream>

struct Foo
{
    Foo() = default;
    double m_default;
    double m_value{};
    double m_zero{0.0};
};

int main()
{
    Foo f;
    std::cout << f.m_default << std::endl;
    //std::cout << f.m_value << std::endl;
    std::cout << f.m_zero << std::endl;
    return 0;
}