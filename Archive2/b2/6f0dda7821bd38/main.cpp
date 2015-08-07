#include <iostream>

int main() {
    long long int* p;
    p = (long long int*)&p;
    
    *p = 1;
    
    std::cout << p << ' ' << std::hex << *p;
    return 0;
}