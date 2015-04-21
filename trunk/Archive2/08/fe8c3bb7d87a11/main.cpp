#include <iostream>

struct X
{
    ~X () {std::cout << "bye " << std::endl;}
};

int main ()
{
    X x;
    std::exit (0);
}