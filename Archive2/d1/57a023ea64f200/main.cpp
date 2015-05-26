#include <iostream>

template <char... C>
void meow()
{
    (std::cout << ... << C);
}

int main()
{
    meow<'H', 'e', 'l', 'l', 'o', ',', ' ', 'w', 'o', 'r', 'l', 'd', '!', '\n'>();
}