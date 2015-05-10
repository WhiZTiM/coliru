#include <string>
#include <iostream>

class Foo
{
public:
    Foo() {}

    std::string Bar;
    int Boo;
};

void foo( const Foo& f )
{
    std::cout << f.Bar << " " << f.Boo << std::endl;
}

int main()
{
    foo( []{ Foo f; f.Bar = "sausage"; f.Boo = 4; return f; }() );
}
