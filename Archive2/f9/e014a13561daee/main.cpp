#include <iostream>
#include <memory>
#include <vector>

class Base
{
  public:
    virtual void identity() const
    {
        std::cout << "Base\n";
    }

    virtual ~Base() = default;
};

class Derived: public Base
{
  public:
    virtual void identity() const override
    {
        std::cout << "Derived\n";
    }
};

int main()
{
    //Approach 1: pointers
    std::vector<std::unique_ptr<Base>> foo;
    foo.emplace_back(std::make_unique<Base>());
    foo.emplace_back(std::make_unique<Derived>());
    foo.emplace_back(std::make_unique<Base>());
    for(const auto& p: foo)
        p->identity();
    std::cout << "\n\n";

    //Approach 2: reference wrappers
    std::vector<std::reference_wrapper<Base>> bar;
    Base i1, i3;
    Derived i2;
    bar.emplace_back(i1);
    bar.emplace_back(i2);
    bar.emplace_back(i3);
    for(Base& p: bar)
        p.identity();
    std::cout << "\n\n";
}