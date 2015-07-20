#include <memory>
#include <iostream>

class Base { public: virtual ~Base() {} };
class Derived : public Base {};

void foo(std::shared_ptr<Base> basePtr)
{
    (void)(&basePtr);
    std::cout << "foo called" << std::endl;
}

void baz()
{
    class MoreDerived : public Base {};
    foo(std::make_shared<MoreDerived>());
    foo(std::shared_ptr<Base>(new MoreDerived));

    Base *basePtr = new MoreDerived;
    foo(std::shared_ptr<Base>(basePtr));
}

int main()
{
    foo(std::make_shared<Derived>());
    foo(std::shared_ptr<Base>(new Derived));

    baz();
    
    std::cout << "lel" << std::endl;
}