#include <random>
#include <iostream>
 
int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 6);

    using pt = std::uniform_int_distribution<>::param_type;
    for (int n=0; n<10; ++n)
        std::cout << dis(gen, pt(1, n+1)) << ' ';
    std::cout << '\n';
}