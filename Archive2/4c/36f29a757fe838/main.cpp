#include <vector>
#include <type_traits>
#include <iostream>

int main()
{
    std::vector<int> a = {1,2,3};
    auto iter = a.begin();
    std::cout << std::boolalpha << std::is_same<
        decltype(*iter),
        int&>::value << "\n";
}