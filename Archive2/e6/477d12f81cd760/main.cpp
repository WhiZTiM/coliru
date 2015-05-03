#include <vector>
#include <string>
#include <iostream>
int main()
{
    std::vector<int> v = {1, 2, 3, 4};
    std::vector<std::vector<std::string>> vv = {{"a", "b"}, {"c", "d", "e"}};

    for(int n : v) std::cout << n << ' ';
    std::cout << '\n';
    for(auto& r : vv) {
        for(auto& s : r)
            std::cout << s << ' ';
        std::cout << '\n';
    }
    std::cout << '\n';
}
