#include <iostream>

class Pancake
{
    public:
    double goodness;
};
class Waffle
{
    public:
    double goodness;
};

int main()
{
    Pancake p;
    Waffle w;
    p.goodness = 0.0;
    w.goodness = 0.1234;
    ( p.goodness == w.goodness) ? std::cout << 7 : std::cout << 4;
}
