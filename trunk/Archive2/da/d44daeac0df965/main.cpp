#include <iostream>
#include <vector>

struct Foo
{
    int i = 3;
    int j;
};

int main()
{
    std::vector<Foo> v;
    v.push_back({1,2});
    std::cout << v.at(0).i << " " << v.at(0).j << std::endl;
}