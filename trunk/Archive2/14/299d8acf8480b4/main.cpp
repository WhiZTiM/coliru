#include <iostream>
#include <vector>
#include <memory>

struct A{ };

void foo(A*){ std::cout << "foo" << std::endl; }

void (*bar)(){ };


int main(){
    
    bar();
}