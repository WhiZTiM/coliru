#include <iostream>
#include <iomanip>

int main()
{
    namespace STD = std;
    STD::cout << std::boolalpha << (0.1 + (0.2 + 0.3) == (0.1 + 0.2) + 0.3);
}
