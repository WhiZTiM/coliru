#include <iostream>

class A
{
public:
        int field_in_A;
};

class B : public A
{
public:
        int field_in_B;
};

int main()
{
        B b;

        std::cout << &b << std::endl;
        std::cout << &b.field_in_A << std::endl;
        std::cout << &b.field_in_B << std::endl;
}