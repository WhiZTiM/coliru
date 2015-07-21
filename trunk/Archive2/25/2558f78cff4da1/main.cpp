#include <iostream>
#include <utility>

struct A {
    A& operator=(A&) {
        std::cout << "copy assignment called" << std::endl;
        return *this;
    }
    
    A& operator=(A&&) {
        std::cout << "move assignment called" << std::endl;
        return *this;
    }
};

int main() {
    A a, b;    
    b = a;
    b = std::move(a);
}
