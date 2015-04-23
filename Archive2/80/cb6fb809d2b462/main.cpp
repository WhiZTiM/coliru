#include <stdexcept>
#include <iostream>

struct nop
{
    template<typename... Ts>
    nop(Ts &&...)
    {
    }
};

int main()
{
    try
    {
        nop{ (throw std::runtime_error("foo"), 0), (throw std::runtime_error("bar"), 0) };
    }
    catch (std::exception& ex)
    {
        std::cout << ex.what() << '\n';
    }
}
