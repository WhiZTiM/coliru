#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    std::vector<int> v{1, 2, 0, 7, 8};
    auto forbid = {0, 1};
    auto min_iter = std::min_element(v.cbegin(), v.cend(), [&forbid](int a, int b){
        return a < b && std::none_of(forbid.begin(), forbid.end(), [a, b](int i){ return a == i || b == i;}); 
    });
    std::cout << *min_iter << std::endl;
}
