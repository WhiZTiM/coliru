#include <iostream>
#include <mutex>
#include <thread>
#include <memory>
#include <vector>


struct s
{
    std::unique_ptr<int> p;
};
        
int main() {
     std::vector<s> v(10);
     std::vector<std::unique_ptr<int>> foo;
     
     for (auto&& e : v)
     {
         foo.push_back(std::move(e.p));
     }
     
     return 0;
}