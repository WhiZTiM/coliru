#include <numeric>
#include <vector>
#include <iostream>
#include <iterator>
#include <functional>
 
int main()
{
    std::vector<int> v = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    v2 = {5,8,7,10,6,13};// or std::vector<int>v(10, 2);
 int first=5;
    std::cout << "The first 10 even numbers are: ";
    std::partial_sum(v2.begin(), v2.end(), 
                     std::ostream_iterator<int>(std::cout, " "),[first](int a,int b)->int{return a+(b-first);});
    std::cout << '\n';
 
    std::partial_sum(v.begin(), v.end(), v.begin(), std::multiplies<int>());
    std::cout << "The first 10 powers of 2 are: ";
    for (auto n : v) {
        std::cout << n << " ";
    }
    std::cout << '\n';
}