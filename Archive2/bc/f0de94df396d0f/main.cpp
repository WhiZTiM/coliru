// Example program
#include <iostream>
#include <string>
#include <memory>


// Option 2. This one is to return toJson from inner implementation instead of exposing the pointer to A<-B,C

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
    virtual std::string toJson() const = 0;
};

struct BB: public AA
{
    std::string toJson() const
    {
        return b.toJson();    
    }
        
    private:
        B b; // note structure, rather than a pointer
};

struct CC: public AA
{
    std::string toJson() const
    {
        return c.toJson();    
    }

private:
        C c; // note structure, rather than a pointer
};

int main()
{
    BB b;
    CC c;
    
    std::cout << b.toJson() << std::endl;
    std::cout << c.toJson() << std::endl;
}
