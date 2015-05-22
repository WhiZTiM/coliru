#include <iostream>
#include <tuple>

#define LR(EXPR) (auto&&... ps){ auto p = std::forward_as_tuple(ps...); return EXPR; }

int main()
{
    std::cout << []LR(std::get<0>(p))("test");
    std::cout << []LR(std::get<0>(p) + std::get<1>(p))(2, 3); 
    std::cout << []LR(std::get<0>(p) + std::get<1>(p))(std::string("hello "), std::string(" world!"));
}
