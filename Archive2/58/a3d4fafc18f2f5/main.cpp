#include <iostream>
#include <vector>

int main(void) {
    std::vector<bool> a;
    a.push_back(0);
    
    auto x = a[0];
    x = 1;
    
    std::cout << a[0] << std::endl;
    
    return 0;
}