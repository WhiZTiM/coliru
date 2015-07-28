#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
 
int main()
{
    std::vector<int> vec{ 1,2,3,4,5,6,7 };
    int x = 4;
    vec.erase(std::remove_if(vec.begin(), vec.end(), [x](int n) { return n < x; } ), vec.end());
 
    std::cout << "vec: ";
    for (auto i: vec) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
 
    // the type of a closure cannot be named, but can be inferred with auto
    auto add4 = [](int i) { return i+4; };
    std::cout << "add4: " << add4(6) << '\n'; 
}