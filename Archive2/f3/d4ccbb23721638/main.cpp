#include <iostream>
#include <list>
#include <algorithm>
#include <atomic>
#include <omp.h>

struct A {
    
    A(const int& x)
    : _number(x)
    {
        std::cout << "constructed " << _number << std::endl;
    }
    
    A(const A& other)
    {
        _number = other._number;
       std::cout << "called copy for " << _number << std::endl;
    }
    
    int _number;
};

A create(const int& x)
{
    return A(x);    
}

int main() {
    A version1( 1 );
    A version2 = version1;
    A version5 = create( 5 );
    
    std::cout << "finished my testing" << std::endl;

   return 0;
}
