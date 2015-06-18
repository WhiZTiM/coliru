#include <iostream>
#include <functional>
#include <typeinfo>
#include <vector>

int add(int a, int b) {return a + b;}



int main() {
    
    std::vector<std::function<int(int)>> funcs;
    
    for (int i = 0; i < 5; ++i) {
        auto f = std::bind(add, std::placeholders::_1, i+1);
        funcs.push_back(f);
    }
    
   
    int i = 0;
    for (int k = 0; k > -10; k = k - 2) {
        std::cout << funcs[i](k) << std::endl;
        ++i;
    }
    
    return 0;   
}