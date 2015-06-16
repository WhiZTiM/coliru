#include <iostream>
#include <typeinfo>

struct Bar
{
    Bar(double);  // some non-default ctor
    double f(); // some function of which return type we want to get
};

using Barref = Bar&&;

int main()
{
    // FUNKY, compiles in g++, not in clang++
    // error: unexpected type name 'Barref': expected expression
    decltype(Barref.f()) x;
    std::cout << typeid(x).name() << std::endl; // i -> int INCORRECT

    // OK
    decltype(std::declval<Bar>().f()) y;
    std::cout << typeid(y).name() << std::endl; // d -> double CORRECT
}
