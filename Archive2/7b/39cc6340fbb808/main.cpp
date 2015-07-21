#include <iostream>
#include <vector>
#include <memory>

class A{ };

void (*foo)(A* p){ };

int main(){
    std::shared_ptr<A> sp(new A, foo);
}