#include <iostream>
#include <vector>
int main()
{
    std::vector<int> v(8);
    for (size_t i = 0; i < v.size(); ++i)
    {
        v[i] = i;
    }
    
    for (int val : v)
    {
        std::cout << val << '\n';
    }
}
