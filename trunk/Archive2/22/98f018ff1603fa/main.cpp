#include <iostream>

int main() {
    int* p;
    p = (int*)&p;
    
    *p = 7;
    
    std::cout << *p;
    return 0;
}