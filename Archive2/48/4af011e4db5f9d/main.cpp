#include <iostream>
#include <utility>
#include <vector>

int main()
{
    std::vector<int> foo = { 1, 2, 3, 42 };
    
    foo.erase(foo.begin() + 2);
}