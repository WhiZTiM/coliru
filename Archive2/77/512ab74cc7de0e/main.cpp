#include <iostream>
#include <iterator>
#include <vector>
 
int main() 
{
    std::vector<int> v{ 3, 1, 4, 8, 10 };
 
    auto it = v.begin();
 
 while(v.begin!=v.end)
    auto nx = std::next(it, 2);
 
    std::cout << *it << ' ' << *nx << '\n';
}