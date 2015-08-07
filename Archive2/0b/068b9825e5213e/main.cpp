#include <iostream>

template <typename T> void TD() { std::cout << __PRETTY_FUNCTION__ << std::endl; }

struct Widget {};

int main()
{
    Widget w;
    const Widget& cw = w;
    auto& myWidget1 = cw;
    
    TD<decltype(myWidget1)>();
}
