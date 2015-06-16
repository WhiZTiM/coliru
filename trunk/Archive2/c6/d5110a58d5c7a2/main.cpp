#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>
 

int f()
{
    std::cout << "in f() - start\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "in f() - end\n";    
    return 42;
}
int g()
{
    std::cout << "in g() - start\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "in g() - end\n";
    return 42;
}
 
int main()
{
    auto result_f = std::async(std::launch::async, f); 
    std::cout << "outside f()\n";
   // {
     /*auto result_g =*/ std::async(std::launch::async, g);
   // }
    std::cout << "outside g()\n";
    int i = result_f.get();
    std::cout << i  << "\n";
}