#include <iostream>

int main()
{
    auto v = "hello";
    std::cout << 5??(v??) << std::endl;
}
