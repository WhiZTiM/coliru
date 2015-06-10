#include<iostream>
#include<vector>
   
std::vector<int> foo(std::vector<int> v)
{
    std::vector<int> result;
    std::cout << "Initial size = " << v.size() << std::endl;
    for(int i = 0; i < v.size(); i++)
    {
        std::cout << "Size = " << v.size() << std::endl;
        v.erase(v.begin() + i);
    }
    return result;
}

int main()
{
    int a[] = {1 ,2, 5, 8, 213, 2};
    std::vector<int> v;
    v.assign(a, a+6);
    foo(v);
}