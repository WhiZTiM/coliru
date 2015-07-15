#include <iostream>

struct Tracked
{
    Tracked() { std::cout << "ctor\n"; }
    Tracked(const Tracked&) { std::cout << "copy\n"; }
    ~Tracked() { std::cout << "dtor\n"; }
};

struct Tester
{
    void foo()
    {
        static Tracked t;
    }
};

int main()
{
    Tester t1;
    Tester t2;
    
    t1.foo();
    t2.foo();
}