#include <iostream>

int main() {
    int* p;
    p = (int*)&p;
    
    std::cout << p << " ";
    *p = 0;
    
    std::cout << p;
    return 0;
}