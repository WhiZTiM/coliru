#include <iostream>
#include <initializer_list>

struct C
{
    C(std::initializer_list<int>) { std::cout << "list\n"; }
    C(std::initializer_list<int>, std::initializer_list<int>) { std::cout << "twice-list\n"; }
};

int main()
{
    C c1 { {1,2}, {3} }; // twice-list ctor
    C c2 { {1}, {2} }; // why not twice-list ?
    return 0;
}
