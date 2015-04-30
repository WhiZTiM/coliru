#include <memory>
#include <iostream>
int main()
{
    std::unique_ptr<int> i;
    std::cout << (i == false) << std::endl;
}
    