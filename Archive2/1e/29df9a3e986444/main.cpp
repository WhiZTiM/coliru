#include <iostream>
#include <iterator>
#include <vector>
 
int main() 
{
    std::vector<int> v{ 13, 111, 54 };
 
    auto distance = std::distance(v.begin(), v.end());
 
    std::cout << distance << '\n';
}