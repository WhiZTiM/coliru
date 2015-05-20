
#include <boost/function.hpp>
#include <iostream>

void f() 
{
    std::cout << "the hell they don't have boost::function" << std::endl;
}

int main()
{
    boost::function<void()> bfv = f;
    bfv();
}