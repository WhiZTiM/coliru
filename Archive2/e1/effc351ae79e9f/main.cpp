#include <iostream>


struct A
{
    A & operator --(int)
    {
        std::cout << "post-decrement\n";
        return *this;
    }
    
    A operator -(const A & )
    {
        std::cout << "subtraction\n";
        return *this;
    }
};


int main()
{
    A a, b;
    a-----b;
}



