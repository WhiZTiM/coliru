#include<memory>
#include<iostream>

class Base
{
public:
    virtual void aVirtualFunction() = 0;
    virtual Base& operator<<( int ) = 0;
};

class A : public Base
{
    virtual A& operator<<( int ) override
    {
        // Do something
        return *this;
    }
};

class B : public Base
{
    virtual B& operator<<( int ) override
    {
        // Do something
        return *this;
    }
};

int main()
{
}
    