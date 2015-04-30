#include <queue>
#include <iostream>

class A : std::queue<double>
{
public:
    A() { push( 1 ); push( 42.123 ); }
    void foo();
};

void A::foo()
{
    for( auto elem : c ) {
        std::cout << elem << std::endl;
    }
}

int main()
{
    A a;
    a.foo();
}
