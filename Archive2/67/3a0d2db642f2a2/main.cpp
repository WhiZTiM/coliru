#include <numeric>
#include <iostream>
#include <vector>
#include <functional>
int main()
{
    std::vector<int> a{0, 1, 0, 1, 0};
    std::vector<int> b{0, 0, 1, 1, 0};
 
    int err = std::inner_product(a.begin(), a.end(), b.begin(), 0,
                                std::plus<int>(), std::not_equal_to<int>());
    std::cout << "bit errors: " <<  err << '\n';
}