#include <iostream>
#include <string>
#include <vector>

class Base
{
public:
    void operator =(const Base&)
    {
        std::cout << "Base operator =" << std::endl;
    }
};

class Derived : public Base
{
public:
    void operator =(const Derived&)
    {
        std::cout << "Derived operator =" << std::endl;
    }
};

int main()
{
    //Create a Derived
    Derived* derived = new Derived;
    //Assignment operator
    *derived = Derived();
    
    //Put derived in a Base pointer
    Base* base = derived;
    //Assignment operator
    *base = Base();
    
    delete derived;
}
