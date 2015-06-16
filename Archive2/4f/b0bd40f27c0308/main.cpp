#include <iostream>
#include <vector>
#include <list>
#include <memory>

struct X
{
    X(int i) : x{std::make_unique<int>(i)} { }
    X(X&&) = default;
    X& operator = (X&&) = default;
    ~X() { if (x) { std::cout << *x << std::endl; } }
    std::unique_ptr<int> x;
};

int main()
{
    std::vector<X> v;
    v.emplace_back(1);
    v.emplace_back(2);
    v.emplace_back(3);
    std::cout << "Destroying...\n";
}