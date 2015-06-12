#include <type_traits>
#include <iostream>
#include <functional>

void func( int i )
{
    std::function<void()> a, b, c;
    a = [&]{if(i>0){b(); c();}};
    b = [&]{std::cout << "b" << i--;a();};
    c = [&]{std::cout << "c" << i--;a();};
    a();
}


int main()
{
    func(5);
}