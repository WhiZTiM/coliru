#include <iostream>
#include <vector>
#include <sstream>
#include <utility>

struct A
{
    A(){ }
    A(const A&){ std::cout << "A&" << std::endl; }
    ~A(){ std::cout << "~A()" << std::endl; }
    A operator=(const A&){ std::cout << "operator=" << std::endl; return A();}
};

void foo(const A&&){ std::cout << "foo()" << std::endl; }

int main(){
    const A& a = A();
    foo(std::move(a));
    std::cout << "before ending the program" << std::endl;
}