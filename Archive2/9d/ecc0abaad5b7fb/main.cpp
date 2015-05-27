// Example program
#include <iostream>
#include <string>
#include <memory>


// Option 1. This one is to return pointer of the base class type that holds concrete type data (see implementations in the BB and CC)
// this is pretty much what we have, only replacing shared_ptr for raw pointer

struct A
{
    virtual std::string toJson() const
    {
        return "A::toJson()";
    }
};

struct B: public A
{
    std::string toJson() const
    {
        std::string baseImpl = A::toJson();
        return baseImpl + " + " + "B::toJson()";
    }
};

struct C: public A
{
    std::string toJson() const
    {
        std::string baseImpl = A::toJson();
        return baseImpl + " + " + "C::toJson()";
    }    
};

struct AA
{
    virtual A* getMember() = 0;
};

struct BB: public AA
{
    A* getMember()
    {
        return &b;    
    }
        
    private:
        B b; // note structure, rather than a pointer
};

struct CC: public AA
{
    A* getMember()
    {
        return &c;    
    }

private:
        C c; // note structure, rather than a pointer
};

int main()
{
    BB b;
    CC c;
    
    std::cout << b.getMember()->toJson() << std::endl;
    std::cout << c.getMember()->toJson() << std::endl;
}
