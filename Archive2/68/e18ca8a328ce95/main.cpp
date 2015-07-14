#include <iostream>

struct Tracked
{
    Tracked() { std::cout << "ctor\n"; };
    Tracked(const Tracked&) { std::cout << "copy\n"; };
    ~Tracked() { std::cout << "dtor\n"; };
};

void foo()
{
    static const Tracked& ref = Tracked();
}

int main()
{
    std::cout << "main()\n";
    foo();
    std::cout << "bye\n";
}