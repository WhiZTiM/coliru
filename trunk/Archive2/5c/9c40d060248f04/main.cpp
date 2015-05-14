#include <iostream>
template<typename ...Args>
int fold(Args&&... args)
{
    return (... * args);
}
int main()
{
    std::cout << fold(1, 2, 3, 4, 5);
}