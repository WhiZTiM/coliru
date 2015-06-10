#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>

int main()
{
    std::vector<int> v{1, 2, 0, 7, 8};
    auto forbid = {0, 1};
    auto ret = INT_MAX;
    for (int i : v) {
        if (std::find(forbid.begin(), forbid.end(), i) != forbid.end()) continue;
        ret = std::min(ret, i);
    }
    std::cout << ret << std::endl;
}
