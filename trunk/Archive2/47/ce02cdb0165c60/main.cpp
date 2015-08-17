#include <iostream>

void Foo(int i) {
    i = 10;    
}

void Bar(int& i) {
    i = 10;    
}


int main() {
    int a1 = 0;
    int a2 = 0;
    
    Foo(a1);
    Bar(a2);
    
    std::cout << a1 << std::endl;
    std::cout << a2 << std::endl;
}