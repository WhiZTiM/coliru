#include <iostream>

template <int I> struct banana {
    int getNumber() { return 5; }

    //int getNumber<0>() { return 6; } // WRONG
};

template<> int banana<0>::getNumber(){ return 6;} // CORRECT WAY OF SPECIALIZING

int main()
{
    banana<42> foo;
    banana<0> bar;

    std::cout << foo.getNumber() << std::endl; // outputs 5
    std::cout << bar.getNumber() << std::endl; // outputs 6
}