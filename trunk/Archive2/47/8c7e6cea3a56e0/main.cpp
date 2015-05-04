#include <iostream>
#include <string>
#include <functional>
#include <memory>

struct Foo{
    int x;
    Foo(int x) : x(x){}
    int show(){
        return x;
    }
};

int main()
{
    auto foo = std::make_unique<Foo>(3);
    std::cout<<foo->show() <<std::endl;
}
