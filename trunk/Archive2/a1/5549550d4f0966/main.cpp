struct T {
    T(int,int,int){}
};

class Foo
{
public:
    Foo();
    ~Foo();

private:
    T* var;
};

Foo::Foo()
{
    var = new T(1, 2, 3);
}

Foo::~Foo()
{
    delete var;
}

#include <iostream>

using namespace std;

int main()
{
    Foo test;
    return 0;
}