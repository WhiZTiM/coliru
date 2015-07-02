#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v = {0, 6, 3, 10, 2};
    std::sort(v, v.end());
    
    for (auto&& x : v) std::cout << x << " ";
    return 0;
}