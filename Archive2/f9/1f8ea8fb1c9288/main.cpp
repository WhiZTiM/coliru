#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
 using namespace std;
int main()
{
    std::vector<int> v{5, 8, 4, 3, 2 ,6, 7, 9, 1};
 
    std::nth_element(v.begin(), v.begin() + v.size()/2, v.end());
    std::cout << "The median is " << v[v.size()/2] << '\n';
 
    for (auto s : v)
    std:: cout << s << ' ';
}