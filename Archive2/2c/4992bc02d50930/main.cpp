#include <iostream>
#include <string>
#include <vector>

class Base
{
public:
    Base(int value) : mValue(value) {}
    ~Base() {}
    
    virtual void print() { std::cout << "Base class" << std::endl; }
    int getValue() { return mValue; }
    int compute() { return getValue() * 2; }
private:
    int mValue;
};

class Derived: Base
{
public:
    Derived(int value) : Base(value) {}
    virtual void print() { std::cout << "Derived class" << std::endl;}
    int compute() { return getValue() * 3; }
};

int main()
{
    Derived* d1 = new Derived (1);
    d1->print();
    std::cout << d1->compute() << std::endl; 
    
    Base* d2 = new Derived(1);
    d2->print();
    std::cout << d2->compute() << std::endl; 
}
