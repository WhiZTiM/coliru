#include <iostream>

int main() {
    int* p;
    p = (int*)&p;
    
    *p = 1;
    
    std::cout << p << ' ' << std::hex << *p;
    return 0;
}