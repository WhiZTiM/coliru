#include <iostream>

struct Foo
{
    Foo() : bar{ 0.1, 0.2, 0.3, 0.4 }
    {}
    
    float bar[4];
};

int main(int argc, char* argv[])
{
    Foo f;
    std::cout << f.bar[2] << std::endl;
    
    return 0;
}