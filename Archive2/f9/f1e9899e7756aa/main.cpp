#include <iostream>
#include <utility>

struct Cheese
{
    Cheese() { std::cout << "Cheese()" << std::endl; }
    Cheese(const Cheese &o) { std::cout << "CheeseCopy()" << std::endl; }
    //Cheese(Cheese &&o) { std::cout << "CheeseMove()" << std::endl; }
};

int main()
{
    Cheese c([]() { Cheese cheese; return std::move(cheese); }());   
}