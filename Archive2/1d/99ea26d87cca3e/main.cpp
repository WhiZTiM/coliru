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
    Pancake pancake;
    Waffle waffle;
    pancake.goodness = 0.0;
    waffle.goodness = 0.1234;
    ( pancake.goodness == waffle.goodness) ? std::cout << 47 : std::cout << -8;
}
