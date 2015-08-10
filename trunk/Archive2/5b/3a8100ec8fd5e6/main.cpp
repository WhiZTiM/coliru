#include <vector>
#include <iostream>
#include <type_traits>

int x;
int& getFoo() { return x; }

int main()
{
    auto x = getFoo();
    std::cout << std::is_same<int&, decltype(x)>::value;
}
