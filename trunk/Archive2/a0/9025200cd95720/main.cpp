#include <iostream>
#include <vector>

int main(void) {
    std::vector<bool> a;
    a.push_back(false);
    
    auto x = a[0];
    x = true;
    
    std::cout << a[0] << std::endl;
    
    return 0;
}