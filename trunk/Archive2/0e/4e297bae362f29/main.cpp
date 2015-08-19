#include <iostream>

struct B
{
    B() { std::cout << "B Created\n"; }  
    B(int) { std::cout << "Parametrised constructor"; }
};

int main()
{

    std::cout << "Hello\n";
    B a; //Ceates object
    B b(); //Declares function
    std::cout << "Hi!\n";
    b(); //Calls function
}

B b()
{
    std::cout << "In function\n";
    return 1;
}