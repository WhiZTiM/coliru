#include <array>
#include <iostream>
struct A {
 uint a : 3;
}; 

 
 int main() {
    std::array<A, 10> a;
    std::cout << sizeof(a) << " " << sizeof(int{}) << std::endl;
    return 0;
}
