#include <iostream>


void foo(int x)
{
     std::cout << "     " <<  x << "\n";
}


void foo(int& x)
{
    std::cout << "     " <<  x << "\n";
}


int main()
{
   
    foo(10);
}