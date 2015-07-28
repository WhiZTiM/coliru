#include <iostream>
#include <string>

class dog { 
public: 
    dog(std::string name) : mname(name) {} // use initializer list
private: 
    std::string mname;
};

void Foo(dog g) {}

int main()
{
    std::string name = "fido";
    Foo(name);
}

