#include <iostream>
#include <string>
#include <array>

struct S
{
    explicit S(int i) : i_{i}
    {};
    
    int i_;
};

int main()
{
    std::array<S, 2> arr = { S{1}, S{2} };
    
    std::cout << arr[0].i_ << std::endl;
    std::cout << arr[1].i_ << std::endl;
}
