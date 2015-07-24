#include <iostream>
#include <string>

int main()
{
    int foo = 123456789;
    int pos = 3;
    std::cout << std::to_string(foo)[pos- 1];
}