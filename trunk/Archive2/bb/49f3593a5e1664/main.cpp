#include <vector>
#include <memory>
#include <iostream>
#include<functional>
#include <boost/filesystem.hpp>


template<typename T>
struct FailStruct;

template<typename T>
class Foo{
    public:
    T a = static_cast<T>(1.0);
};

class Bar{
    public:
    int b = 2;
};

Foo<double> MyFunction(const Bar* b)
{
    Foo<double> toReturn;
    std::cout << "Bar's member value is " << b->b << std::endl;
    return toReturn;
}

void Baz(std::function<Foo<double>(const Bar*)> f)
{
    Bar* barPtr = new Bar();
    const auto& w = barPtr;
    
    auto prop = f(w);
    std::cout << "Value of prop: " << prop.a << std::endl;
    
    delete barPtr;
}

int main(int argc, char* argv[])
{
    
    Baz(::MyFunction);
    std::cout << "Hello world " << std::endl;
    return 0;
}