#include <unordered_set>
#include <iostream>

int main()
{
    std::unordered_set<int> u = {0,1,2,1024};
    
    auto p = [&]{
        for(auto i : u) std::cout << i << ", ";
        std::cout << "\n";
    };
    
    p();
    u.rehash(10);
    p();
}