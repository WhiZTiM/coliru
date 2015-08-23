#include <valarray>
#include <iostream>
int main()
{
    std::valarray<int> v{1,2,3};
    v.resize(3);
    for(int n: v) std::cout << n << ' ';
    std::cout << '\n';
}