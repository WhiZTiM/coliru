#include <type_traits>
#include <iostream>
#include <functional>

void func( int i )
{
    std::function<void()> a, b, c;
    a = [&]{b(); c();};
    b = [&]{std::cout << "b" << i;};
    c = [&]{std::cout << "c" << i;};
    a();
}


int main()
{
    func(5);
}