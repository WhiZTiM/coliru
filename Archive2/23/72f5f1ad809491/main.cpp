#include<iostream>
#include<typeinfo>
class Base { public: virtual ~Base(){} };
class Derived : public Base{};
int main()
{
     Derived d;    
     Base& b = d;
     std::cout << typeid(b).name() << '\n';
}
